#include "map_parser.h"

using namespace mp;

#include <iostream>   /* Delete */
#include <limits>     /* Maximum value of variables */
#include <cmath>      /* Pow */
#include <string>     /* Stoul */  

map_parser_error Map_parser::init(const std::string& _filename)
{

    /* Open file */
    std::ifstream file(_filename);

    if(!file.is_open()) {
        return ERROR_FILE_OPENING;         /* Error opening the file */
    }

    std::string line;                      /* Auxiliary string for reading data from a file */

    /* Skipping header lines */
    std::getline(file, line);
    if (!std::getline(file, line)) {
        return ERROR_READING_FILE_HEADER;  /* Error reading the file header */
    }


    /* Parsing */
    while (std::getline(file, line)) {
        if (line.size() != 102) {
            return ERROR_INCORRECT_DATA_IN_FILE;
        }

        /* Delete all space */
        line.erase(std::remove_if(begin(line), end(line), [](char symb) {return symb == ' '; }), end(line));

        std::vector<std::string> data_in_row;
        const size_t number_of_columns = 6; /* The amount of data in a row */
        for (size_t i = 0; i < number_of_columns; ++i) {

            /* Check symb | */
            if (std::find(begin(line), end(line), '|') != begin(line)) {
                return ERROR_INCORRECT_DATA_IN_FILE;
            }
            /* Delete first | */
            line.erase(0, 1);

            /* Get element */
            auto iter = std::find(begin(line), end(line), '|');
            std::string data = line.substr(0, iter-begin(line));
            data_in_row.push_back(data);

            /* Delete saved data in the line */
            line.erase(begin(line), iter);
        }

        /* Check last symb | */
        if (std::find(begin(line), end(line), '|') == end(line)) {
            return ERROR_INCORRECT_DATA_IN_FILE;
        }

        /* From */
        std::string from{};
        bool zc_flag = data_in_row[0].substr(0, 4) == "SGW-";           /* flag for tracking SWG- signatures */
        if (!(zc_flag) && data_in_row[0].substr(0, 3) != "zb.") {
            return ERROR_ADDRESS_IN_FROM;
        }
        from = data_in_row[0];

        /* To */
        std::string to;
        if (data_in_row[1].substr(0, 3) != "zb.") {
            return ERROR_ADDRESS_IN_TO;
        }
        to = data_in_row[1];

        /* Communication quality indication */
        std::uint8_t lqi;
        try {
            unsigned long tmp = std::stoul(data_in_row[2]);
            if (tmp > std::numeric_limits<std::uint8_t>::max() || tmp <= 0) {
                throw std::invalid_argument("Communication quality indication error");
            }
            lqi = tmp;
        }
        catch (...) {
            return ERROR_COMMUNICATION_QUALITY_INDICATION;
        }

        /* Network address */
        std::uint16_t addr;
        try {
            size_t pos{};        /* Position in the address bar */
            const int base = 16; /* Hexadecimal base */
            unsigned long tmp = std::stoul(data_in_row[3], &pos, base);
            if (tmp > std::numeric_limits<std::uint16_t>::max()) {
                throw std::invalid_argument("Invalid address");
            }
            addr = tmp;
        }
        catch (...) {
            return ERROR_INVALID_ADDRESS;
        }

        /* Type */
        nal::Nwk_type device_type;
        if (data_in_row[4] == "ZR") {
            device_type = nal::Nwk_type::NWKMAP_DEV_ROUTER;
        }
        else if (data_in_row[4] == "ZC") {
            device_type = nal::Nwk_type::NWKMAP_DEV_COORDINATOR;
        }
        else if (data_in_row[4] == "ZED") {
            device_type = nal::Nwk_type::NWKMAP_DEV_END_DEVICE;
        }
        else {
            device_type = nal::Nwk_type::NWKMAP_DEV_UNKNOWN;
        }
        
        /* Relationship */
        nal::Nwk_relation relation;
        if (data_in_row[5] == "Sibling") {
            relation = nal::Nwk_relation::NWKMAP_RELATION_SIBLING;
        }
        else if (data_in_row[5] == "Parent") {
            relation = nal::Nwk_relation::NWKMAP_RELATION_PARENT;
        }
        else if (data_in_row[5] == "Child") {
            relation = nal::Nwk_relation::NWKMAP_RELATION_CHILD;
        }
        else if (data_in_row[5] == "Prev_child") {
            relation = nal::Nwk_relation::NWKMAP_RELATION_PREV_CHILD;
        }
        else {
            relation = nal::Nwk_relation::NWKMAP_RELATION_UNKNOWN;
        }


        /* Right id */
        Node* right_dev{};
        if (device_type == nal::Nwk_type::NWKMAP_DEV_COORDINATOR) {

        }
        else {

        }


    }

    file.close();

    return NO_ERRORS;
}

Node* mp::Map_parser::find(const std::string& _id) {
    for (auto& it : nodes) {
        if (*it == _id) {
            return it;
        }
    }
    return nullptr;
}

//uint64_t mp::convert_hex_string_to_uint(const std::string& str_hex)
//{
//    std::string hex = str_hex;
//    if (hex.size() >= 2) {
//        hex.erase(0, 2); /* Removing uppercase characters */
//        std::uint64_t result{};
//        for (int i = hex.size() - 1; i >= 0; --i) {
//            int value;
//            switch (hex[i])
//            {
//            case '0':
//            case '1':
//            case '2':
//            case '3':
//            case '4':
//            case '5':
//            case '6':
//            case '7':
//            case '8':
//            case '9':
//                value = hex[i] - '0';
//                break;
//            case 'a':
//            case 'b':
//            case 'c':
//            case 'd':
//            case 'e':
//            case 'f':
//                value = hex[i] - 'a' + 10;
//                break;
//            case 'A':
//            case 'B':
//            case 'C':
//            case 'D':
//            case 'E':
//            case 'F':
//                value = hex[i] - 'A' + 10;
//                break;
//            default:
//                throw std::invalid_argument("Invalid hex number");
//            }
//            result += value * std::pow(16, hex.size() - i - 1);
//        }
//        return result;
//    }
//    else {
//        throw std::invalid_argument("Invalid hex number");
//    }
//}
