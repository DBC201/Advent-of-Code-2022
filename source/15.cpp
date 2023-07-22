#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <utils/coordinate_utils.h>
#include <unordered_set>

namespace file_utils = utils::file_utils;
namespace string_utils = utils::string_utils;
namespace coordinate_utils = utils::coordinate_utils;

struct SignalZone {
	int64_t sensor_x;
	int64_t sensor_y;
	int64_t beacon_x;
	int64_t beacon_y;
};

bool noBeacon(int64_t x, int64_t y, SignalZone signalZone) {
	int64_t x_margin = std::abs(signalZone.sensor_x-signalZone.beacon_x);
	int64_t y_margin = std::abs(signalZone.sensor_y-signalZone.beacon_y);

	int64_t radius = x_margin + y_margin;

	if ((x == signalZone.sensor_x && y == signalZone.sensor_y) || (x == signalZone.beacon_x && y == signalZone.beacon_y)) {
		return false;
	}
	return std::abs(x-signalZone.sensor_x) + std::abs(y-signalZone.sensor_y) <= radius;
}

bool checkIfNoBeacon(int64_t x, int64_t y, std::vector<SignalZone> signal_zones) {
	for (int i=0; i<signal_zones.size(); i++) {
		if (noBeacon(x, y, signal_zones[i])) {
			return true;
		}
	}
	return false;
}

uint64_t part2(std::vector<SignalZone> signal_zones) {
	std::unordered_set<std::string> beacon_or_sensor;
	for (int i=0; i<signal_zones.size(); i++) {
		beacon_or_sensor.insert(coordinate_utils::coordinate_vector_to_string<int64_t>({signal_zones[i].sensor_x, signal_zones[i].sensor_y}));
		beacon_or_sensor.insert(coordinate_utils::coordinate_vector_to_string<int64_t>({signal_zones[i].beacon_x, signal_zones[i].beacon_y}));
	}
	for (int i=0; i<signal_zones.size(); i++) {
		SignalZone signalZone = signal_zones[i];
		int64_t x_margin = std::abs(signalZone.sensor_x-signalZone.beacon_x);
		int64_t y_margin = std::abs(signalZone.sensor_y-signalZone.beacon_y);

		int64_t radius = x_margin + y_margin + 1;

		int64_t dx = 0, dy = radius;

		bool cycle_started = false;

		while (true) {
			if (dx == 0 && dy == radius && cycle_started) {
				break;
			}

			int64_t x = dx + signalZone.sensor_x;
			int64_t y = dy + signalZone.sensor_y;

			std::string coordinate_string = coordinate_utils::coordinate_vector_to_string<int64_t>({x, y});
			if ( x >= 0 && x <= 4000000 && y >= 0 && y <= 4000000 && !beacon_or_sensor.contains(coordinate_string) && !checkIfNoBeacon(x, y, signal_zones)) {
				return x * 4000000 + y;
			}
 
			if (dx >= 0 && dy > 0) {
				dx++;
				dy--;
				cycle_started = true;
			}
			else if (dx > 0 && dy <= 0) {
				dx--;
				dy--;
			}
			else if (dx <= 0 && dy < 0) {
				dx--;
				dy++;
			}
			else if (dx < 0 && dy >= 0) {
				dx++;
				dy++;
			}
		}
	}
}

int main(int argc, char **argv) {
	if (argc < 2)
	{
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}

	int64_t min_x = INT64_MAX;
	int64_t max_x = INT64_MIN;
	std::vector<SignalZone> signal_zones;

	file_utils::process_lines(argv[1], [&](auto line) {
		auto tokens = string_utils::split_by_string(line, " ");
		auto raw_sensor_x = tokens[2].substr(0, tokens[2].length()-1);
		auto raw_sensor_y = tokens[3].substr(0, tokens[3].length()-1);;
		auto raw_beacon_x = tokens[8].substr(0, tokens[8].length()-1);;
		auto raw_beacon_y = tokens[9];
		
		std::string sensor_x_str = string_utils::split_by_string(raw_sensor_x, "=")[1];
		std::string sensor_y_str = string_utils::split_by_string(raw_sensor_y, "=")[1];
		std::string beacon_x_str = string_utils::split_by_string(raw_beacon_x, "=")[1];
		std::string beacon_y_str = string_utils::split_by_string(raw_beacon_y, "=")[1];

		int64_t sensor_x = string_utils::convert_string<int64_t>(sensor_x_str);
		int64_t sensor_y = string_utils::convert_string<int64_t>(sensor_y_str);
		int64_t beacon_x = string_utils::convert_string<int64_t>(beacon_x_str);
		int64_t beacon_y = string_utils::convert_string<int64_t>(beacon_y_str);

		int64_t x_margin = std::abs(sensor_x-beacon_x);
		int64_t y_margin = std::abs(sensor_y-beacon_y);

		int64_t radius = x_margin + y_margin;

		min_x = std::min(min_x, beacon_x);
		max_x = std::max(max_x, beacon_x);

		min_x = std::min(min_x, sensor_x-radius);
		max_x = std::max(max_x, sensor_x+radius);

		SignalZone signalZone;

		signalZone.sensor_x = sensor_x;
		signalZone.sensor_y = sensor_y;
		signalZone.beacon_x = beacon_x;
		signalZone.beacon_y = beacon_y;
		
		signal_zones.push_back(signalZone);
	});

	uint64_t count = 0;

	for (int64_t x=min_x; x<=max_x; x++) {
		if (checkIfNoBeacon(x, 2000000, signal_zones)) {
			count++;
		}
	}

	std::cout << count << std::endl;

	std::cout << part2(signal_zones) << std::endl;

	return 0;
}
