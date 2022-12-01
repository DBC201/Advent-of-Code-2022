/*
Template that other days will follow and inherit the day class from
*/
#ifndef DAY0_H
#define DAY0_H
#include <iostream>

namespace solutions::day_0 {
	const std::string day_id = "00";

	class Day0 {
	public:
		Day0(std::string filepath) {
			this->filepath = filepath;
		}

		auto part1();

		auto part2();
	protected:
		std::string filepath;
	};
} // solutions::day_0

#endif // DAY0_H
