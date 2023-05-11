#ifndef DAY7_H
#define DAY7_H

#include <00.h>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <utils/file_utils.h>
#include <utils/string_utils.h>

using solutions::day_0::Day0;
using utils::file_utils::process_lines;
using utils::string_utils::convert_string;
using utils::string_utils::split_by_string;

namespace solutions::day_7
{
	const std::string day_id = "07";
	

	class Day7 : public Day0
	{
	public:
		Day7(std::string filepath) : Day0(filepath)
		{
			std::string current_path = "";
			std::string parent_directory = "";
			bool ls_flag = false;
			process_lines(filepath, [&](auto line)
						  {
				auto tokens = split_by_string(line, " ");
				if (tokens[0] == "$") {
					ls_flag = false;
					if (tokens[1] == "cd" && tokens[2] == "..") {
						current_path = go_up(current_path);
						parent_directory = current_path;
					}
					else if (tokens[1] == "cd") {
						current_path = go_down(current_path, tokens[2]);
						parent_directory = current_path;
					}
					else if (tokens[1] == "ls") {
						ls_flag = true;
					}
				} else if (ls_flag && convert_string<uint64_t>(tokens[0]) > 0) {
					auto size = convert_string<uint64_t>(tokens[0]);
					auto filename = go_down(current_path, tokens[1]);
					add_file(parent_directory, filename, size);
				}
				else if (ls_flag && tokens[0] == "dir") {
					auto filename =  go_down(current_path, tokens[1]);
					add_file(parent_directory, filename, 0);					
				} });

				calculate_dirsizes();
		}

		void print_filesystem()
		{
			for (const auto &p : filesystem)
			{
				std::cout << p.first << std::endl;
				for (const auto &f : p.second)
				{
					std::cout << "\t" << f << std::endl;
				}
			}
		}

		auto part1()
		{
			uint64_t sum = 0;
			for (const auto& d: directory_sizes) {
				//std::cout << d.first << " " << d.second << std::endl;
				if (d.second <= 100000) {
					sum += d.second;
				}
			}
			// print_filesystem();
			return sum;
		};

		auto part2()
		{
			uint64_t max_size = 70000000;
			uint64_t required_size = 30000000;
			uint64_t curr_size = directory_sizes["/"];
			uint64_t empty_space = max_size - curr_size;
			uint64_t min_to_be_deleted = required_size - empty_space;
			std::pair<std::string, uint64_t> min_deletable = {"", UINT64_MAX};
			for (const auto& d: directory_sizes) {
				if (d.second > min_to_be_deleted && d.second < min_deletable.second) {
					min_deletable = d;
				}
			}
			
			return min_deletable.second;
		};

	private:
		std::unordered_map<std::string, std::unordered_set<std::string>> filesystem;
		std::unordered_map<std::string, uint64_t> file_sizes;
		std::unordered_map<std::string, uint64_t> directory_sizes;

		std::string full_path(std::vector<std::string> &tokens)
		{
			if (!tokens.size())
			{
				return "/";
			}
			std::string res = "";
			for (const auto &t : tokens)
			{
				res += "/" + t;
			}
			return res;
		}

		std::string go_up(std::string &curr)
		{
			auto tokens = split_by_string(curr, "/");
			tokens.erase(tokens.begin());
			tokens.pop_back();
			return full_path(tokens);
		}

		std::string go_down(std::string &curr, auto &next)
		{
			if (next == "/")
			{
				return "/";
			}

			if (curr == "/")
			{
				return "/" + next;
			}

			return curr + "/" + next;
		}

		void add_file(std::string &parent_directory, std::string &file, uint64_t size)
		{
			if (filesystem.contains(parent_directory))
			{
				filesystem[parent_directory].insert(file);
			}
			else
			{
				std::unordered_set<std::string> s;
				s.insert(file);
				filesystem.insert({parent_directory, s});
			}

			if (file_sizes.contains(file))
			{
				file_sizes[file] = size;
			}
			else
			{
				file_sizes.insert({file, size});
			}
		}

		void increment_dirsize(std::string path, uint64_t size)
		{
			while (path != "/") {
				if (directory_sizes.contains(path)) {
					directory_sizes[path] += size;
				}
				else {
					directory_sizes.insert({path, size});
				}
				path = go_up(path);
			}

			if (directory_sizes.contains("/")) {
				directory_sizes["/"] += size;
			}
			else {
				directory_sizes.insert({"/", size});
			}
		}

		void calculate_dirsizes() {
			for (const auto& p: filesystem) {
				for (const auto& f: p.second) {
					increment_dirsize(p.first, file_sizes[f]);
				}
			}
		}
	};
} // solutions::day_7

#endif // DAY7_H
