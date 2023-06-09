#include <iostream>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <vector>

namespace file_utils = utils::file_utils;
namespace string_utils = utils::string_utils;

int main(int argc, char **argv) {
	if (argc < 2)
	{
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}

	int cycle_count = 0;
	int x = 1;

	int signal_sum = 0;

	int width = 40, height = 6;

	std::vector<std::vector<bool>> crt(height, std::vector<bool>(width, false));

	auto increment_cycle = [&] () {
		int column = cycle_count % width;

		if (column == x - 1 || column == x || column == x + 1) {
			int row = (cycle_count/width) % height;
			crt[row][column] = true;
		}

		cycle_count++;

		if (cycle_count - 20 >= 0 && (cycle_count - 20) % width == 0) {
			signal_sum += x*cycle_count;
		}
	};

	file_utils::process_lines(argv[1], [&](auto line) {
		auto tokens = string_utils::split_by_string(line, " ");
		if (tokens[0] == "noop") {
			increment_cycle();
		}
		else if (tokens[0] == "addx") {
			increment_cycle();
			increment_cycle();
			int V = string_utils::convert_string<int>(tokens[1]);
			x += V;
		}
	});

	std::cout << signal_sum << std::endl;

	for (int i=0; i<crt.size(); i++) {
		for (int j=0; j<crt[i].size(); j++) {
			if (crt[i][j]) {
				std::cout << "#";
			}
			else {
				std::cout << ".";
			}
		}
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}