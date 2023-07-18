#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <unordered_set>

namespace file_utils = utils::file_utils;
namespace string_utils = utils::string_utils;

auto string_to_int(auto str) {
	return string_utils::convert_string_vector<int>(string_utils::split_by_string(str, ","));
}

auto int_to_string(int x, int y) {
	return std::to_string(x) + "," + std::to_string(y);
}

int find_max_y(auto& pieces) {
	int curr_y = INT32_MIN;
	for (const auto &p: pieces) {
		auto coords = string_to_int(p);
		curr_y = std::max(curr_y, coords[1]);
	}
	return curr_y;
}

bool move_particle(int& x, int& y, auto& pieces) {
	auto next_pos = int_to_string(x, y+1);
	if (!pieces.contains(next_pos)) {
		y++;
		return true;
	}

	next_pos = int_to_string(x-1, y+1);

	if (!pieces.contains(next_pos)) {
		x--;
		y++;
		return true;
	}

	next_pos = int_to_string(x+1, y+1);

	if (!pieces.contains(next_pos)) {
		x++;
		y++;
		return true;
	}
 
	return false;
}

int part1(std::unordered_set<std::string> pieces) {
	int max_y = find_max_y(pieces);
	int sand_count = 0;
	
	while (true) {
		int x = 500, y = 0;
		while (y < max_y && move_particle(x, y, pieces)) {
		}
		if (y >= max_y) {
			return sand_count;
		}
		pieces.insert(int_to_string(x, y));
		sand_count++;
	}
}

int part2(std::unordered_set<std::string> pieces) {
	int max_y = find_max_y(pieces);
	int sand_count = 0;
	
	while (true) {
		int x = 500, y = 0;
		while (y < max_y+1 && move_particle(x, y, pieces)) {
		}
		pieces.insert(int_to_string(x, y));
		sand_count++;
		if (x == 500 && y == 0) {
			return sand_count;
		}
	}
}

int main(int argc, char **argv) {
	if (argc < 2)
	{
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::unordered_set<std::string> pieces;
	file_utils::process_lines(argv[1], [&](auto line) {
		auto tokens = string_utils::split_by_string(line, " -> ");
		for (int i=0; i<tokens.size()-1; i++) {
			auto coords1 = string_to_int(tokens[i]);
			auto coords2 = string_to_int(tokens[i+1]);
			for (int j=std::min(coords1[0], coords2[0]); j<=std::max(coords1[0], coords2[0]); j++) {
				pieces.insert(int_to_string(j, coords1[1]));
			}
			for (int j=std::min(coords1[1], coords2[1]); j<=std::max(coords1[1], coords2[1]); j++) {
				pieces.insert(int_to_string(coords1[0], j));
			}	
		}	
	});

	std::cout << part1(pieces) << std::endl;

	std::cout << part2(pieces) << std::endl;

	return 0;
}
