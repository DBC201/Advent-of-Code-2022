#include <05.h>	

using solutions::day_5::Day5;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	Day5 day5(argv[1]);

	std::cout << day5.part1() << std::endl;
	std::cout << day5.part2() << std::endl;
}
