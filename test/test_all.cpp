#include <01.h>
#include <02.h>
#include <03.h>
#include <04.h>
#include <05.h>

using solutions::day_1::Day1;
using solutions::day_2::Day2;
using solutions::day_3::Day3;
using solutions::day_4::Day4;
using solutions::day_5::Day5;

bool assert(auto actual, auto expected) {
	if (actual != expected) {
		std::cerr << "Failed: (actual)" << actual << " == (expected)" << expected << std::endl;
		return false;
	}
	else {
		std::cerr << "Passed: (actual)" << actual << " == (expected)" << expected << std::endl;
		return true;
	}
}

bool test_day(auto day_id, auto day, auto p1_solution, auto p2_solution) {
	bool passed = true;
	std::cout << "--------------------" << std::endl;
	std::cout << "Testing " << day_id << std::endl;
	std::cout << "Part 1: ";
	try {
		passed = !assert(day.part1(), p1_solution) ? false : passed;
	}
	catch (std::exception& e) {
		std::cerr << "Failed with error: " << e.what() << std::endl;
		passed = false;
	}
	std::cout << "Part 2: ";
	try {
		passed = !assert(day.part2(), p2_solution) ? false : passed;
	}
	catch (std::exception& e) {
		std::cerr << "Failed with error: " << e.what() << std::endl;
		passed = false;
	}
	return passed;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "project root absolute path not given" << std::endl;
		return EXIT_FAILURE;
	}

	std::vector<std::string> failed_tests;

	const std::string root = argv[1];

	auto get_input_path = [&](std::string day) {
		return root + "/inputs" + "/" + day + ".txt";
	};

	auto day1_id = solutions::day_1::day_id;
	auto day2_id = solutions::day_2::day_id;
	auto day3_id = solutions::day_3::day_id;
	auto day4_id = solutions::day_4::day_id;
	auto day5_id = solutions::day_5::day_id;
	
	Day1 day1(get_input_path(day1_id));
	if (!test_day(day1_id, day1, 70369, 203002)) {
		failed_tests.push_back(day1_id);
	}

	Day2 day2(get_input_path(day2_id));
	if (!test_day(day2_id, day2, 13221, 13131)) {
		failed_tests.push_back(day2_id);
	}

	Day3 day3(get_input_path(day3_id));
	if (!test_day(day3_id, day3, 8053, 2425)) {
		failed_tests.push_back(day3_id);
	}

	Day4 day4(get_input_path(day4_id));
	if (!test_day(day4_id, day4, 518, 909)) {
		failed_tests.push_back(day4_id);
	}

	Day5 day5(get_input_path(day5_id));
	if (!test_day(day5_id, day5, "QPJPLMNNR", "BQDNWJPVJ")) {
		failed_tests.push_back(day5_id);
	}

	if (failed_tests.empty()) {
		std::cout << "--------------------" << std::endl;
		std::cout << "all tests passed" << std::endl;;
		return EXIT_SUCCESS;
	}
	else {
		std::cerr << "--------------------" << std::endl;
		std::cerr << "failed tests:" << std::endl;
		for (const auto& id : failed_tests) {
			std::cerr << id << ", ";
		}
		std::cerr << std::endl;
		return EXIT_FAILURE;
	}
}
