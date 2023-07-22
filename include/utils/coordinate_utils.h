#ifndef COORDINATE_UTILS_H
#define COORDINATE_UTILS_H
#include "file_utils.h"
#include "string_utils.h"

namespace utils::coordinate_utils {
	template <typename T>
	std::vector<T> string_to_coordinate_vector(std::string str) {
		return utils::string_utils::convert_string_vector<T>(utils::string_utils::split_by_string(str, ","));
	}

	template <typename T>
	std::string coordinate_vector_to_string(std::vector<T> v) {
		std::string str;
		for (int i=0; i<v.size(); i++) {
			str += std::to_string(v[i]);
			if (i != v.size()-1) {
				str += ",";
			}
		}

		return str;
	}

	std::string coordinate_vector_to_string(std::vector<std::string> v) {
		std::string str;
		for (int i=0; i<v.size(); i++) {
			str += v[i];
			if (i != v.size()-1) {
				str += ",";
			}
		}

		return str;
	}

} // utils::coordinate_utils

#endif // COORDINATE_UTILS_H
