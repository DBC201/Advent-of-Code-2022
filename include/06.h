#ifndef DAY6_H
#define DAY6_H

#include <00.h>
#include <utils/file_utils.h>
#include <unordered_set>
using solutions::day_0::Day0;
using utils::file_utils::get_lines;

namespace solutions::day_6 {
	const std::string day_id = "06";

	class Day6: public Day0  {
	public:
		Day6(std::string filepath): Day0(filepath) {
			input = get_lines<std::string>(filepath, [](auto line){ return line; })[0];
		}

		auto part1() {
			int64_t i;
			for (i=0; i<input.length()-4; i++) {
				std::unordered_set<char> c;
				c.insert(input[i]);
				c.insert(input[i+1]);
				c.insert(input[i+2]);
				c.insert(input[i+3]);
				if (c.size() == 4) {
					i += 4;
					break;
				}
			}
			return i;
		};

		auto part2() {
			int64_t i;
			for (i=0; i<input.length()-14; i++) {
				std::unordered_set<char> c;
				for (int16_t j=i; j<i+14; j++) {
					c.insert(input[j]);
				}
				if (c.size() == 14) {
					i += 14;
					break;
				}
			}
			return i;
		};
	private:
		std::string input;
	};
} // solutions::day_6

#endif // DAY6_H
