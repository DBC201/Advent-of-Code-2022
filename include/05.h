#ifndef DAY5_H
#define DAY5_H

#include <00.h>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <utils/regex_utils.h>
#include <stack>
using solutions::day_0::Day0;
using utils::file_utils::process_lines;
using utils::string_utils::replace_substring;
using utils::string_utils::split_by_string;
using utils::string_utils::convert_string_vector;
using utils::regex_utils::RegexWrapper;

namespace solutions::day_5 {
	const std::string day_id = "05";

	class Day5: public Day0 {
	public:
		Day5(std::string filepath): Day0(filepath) {
			bool crates_read = false;
			RegexWrapper regexWrapper("\\[.\\]");
			using crate_order_t = std::pair<std::string, uint16_t>;
			using crate_row_t = std::vector<crate_order_t>;
			using crate_rows_t = std::vector<crate_row_t>;
			crate_rows_t raw_crates;
			process_lines(filepath, [&](auto line) {
				if (line.empty()) {
					return;
				}else if (std::isdigit(line[1])) {
					crates_read = true;
					line = line.substr(1, line.length()-2);
					uint32_t crate_count = replace_substring(line, " ", "").length();
					stacks = stacks_container_t(crate_count);
					for (int64_t i=raw_crates.size()-1; i>=0; i--) {
						for (const auto& crate: raw_crates[i]) {
							stacks[crate.second].push(crate.first);
						}
					} 
				} else if (!crates_read) {
					crate_row_t crate_row;
					regexWrapper.handleMatches(line, [&](auto smatch) {
						crate_order_t crate;
						crate.first = smatch.str(0);
						crate.second = smatch.position(0)/4;
						crate_row.push_back(crate);
					});
					raw_crates.push_back(crate_row);
				}
				else {
					auto tokens = convert_string_vector<uint16_t>(split_by_string(line, " "));
					std::vector<uint16_t> curr_moves(3);
					curr_moves[0] = tokens[1];
					curr_moves[1] = tokens[3]-1;
					curr_moves[2] = tokens[5]-1;
					moves.push_back(curr_moves);
				}
			});
		}

		auto part1() {
			auto stacks = this->stacks;
			for (auto it=moves.begin(); it!=moves.end(); ){
				auto curr_move = *it;
				auto from = curr_move[1];
				auto to = curr_move[2];
				auto quantity = curr_move[0];
				for (auto i=0; i<quantity; i++) {
					auto c = stacks[from].top();
					stacks[from].pop();
					stacks[to].push(c);
				}
				it++;
			}
			std::string top_crates;
			for (auto it=stacks.begin(); it!=stacks.end(); ) {
				auto crate = (*it).top();
				crate = replace_substring(crate, "[", "");
				crate = replace_substring(crate, "]", "");
				top_crates+=crate;
				it++;
			}
			return top_crates;
		}

		auto part2() {
			auto stacks = this->stacks;
			for (auto it=moves.begin(); it!=moves.end(); ){
				auto curr_move = *it;
				auto from = curr_move[1];
				auto to = curr_move[2];
				auto quantity = curr_move[0];
				std::vector<std::string> picked_crates(quantity);
				for (int64_t i=quantity-1; i>=0; i--) {
					auto c = stacks[from].top();
					stacks[from].pop();
					picked_crates[i] = c;
				}

				for (const auto& c: picked_crates) {
					stacks[to].push(c);
				}
				it++;
			}
			std::string top_crates;
			for (auto it=stacks.begin(); it!=stacks.end(); ) {
				auto crate = (*it).top();
				crate = replace_substring(crate, "[", "");
				crate = replace_substring(crate, "]", "");
				top_crates+=crate;
				it++;
			}
			return top_crates;
		}
	private:
		using stacks_container_t = std::vector<std::stack<std::string>>;
		stacks_container_t stacks;
		std::vector<std::vector<uint16_t>> moves;
	};
} // solutions::day_5

#endif // DAY5_H
