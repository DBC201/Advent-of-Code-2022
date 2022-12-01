#include <01.h>	

using solutions::day_1::Day1;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	Day1 day1(argv[1]);

	std::cout << day1.part1() << std::endl;
	std::cout << day1.part2() << std::endl;
}

