#include <03.h>	

using solutions::day_3::Day3;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	Day3 day3(argv[1]);

	std::cout << day3.part1() << std::endl;
	std::cout << day3.part2() << std::endl;
}
