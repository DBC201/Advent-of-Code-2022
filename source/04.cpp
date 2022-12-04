#include <04.h>	

using solutions::day_4::Day4;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	Day4 day4(argv[1]);

	std::cout << day4.part1() << std::endl;
	std::cout << day4.part2() << std::endl;
}
