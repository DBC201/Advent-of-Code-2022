#include <iostream>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <unordered_map>
#include <vector>

namespace file_utils = utils::file_utils;
namespace string_utils = utils::string_utils;

std::string coords_to_string(int x, int y)
{
	return std::to_string(x) + "," + std::to_string(y);
}

void move_knot(int &hx, int &hy, int &tx, int &ty)
{
	int dx = hx - tx;
	int dy = hy - ty;
	int adx = std::abs(dx);
	int ady = std::abs(dy);

	if (adx > 1 && ady > 1) {
		tx += dx > 0 ? 1 : -1;
		ty += dy > 0 ? 1 : -1;
	}
	else if (adx > 1 && ady > 0)
	{
		tx += dx > 0 ? 1 : -1;
		ty = hy;
	}
	else if (adx > 1)
	{
		tx += dx > 0 ? 1 : -1;
	}
	else if (ady > 1 && adx > 0)
	{
		tx = hx;
		ty += dy > 0 ? 1 : -1;
	}
	else if (ady > 1)
	{
		ty += dy > 0 ? 1 : -1;
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}

	int hx = 0, hy = 0, tx = 0, ty = 0;

	std::unordered_map<std::string, int> tail_visited;

	file_utils::process_lines(argv[1], [&](auto line)
							  {
		auto tokens = string_utils::split_by_string(line, " ");
		char direction = tokens[0][0];
		int distance = string_utils::convert_string<int>(tokens[1]);

		for (int i=0; i<distance; i++) {
			switch (direction) {
				case 'L':
					hx--;
					break;
				case 'R':
					hx++;
					break;
				case 'U':
					hy++;
					break;
				case 'D':
					hy--;
					break;
			}

			move_knot(hx, hy, tx, ty);

			auto coord = coords_to_string(tx, ty);
			if (tail_visited.contains(coord)) {
				tail_visited.at(coord)++;
			}
			else {
				tail_visited.insert({coord, 1});
			}
		} });

	std::cout << tail_visited.size() << std::endl;

	// PART 2

	tail_visited.clear();

	int knot_count = 10;

	std::vector<std::vector<int>> tails(knot_count, std::vector<int>(2, 0));

	file_utils::process_lines(argv[1], [&](auto line)
							  {
		auto tokens = string_utils::split_by_string(line, " ");
		char direction = tokens[0][0];
		int distance = string_utils::convert_string<int>(tokens[1]);

		for (int i=0; i<distance; i++) {
			switch (direction) {
				case 'L':
					tails[0][0]--;
					break;
				case 'R':
					tails[0][0]++;
					break;
				case 'U':
					tails[0][1]++;
					break;
				case 'D':
					tails[0][1]--;
					break;
			}

			for (int i=1; i<tails.size(); i++) {
				move_knot(tails[i-1][0], tails[i-1][1], tails[i][0], tails[i][1]);
			}

			auto tail_to_string = [&] (auto knot) {
				return coords_to_string(knot[0], knot[1]);
			};

			auto coord = coords_to_string(tails[knot_count-1][0], tails[knot_count-1][1]);
			if (tail_visited.contains(coord)) {
				tail_visited.at(coord)++;
			}
			else {
				tail_visited.insert({coord, 1});
			}
		} });

		std::cout << tail_visited.size() << std::endl;

	return EXIT_SUCCESS;
}
