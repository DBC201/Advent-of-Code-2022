#ifndef DAY1_H
#define DAY1_H

#include <00.h>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <algorithm>
#include <numeric>

using utils::file_utils::process_lines;
using utils::string_utils::convert_string;
using solutions::day_0::Day0;

namespace solutions::day_1 {
	const std::string day_id = "00";

	class Day1: public Day0 {
	public:
		Day1(std::string filepath): Day0(filepath) {
			uint64_t current_calories = 0;
			max_calorie_elf.first = -1;
			max_calorie_elf.second = 0;
			// need two newlines at the end of file
			process_lines(filepath, calories, [&](auto line, auto container) {
				if (line.empty()) {
					calories.push_back(current_calories);
					if (current_calories > max_calorie_elf.second) {
						max_calorie_elf.first = calories.size() - 1;
						max_calorie_elf.second = current_calories;
					}
					current_calories = 0;
				} 
				else {
					current_calories += convert_string<uint64_t>(line);
				}
			});
		}

		uint64_t part1() {
			return max_calorie_elf.second;
		}

		uint64_t part2() {
			std::sort(calories.begin(), calories.end(), std::greater<uint64_t>());
			return std::accumulate(calories.begin(), calories.begin()+3, 0);
		}
	private:
		std::vector<uint64_t> calories;
		std::pair<int32_t, uint64_t> max_calorie_elf;
	};
} // solutions::day_1

#endif // DAY1_H
