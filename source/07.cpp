#include <07.h>	

using solutions::day_7::Day7;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	Day7 day7(argv[1]);

	std::cout << day7.part1() << std::endl;
	std::cout << day7.part2() << std::endl;
}
