#include <06.h>	

using solutions::day_6::Day6;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	Day6 day6(argv[1]);

	std::cout << day6.part1() << std::endl;
	std::cout << day6.part2() << std::endl;
}
