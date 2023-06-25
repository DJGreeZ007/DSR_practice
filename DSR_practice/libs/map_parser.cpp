#include "map_parser.h"

using namespace mp;

#include <iostream> //delete
map_parser_error Map_parser::init(std::string filename)
{

	//open file
	std::ifstream file(filename);

	if(!file.is_open()) {
		return ERROR_FILE_OPENING; //Error opening the file
	}

	std::string line;

	//skipping header lines
	std::getline(file, line);
	if (!std::getline(file, line)) {
		return ERROR_READING_FILE_HEADER; //Error reading the file header
	}


	//parsing
	while (std::getline(file, line)) {
		if (line.size() != 102) {
			return ERROR_INCORRECT_DATA_IN_FILE;
		}

		//delete all space
		line.erase(std::remove_if(begin(line), end(line), [](char symb) {return symb == ' '; }), end(line));

		std::vector<std::string> data_in_rows;
		const size_t amount_of_data_in_row = 6; //the amount of data in a row
		for (size_t i = 0; i < amount_of_data_in_row; ++i) {

			//check symb |
			if (std::find(begin(line), end(line), '|') != begin(line)) {
				return ERROR_INCORRECT_DATA_IN_FILE;
			}
			//delete first |
			line.erase(0, 1);

			//get data
			auto iter = std::find(begin(line), end(line), '|');
			std::string data = line.substr(0, iter-begin(line));
			data_in_rows.push_back(data);

			//delete saved data in the line
			line.erase(begin(line), iter);
		}

		//todo 
		//convert data to the desired format

		for (auto it : data_in_rows) {
			std::cout << it << " : ";
		}
		std::cout << std::endl;
	}

	file.close();

	return NO_ERRORS;
}
