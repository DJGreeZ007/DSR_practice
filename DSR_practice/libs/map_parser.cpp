#include "map_parser.h"

using namespace mp;

#include <iostream> // delete
#include <limits>

map_parser_error Map_parser::init(std::string filename)
{

	//open file
	std::ifstream file(filename);

	if(!file.is_open()) {
		return ERROR_FILE_OPENING; // Error opening the file
	}

	std::string line;

	//skipping header lines
	std::getline(file, line);
	if (!std::getline(file, line)) {
		return ERROR_READING_FILE_HEADER; // Error reading the file header
	}


	// parsing
	while (std::getline(file, line)) {
		if (line.size() != 102) {
			return ERROR_INCORRECT_DATA_IN_FILE;
		}

		// delete all space
		line.erase(std::remove_if(begin(line), end(line), [](char symb) {return symb == ' '; }), end(line));

		std::vector<std::string> data_in_rows;
		const size_t amount_of_data_in_row = 6; // the amount of data in a row
		for (size_t i = 0; i < amount_of_data_in_row; ++i) {

			// check symb |
			if (std::find(begin(line), end(line), '|') != begin(line)) {
				return ERROR_INCORRECT_DATA_IN_FILE;
			}
			// delete first |
			line.erase(0, 1);

			// get data
			auto iter = std::find(begin(line), end(line), '|');
			std::string data = line.substr(0, iter-begin(line));
			data_in_rows.push_back(data);

			// delete saved data in the line
			line.erase(begin(line), iter);
		}

		// check last symb |
		if (std::find(begin(line), end(line), '|') == end(line)) {
			return ERROR_INCORRECT_DATA_IN_FILE;
		}

		std::string from = data_in_rows[0];
		std::string to = data_in_rows[1];

		// Communication quality indication
		std::uint8_t lqi;
		try {
			unsigned long tmp = std::stoul(data_in_rows[2]);
			if (tmp > UCHAR_MAX || tmp <= 0) {
				throw std::invalid_argument("Communication quality indication error");
			}
			lqi = tmp;
		}
		catch (const std::invalid_argument& ia) {
			return ERROR_COMMUNICATION_QUALITY_INDICATION;
		}

		// Network address
		std::uint16_t addr;
		try {
			convert_hex_string_to_uint(data_in_rows[3]);
			/*unsigned long tmp = std::stoul(data_in_rows[3]);
			std::cout << tmp;*/
			/*if (tmp > UCHAR_MAX || tmp <= 0) {
				throw std::invalid_argument("Communication quality indication error");
			}
			lqi = tmp;*/
		}
		catch (...) {
			return ERROR_COMMUNICATION_QUALITY_INDICATION;
		}

	}

	file.close();

	return NO_ERRORS;
}

uint64_t mp::convert_hex_string_to_uint(const std::string& str_hex)
{
	std::string hex = str_hex;
	if (hex.size() >= 2) {
		hex.erase(0, 2); //removing uppercase characters
		std::uint64_t result{};
		for (int i = hex.size() - 1; i >= 0; --i) {
			int value;
			switch (hex[i])
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				value = hex[i] - '0';
				break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
				value = hex[i] - 'a' + 10;
				break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
				value = hex[i] - 'A' + 10;
				break;
			default:
				throw std::invalid_argument("Invalid hex number");
			}
			result += value * std::pow(16, hex.size() - i - 1);
		}
		return result;
	}
	else {
		throw std::invalid_argument("Invalid hex number");
	}
}
