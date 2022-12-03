#ifndef DAY3_H
#define DAY3_H

#include <00.h>
#include <utils/file_utils.h>
#include <utils/set_utils.h>
#include <unordered_set>
#include <string>
using solutions::day_0::Day0;
using utils::file_utils::get_lines;
using utils::set_utils::set_intersection;

namespace solutions::day_3 {
	const std::string day_id = "03";

	class Day3: public Day0 {
	public:
		Day3(std::string filepath): Day0(filepath) {
			priority_sum = 0;
			backpacks = get_lines<charset_t>(filepath, [&](auto line){
				auto length = line.length();
				uint32_t mid = length/2;
				auto b1 = line.substr(0, mid);
				auto b2 = line.substr(mid, mid);

				charset_t bs1 = string_to_charset(b1);
				charset_t bs2 = string_to_charset(b2);

				charset_t intersection = set_intersection<charset_t>(bs1, bs2);

				for (auto it=intersection.begin(); it!=intersection.end(); ){
					priority_sum += priority_value(*it);
					it++;
				} 

				return string_to_charset(line);
			});
		}

		auto part1() {
			return priority_sum;
		}

		auto part2() {
			uint32_t sum = 0;
			for (auto i=0; i<backpacks.size(); i+=3) {
				auto b1 = backpacks[i];
				auto b2 = backpacks[i+1];
				auto b3 = backpacks[i+2];
				charset_t intersect = set_intersection<charset_t>(b1, b2);
				intersect = set_intersection<charset_t>(intersect, b3);
				sum += priority_value(*intersect.begin());
			}
			return sum;
		}

	private:
		uint32_t priority_value(char c) {
			if (std::islower(c)) {
				return c - 'a' + 1;
			}
			else {
				return c - 'A' + 27;
			}
		}

		using charset_t = std::unordered_set<char>;
		using backpack_container_t = std::vector<charset_t>;
		backpack_container_t backpacks;
		uint32_t priority_sum;

		charset_t string_to_charset(std::string s) {
			charset_t set;
			for (auto i=0; i<s.length(); i++) {
				set.insert(s[i]);
			}
			return set;
		}
	};
} // solutions::day_3

#endif // DAY3_H
