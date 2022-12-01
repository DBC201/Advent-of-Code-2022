/*
Uses row reduction algorithm to decode input
*/
#ifndef REDUCTION_UTILS_H
#define REDUCTION_UTILS_H

#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace utils::reduction_utils {
	template<typename Tattribute, typename Tcommon>
	class ReductionSolver {
	public:
		ReductionSolver() = default;

		ReductionSolver(auto attributes) {
			for (const auto &attribute: attributes) {
				possible_matches.insert({attribute, possibility_container_t()});
			}
		}

		void add_input(Tattribute attribute, auto possibilities) {
			if (possible_matches.contains(attribute)) {
				std::unique_ptr<possibility_container_t> attribute_possibilities = std::make_unique<possibility_container_t>(
						possible_matches.at(attribute));
				for (const auto &p: possibilities) {
					// if it exists in one possibility but not other, discard that possibility
					if (!attribute_possibilities.get()->contains(p)) {
						attribute_possibilities.get()->insert(p);
					} else {
						attribute_possibilities.get()->erase(p);
					}
				}
			} else {
				possibility_container_t possibility_container;
				for (const auto &p: possibilities) {
					possibility_container.insert(p);
				}
				possible_matches.insert({attribute, possibility_container});
			}
		}

		void reduce() {
			while (1) {
				bool no_change = true;
				std::pair<Tattribute, uint32_t> smallest;
				smallest.second = UINT32_MAX;

				// find the smallest row
				for (auto it = possible_matches.begin(); it != possible_matches.end(); it++) {
					auto curr_size = it->second.size();
					if (curr_size < smallest.second) {
						smallest.first = it->first;
						smallest.second = curr_size;
					}
				}

				if (smallest.second == UINT32_MAX) {
					break;
				}
				std::unique_ptr<possibility_container_t> smallest_poss_ptr = std::make_unique<possibility_container_t>(
						possible_matches.at(smallest.first));


				// remove the smallest row and reduce the contents of it
				// from other rows where it intersects
				for (auto it = possible_matches.begin(); it != possible_matches.end(); it++) {
					if (smallest.first != it->first) {
						for (const auto &s: *(smallest_poss_ptr.get())) {
							it->second.erase(s);
						}
					}
				}

				final_matches.insert({smallest.first, *smallest_poss_ptr.get()});
				for (auto it = possible_matches.begin(); it != possible_matches.end();) {
					if (it->second.size() == 0) {
						final_matches.insert({it->first, *smallest_poss_ptr.get()});
						it = possible_matches.erase(it);
						no_change = false;
					} else {
						it++;
					}
				}
				possible_matches.erase(smallest.first);

				if (no_change) {
					break;
				}
			}
		}

		auto get_final_matches() {
			return final_matches;
		}

		auto get_value_to_attribute() {
			value_to_attribute_t value_to_attribute;
			for (const auto &p: final_matches) {
				for (const auto &value: p.second) {
					if (value_to_attribute.contains(value)) {
						value_to_attribute.at(value).insert(p.first);
					} else {
						attribute_container_t attribute_container;
						attribute_container.insert(p.first);
						value_to_attribute.insert({value, attribute_container});
					}
				}
			}
			return value_to_attribute;
		}

	private:
		using possibility_container_t = std::unordered_set<Tcommon>;
		using possible_matches_t = std::unordered_map<Tattribute, possibility_container_t>;
		using attribute_container_t = std::unordered_set<Tattribute>;
		using value_to_attribute_t = std::unordered_map<Tcommon, attribute_container_t>;
		possible_matches_t possible_matches;
		possible_matches_t final_matches;
	};
} // utils::reduction_utils

#endif // REDUCTION_UTILS_H