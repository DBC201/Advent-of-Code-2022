#ifndef DAY2_H
#define DAY2_H

#include <00.h>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <unordered_map>
#include <unordered_set>
using solutions::day_0::Day0;
using utils::file_utils::get_lines;
using utils::string_utils::split_by_string;

namespace solutions::day_2 {
	const std::string day_id = "02";

	class Day2: public Day0 {
	public:
		Day2(std::string filepath): Day0(filepath), win_points(6), draw_points(3) {
			play_conversion = {
				{"X", "A"},
				{"Y", "B"},
				{"Z", "C"},
			};

			win_conditions = {
				{"X", "C"},
				{"Y", "A"},
				{"Z", "B"},
				{"A", "C"},
				{"B", "A"}, 
				{"C", "B"}
			};

			move_points = {
				{"X", 1},
				{"Y", 2},
				{"Z", 3},
				{"A", 1},
				{"B", 2},
				{"C", 3}
			};

			total_score_part1 = 0;

			moves = get_lines<std::pair<std::string, std::string>>(filepath, [&](auto line) {
				auto moves = split_by_string(line, " ");
				auto player_move = moves[1];
				auto opponent_move = moves[0];
				auto player_move_score = move_points.at(player_move);
				auto win_score = win_conditions.at(player_move) == opponent_move ? win_points : 0;
				auto draw_score = play_conversion.at(player_move) == opponent_move ? draw_points : 0;
				auto round_score = player_move_score + win_score + draw_score;
				total_score_part1 += round_score;
				std::pair<std::string, std::string> round_moves;
				round_moves.first = opponent_move;
				round_moves.second = player_move;
				return round_moves;
			});
		}

		uint64_t part1() {
			return total_score_part1;
		}

		uint64_t part2() {
			uint64_t total_score = 0;
			for (auto it=moves.begin(); it!=moves.end(); it++) {
				auto move = *it;
				auto opponent_move = move.first;
				auto player_move = move.second;
				if (player_move == "X") {
					total_score += move_points.at(win_conditions.at(opponent_move));
				}
				else if (player_move == "Y") {
					total_score += move_points.at(opponent_move) + draw_points;
				}
				else if (player_move == "Z") {
					std::unordered_set<std::string> possible_plays = {"A", "B", "C"};
					possible_plays.erase(opponent_move);
					for (auto it2=possible_plays.begin(); it2!=possible_plays.end(); it2++) {
						if (win_conditions.at(opponent_move) == *it2) {
							it2 = possible_plays.erase(it2);
							break;
						}
					}
					total_score += move_points.at(*possible_plays.begin()) + win_points;
				}
			}
			return total_score;
		}
	private:
		std::unordered_map<std::string, std::string> win_conditions;
		std::unordered_map<std::string,std::string> play_conversion;
		std::unordered_map<std::string, uint16_t> move_points;
		std::vector<std::pair<std::string, std::string>> moves;
		uint64_t total_score_part1;
		const uint16_t win_points;
		const uint16_t draw_points;
	};
} // solutions::day_2

#endif // DAY2_H
