#include <02.h>	

using solutions::day_2::Day2;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	Day2 day2(argv[1]);

	std::cout << day2.part1() << std::endl;
	std::cout << day2.part2() << std::endl;
}

