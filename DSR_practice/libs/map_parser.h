#ifndef MAP_PARSER_H
#define MAP_PARSER_H


//libs
#include "node_and_link.h"

//c++ libs
#include <vector>
#include <fstream>

using namespace nal;						//Node and Link classes

namespace mp {

	//map_parser error
	enum map_parser_error {
		NO_ERRORS,
		ERROR_FILE_OPENING,							//Error opening the file
		ERROR_READING_FILE_HEADER,					//Error reading the file header
		ERROR_INCORRECT_DATA_IN_FILE,				//Incorrect data in the file
		ERROR_COMMUNICATION_QUALITY_INDICATION,		//Communication quality indication error
		ERROR_INVALID_ADDRESS						//Invalid address
	};

	class Map_parser {
		Node* head{};						//Reference to the main element, i.e. ZC
		std::vector <Node*> nodes{};		//List of all nodes
	public:
		map_parser_error init(std::string filename);
	};

	uint64_t convert_hex_string_to_uint(const std::string& str_hex);
}

#endif //MAP_PARSER_H