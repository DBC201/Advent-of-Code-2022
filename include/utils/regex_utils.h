#ifndef REGEX_UTILS_H
#define REGEX_UTILS_H

#include <regex>

namespace utils::regex_utils {
	class RegexWrapper{
		public:
			RegexWrapper(std::string expression) {
				r = std::regex(expression);
			}

			bool isMatch(std::string s) {
				return std::regex_match(s, r);
			}

			/**
			 * @brief 
			 * 
			 * @param s 
			 * @param lambda takes smatch object, some functions are: smatch.str(0), smatch.position(0)
			 */
			void handleMatches(std::string s, auto lambda) {
				std::vector<std::smatch> matches;
				for (auto it = std::sregex_iterator(s.begin(), s.end(), r); it!=std::sregex_iterator(); ){
					lambda(*it);
					it++;
				}
			}

			private:
				std::regex r;
	};
} // utils::regex_utils

#endif // REGEX_UTILS_H