#include <iostream>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <unordered_set>
#include <map>

namespace file_utils = utils::file_utils;
namespace string_utils = utils::string_utils;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string filename = argv[1];

	std::vector<std::vector<uint8_t>> trees;

	file_utils::process_lines(filename, trees, [&](auto line, auto& container) {
		std::vector<uint8_t> row;
		for (int i=0; i<line.size(); i++) {
			row.push_back(string_utils::convert_string<uint8_t>(line.substr(i, 1)));
		}
		container.push_back(row);
	});

	std::unordered_set<uint64_t> seen;

	for (int i=0; i<trees.size(); i++) {
		int8_t curr_max = -1;
		for (int j=0; j<trees[i].size(); j++) {
			if (curr_max < trees[i][j]) {
				curr_max = trees[i][j];
				seen.insert(i * trees[i].size() + j);
			}
		}

		curr_max = -1;

		for (int j=trees[i].size()-1; j>=0; j--) {
			if (curr_max < trees[i][j]) {
				curr_max = trees[i][j];
				seen.insert(i * trees[i].size() + j);
			}
		}
	}

	for (int j=0; j<trees.size(); j++) {
		int8_t curr_max = -1;
		for (int i=0; i<trees.size(); i++) {
			if (curr_max < trees[i][j]) {
				curr_max = trees[i][j];
				seen.insert(i * trees[i].size() + j);
			}
		}

		curr_max = -1;

		for (int i=trees.size()-1; i>=0; i--) {
			if (curr_max < trees[i][j]) {
				curr_max = trees[i][j];
				seen.insert(i * trees[i].size() + j);
			}
		}
	}

	std::cout << seen.size() << std::endl;

	uint64_t max_scenic_score = 0;

	auto calculate_scenic_score = [&](uint64_t y, uint64_t x) {
		uint64_t left_visible_count = 0, 
			right_visible_count = 0, up_visible_count = 0,
			 down_visible_count = 0;

		for (int i=x+1; i<trees[y].size(); i++) {
			right_visible_count++;
			
			if (trees[y][i] >= trees[y][x]) {
				break;
			}
		}

		for (int i=x-1; i>=0; i--) {
			left_visible_count++;
			if (trees[y][i] >= trees[y][x]) {
				break;
			}
		}

		for (int i=y+1; i<trees.size(); i++) {
			down_visible_count++;
			if (trees[i][x] >= trees[y][x]) {
				break;
			}
		}

		for (int i=y-1; i>=0; i--) {
			up_visible_count++;
			if (trees[i][x] >= trees[y][x]) {
				break;
			}
		}
		
		return left_visible_count * right_visible_count * up_visible_count * down_visible_count;
	};

	
	for (int i=0; i<trees.size(); i++) {
		for (int j=0; j<trees[i].size(); j++) {
			max_scenic_score = std::max(max_scenic_score, calculate_scenic_score(i, j));
		}
	}

	std::cout << max_scenic_score << std::endl;

	return EXIT_SUCCESS;
}
