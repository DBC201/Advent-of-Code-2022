#include <utils/file_utils.h>

namespace file_utils = utils::file_utils;

struct Position {
	uint16_t elevation;
	uint64_t dist_to_start;
	bool calculated = false;
};

void dijkstra(std::vector<std::vector<Position*>>& g) {
	while (true) {
		Position *curr_min = nullptr;
		int y = 0;
		int x;
		int min_x, min_y;
		for (const auto &r: g) {
			x = 0;
			for (const auto &p: r) {
				if (!p->calculated) {
					if (curr_min == nullptr || curr_min->dist_to_start > p->dist_to_start) {
						curr_min = p;
						min_y = y;
						min_x = x;
					}
				}
				x++;
			}
			y++;
		}

		if (curr_min == nullptr) {
			break;
		}

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0) {
					continue;
				}

				if (i != 0 && j != 0) {
					continue;
				}
				
				int curr_y = min_y + i;
				int curr_x = min_x + j;

				if (curr_y >= 0 && curr_y < g.size() && curr_x >= 0 && curr_x < g[curr_y].size() && g[curr_y][curr_x]->elevation <= curr_min->elevation+1) {
					uint64_t curr_dist_to_start = curr_min->dist_to_start+1;
					if (curr_dist_to_start < g[curr_y][curr_x]->dist_to_start) {
						g[curr_y][curr_x]->dist_to_start = curr_dist_to_start;
					}			
				} 
			}
		}
		curr_min->calculated = true;
	}
}

void reverse_dijkstra(std::vector<std::vector<Position*>>& g) {
	while (true) {
		Position *curr_min = nullptr;
		int y = 0;
		int x;
		int min_x, min_y;
		for (const auto &r: g) {
			x = 0;
			for (const auto &p: r) {
				if (!p->calculated) {
					if (curr_min == nullptr || curr_min->dist_to_start > p->dist_to_start) {
						curr_min = p;
						min_y = y;
						min_x = x;
					}
				}
				x++;
			}
			y++;
		}

		if (curr_min == nullptr || curr_min->dist_to_start == UINT64_MAX) {
			break;
		}

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0) {
					continue;
				}

				if (i != 0 && j != 0) {
					continue;
				}
				
				int curr_y = min_y + i;
				int curr_x = min_x + j;

				if (curr_y >= 0 && curr_y < g.size() && curr_x >= 0 && curr_x < g[curr_y].size() && g[curr_y][curr_x]->elevation >= curr_min->elevation-1) {
					uint64_t curr_dist_to_start = curr_min->dist_to_start+1;
					if (curr_dist_to_start < g[curr_y][curr_x]->dist_to_start) {
						g[curr_y][curr_x]->dist_to_start = curr_dist_to_start;
					}			
				} 
			}
		}
		curr_min->calculated = true;
	}
}

int main(int argc, char **argv) {
	if (argc < 2)
	{
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::vector<std::vector<Position*>> g;
	Position* finish;

	file_utils::process_lines(argv[1], [&](auto line) {
		std::vector<Position*> r;
		for (const auto& c: line) {
			Position* p = new Position;
			if (c == 'S') {
				p->dist_to_start = 0;
				p->elevation = 0;
			}
			else if (c == 'E') {
				p->dist_to_start = UINT64_MAX;
				p->elevation = 'z'-'a';
				finish = p;
			}
			else {
				p->dist_to_start = UINT64_MAX;
				p->elevation = c-'a';
			}
			r.push_back(p);
		}
		g.push_back(r);
	});

	dijkstra(g);
	
	std::cout << finish->dist_to_start << std::endl;

	finish->dist_to_start = 0;

	for (const auto &r: g) {
		for (const auto &p: r) {
			if (p != finish) {
				p->dist_to_start = UINT64_MAX;
			}
			p->calculated = false;
		}
	}

	reverse_dijkstra(g);

	Position *curr_min = nullptr;
	int y = 0, x;
	for (const auto &r: g) {
		x = 0;
		for (const auto &p: r) {
			if (p != finish && p->elevation == 0) {
				if (curr_min == nullptr || curr_min->dist_to_start > p->dist_to_start) {
					curr_min = p;
				}
			}
			x++;
		}
		y++;
	}

	std::cout << curr_min->dist_to_start << std::endl;

	return 0;
}