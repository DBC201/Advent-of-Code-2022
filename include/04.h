#ifndef DAY4_H
#define DAY4_H

#include <00.h>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
using solutions::day_0::Day0;
using utils::file_utils::get_lines;
using utils::string_utils::split_by_string;
using utils::string_utils::convert_string_vector;

namespace solutions::day_4 {
	const std::string day_id = "04";

	class Day4: public Day0 {
	public:
		Day4(std::string filepath): Day0(filepath) {
			containing_elf_pair_count = 0;
			overlapping_elf_pair_count = 0;

			pairs = get_lines<elf_pair_t>(filepath, [&](auto line) {
				std::vector<std::string> elf_pair_vector = split_by_string(line, ",");
				auto create_elf_assignment = [](auto raw_elf_assingment) {
					std::vector<uint16_t> elf_vector = convert_string_vector<uint16_t>(split_by_string(raw_elf_assingment, "-"));
					elf_assignment_t elf;
					elf.first = elf_vector[0];
					elf.second = elf_vector[1];
					return elf;
				};

				elf_pair_t elf_pair;

				elf_pair.first = create_elf_assignment(elf_pair_vector[0]);
				elf_pair.second = create_elf_assignment(elf_pair_vector[1]);

				if (contains(elf_pair.first, elf_pair.second)) {
					containing_elf_pair_count++;					
				}

				if (overlaps(elf_pair.first, elf_pair.second)) {
					overlapping_elf_pair_count++;
				}

				return elf_pair;
			});
		}

		auto part1() {
			return containing_elf_pair_count;
		}

		auto part2() {
			return overlapping_elf_pair_count;
		}
	private:
		uint64_t containing_elf_pair_count;
		uint64_t overlapping_elf_pair_count;
		using elf_assignment_t = std::pair<uint16_t, uint16_t>;
		using elf_pair_t = std::pair<elf_assignment_t, elf_assignment_t>;
		using pairs_container_t = std::vector<elf_pair_t>; 
		pairs_container_t pairs;

		bool contains(elf_assignment_t a, elf_assignment_t b) {
			bool first_contains_second = a.first <= b.first && a.second >= b.second;
			bool second_contains_first = b.first <= a.first && b.second >= a.second;

			return first_contains_second || second_contains_first;
		}

		bool overlaps(elf_assignment_t a, elf_assignment_t b) {
			if (a.first <= b.first) {
				return a.second >= b.first;
			}
			else {
				return b.second >= a.first;
			}
		}
	};
} // solutions::day_4

#endif // DAY4_H
