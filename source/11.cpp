#include <iostream>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <queue>
#include <functional>
#include <unordered_map>
#include <algorithm>

namespace file_utils = utils::file_utils;
namespace string_utils = utils::string_utils;

struct Item
{
	uint64_t worry;
};

struct Monkey
{
	std::queue<Item> inventory;
	uint64_t inspection_count = 0;
	std::function<void(Item &)> inspect;
	uint64_t test_value;
	std::string monkey_id_to_throw_if_true;
	std::string monkey_id_to_throw_if_false;
};

std::queue<Item> parse_starting_items(auto tokens)
{
	std::queue<Item> items;
	for (int i = 2; i < tokens.size()-1; i++)
	{
		Item item;
		item.worry = string_utils::convert_string<uint64_t>(tokens[i].substr(0, tokens[i].length() - 1));
		items.push(item);
	}
	Item item;
	item.worry = string_utils::convert_string<uint64_t>(tokens[tokens.size()-1]);
	items.push(item);
	return items;
}

void set_inspection(Monkey *monkey, std::vector<std::string> tokens)
{
	auto operate = [](auto a, auto b, std::string token)
		{
			char symbol = token[0];
			switch (symbol)
			{
			case '+':
				return a + b;
			case '-':
				return a - b;
			case '*':
				return a * b;
			}
		};

	monkey->inspect = [&, tokens = std::move(tokens)](Item &item)
	{
		std::string lefthand = tokens[3];
		std::string righthand = tokens[5];
		std::string operand = tokens[4];
		bool lefthand_dynamic = lefthand == "old";
		bool righthand_dynamic = righthand == "old";

		if (lefthand_dynamic && righthand_dynamic)
		{
			item.worry = operate(item.worry, item.worry, operand);
		}
		else if (lefthand_dynamic)
		{
			item.worry = operate(item.worry, string_utils::convert_string<uint64_t>(righthand), operand);
		}
		else if (righthand_dynamic)
		{
			item.worry = operate(string_utils::convert_string<uint64_t>(lefthand), item.worry, operand);
		}
	};
}

void round(std::unordered_map<std::string, Monkey> &monkeys)
{
	for (auto &p : monkeys)
	{
		Monkey* monkey = &(p.second);
		while (!monkey->inventory.empty()) {
			auto item_to_inspect = monkey->inventory.front();
			monkey->inventory.pop();
			monkey->inspect(item_to_inspect);
			monkey->inspection_count++;
			item_to_inspect.worry /= 3;
			if (item_to_inspect.worry % monkey->test_value == 0)
			{
				monkeys.at(monkey->monkey_id_to_throw_if_true).inventory.push(item_to_inspect);
			}
			else
			{
				monkeys.at(monkey->monkey_id_to_throw_if_false).inventory.push(item_to_inspect);
			}
		}
	}
}

void round2(std::unordered_map<std::string, Monkey> &monkeys, uint64_t lcm)
{
	for (auto &p : monkeys)
	{
		Monkey* monkey = &(p.second);
		while (!monkey->inventory.empty()) {
			auto item_to_inspect = monkey->inventory.front();
			monkey->inventory.pop();
			monkey->inspect(item_to_inspect);
			monkey->inspection_count++;
			// item_to_inspect.worry /= 3;

			item_to_inspect.worry %= lcm;

			if (item_to_inspect.worry % monkey->test_value == 0)
			{
				monkeys.at(monkey->monkey_id_to_throw_if_true).inventory.push(item_to_inspect);
			}
			else
			{
				monkeys.at(monkey->monkey_id_to_throw_if_false).inventory.push(item_to_inspect);
			}
		}
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::unordered_map<std::string, Monkey> monkeys;
	Monkey *current_monkey;

	file_utils::process_lines(argv[1], [&](auto line)
							  {
		auto raw_tokens = string_utils::split_by_string(line, " ");
		std::vector<std::string> tokens;
		for (const auto& raw_token: raw_tokens) {
			if (raw_token.length() > 0) {
				tokens.push_back(raw_token);
			}
		}

		if (tokens.size() == 0) {
			return;
		}

		if (tokens[0] == "Monkey") {
			Monkey monkey;
			monkeys.insert({tokens[1].substr(0, tokens[1].length()-1), monkey});
			current_monkey = &(monkeys.at(tokens[1].substr(0, tokens[1].length()-1)));
		}
		else if (tokens[0] == "Starting") {
			current_monkey->inventory = parse_starting_items(tokens);
		}
		else if (tokens[0] == "Operation:") {
			set_inspection(current_monkey, tokens);
		}
		else if (tokens[0] == "Test:") {
			current_monkey->test_value = string_utils::convert_string<uint64_t>(tokens[3]);
		}
		else if (tokens[0] == "If" && tokens[1] == "true:") {
			current_monkey->monkey_id_to_throw_if_true = tokens[5];
		}
		else if (tokens[0] == "If" && tokens[1] == "false:") {
			current_monkey->monkey_id_to_throw_if_false = tokens[5];
		} });

	auto monkeys1 = monkeys;
	
	for (int i = 0; i < 20; i++)
	{
		round(monkeys1);
	}

	std::vector<uint64_t> values;

	for (const auto &p : monkeys1)
	{
		values.push_back(p.second.inspection_count);
	}

	std::sort(values.begin(), values.end(), [](auto a, auto b) {
		return a > b;
	});

	std::cout << values[0] * values[1] << std::endl;

	auto monkeys2 = monkeys;
	uint64_t lcm = 1;

	for (const auto& p: monkeys) {
		lcm *= p.second.test_value;
	}

	for (int i=0; i<10000; i++) {
		round2(monkeys2, lcm);
	}

	values.clear();

	for (const auto &p : monkeys2)
	{
		values.push_back(p.second.inspection_count);
	}

	std::sort(values.begin(), values.end(), [](auto a, auto b) {
		return a > b;
	});

	std::cout << values[0] * values[1] << std::endl;

	return 0;
}
