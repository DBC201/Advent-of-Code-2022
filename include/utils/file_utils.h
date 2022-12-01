#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <fstream>
#include <vector>
#include <filesystem>
#include <iostream>

namespace utils::file_utils {
	/**
	* @param file_path path to file to be read
	* @param container the container data type to contain parsed lines
	* @param lambda a lambda function that takes two arguments, line as string and container (container should be taken as reference)
	*/
	void process_lines(std::string file_path, auto& container, auto lambda) {
		std::string line;
		std::fstream file;
		file.open(file_path, std::fstream::in);
		if (!file.is_open()) {
			std::cerr << "Unable to open " + file_path << std::endl;
			exit(EXIT_FAILURE);
		}
		while (std::getline(file, line)) {
			lambda(line, container);
		}
		file.close();
	}

	/*
	* @param file_path path to file to be read
	* @param lambda takes line and returns parsed data to be added to final vector
	* @returns vector of given template type
	*/
	template <typename token>
	std::vector<token> get_lines(std::string file_path, auto lambda) {
		std::vector<token> return_val;
		std::string line;
		std::fstream file;
		file.open(file_path, std::fstream::in);
		if (!file.is_open()) {
			std::cerr << "Unable to open " + file_path << std::endl;
			exit(EXIT_FAILURE);
		}
		while (std::getline(file, line)) {
			return_val.push_back(lambda(line));
		}
		file.close();
		return return_val;
	}

	std::string get_current_directory() {
		std::filesystem::path cwd = std::filesystem::current_path();
		return cwd.string();
	}
} // utils::file_utils

#endif // FILE_UTILS_H
