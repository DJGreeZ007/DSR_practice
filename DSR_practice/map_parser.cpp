﻿#include "map_parser.h"

/* C++ libs */
#include <limits>       /* Maximum value of variables */
#include <cmath>        /* Pow */
#include <string>       /* Stoul */
#include <fstream>      /* Ifstream */

using namespace mp;     /* Namespace of the Map_parser class */

/* Node */
mp::Node::Node(const std::string& _id, const std::uint16_t& _addr, const nal::Nwk_type& _device_type):
    id{ _id }, addr{ _addr }, device_type{ _device_type } {}

/* Link */
mp::Link::Link(const std::string& _from, const std::string& _to, const std::uint8_t& _lqi, nal::Nwk_relation _relation):
    from{ _from }, to{ _to }, lqi{ _lqi }, relation{ _relation } {}

/* Parser Class */
map_parser_error Map_parser::init(const std::string& _filename)
{
    map_parser_error code_error;           /* Getting the error code from auxiliary functions */

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
            clear_nodes_and_links();
            return ERROR_INCORRECT_DATA_IN_FILE;
        }

        std::vector<std::string> data_in_row;
        /* Reading data from a string */
        code_error = get_data_from_line(data_in_row, line);
        if (code_error > 0) {
            clear_nodes_and_links();
            return code_error;
        }

        /* From */
        std::string from{};
        if (data_in_row[0].substr(0, 4) != "SGW-" && data_in_row[0].substr(0, 3) != "zb.") {
            clear_nodes_and_links();
            return ERROR_ADDRESS_IN_FROM;
        }
        from = data_in_row[0];

        /* To */
        std::string to;
        if (data_in_row[1].substr(0, 3) != "zb.") {
            clear_nodes_and_links();
            return ERROR_ADDRESS_IN_TO;
        }
        to = data_in_row[1];

        /* Communication quality indication */
        std::uint8_t lqi;
        code_error = get_lqi_from_string(lqi, data_in_row[2]);
        if (code_error > 0) {
            clear_nodes_and_links();
            return code_error;
        }

        /* Network address */
        std::uint16_t addr;
        code_error = get_addr_from_string(addr, data_in_row[3]);
        if (code_error > 0) {
            clear_nodes_and_links();
            return code_error;
        }

        /* Type */
        nal::Nwk_type device_type = get_type_from_string(data_in_row[4]);
        
        /* Relationship */
        nal::Nwk_relation relation = get_relationship_from_string(data_in_row[5]);

        /* Adding a Node */
        nodes.push_back(Node{ to, addr, device_type });

        /* Adding a Link */
        links.push_back(Link{ from, to, lqi, relation });
    }
    return NO_ERRORS;
}

/* Getters */
const std::vector<Node>& mp::Map_parser::get_nodes() const
{
    return nodes;
}

const std::vector<Link>& mp::Map_parser::get_links() const
{
    return links;
}

void mp::Map_parser::clear_nodes_and_links()
{
    nodes.clear();
    links.clear();
}

/* Auxiliary functions */
nal::Nwk_type mp::get_type_from_string(const std::string& _type)
{
    if (_type == "ZR") {
        return nal::Nwk_type::NWKMAP_DEV_ROUTER;
    }
    else if (_type == "ZC") {
        return nal::Nwk_type::NWKMAP_DEV_COORDINATOR;
    }
    else if (_type == "ZED") {
        return nal::Nwk_type::NWKMAP_DEV_END_DEVICE;
    }
    return nal::Nwk_type::NWKMAP_DEV_UNKNOWN;
}

nal::Nwk_relation mp::get_relationship_from_string(const std::string& _realationship)
{
    if (_realationship == "Sibling") {
        return nal::Nwk_relation::NWKMAP_RELATION_SIBLING;
    }
    else if (_realationship == "Parent") {
        return nal::Nwk_relation::NWKMAP_RELATION_PARENT;
    }
    else if (_realationship == "Child") {
        return nal::Nwk_relation::NWKMAP_RELATION_CHILD;
    }
    else if (_realationship == "Prev_child") {
        return nal::Nwk_relation::NWKMAP_RELATION_PREV_CHILD;
    }
    return nal::Nwk_relation::NWKMAP_RELATION_UNKNOWN;
}

map_parser_error mp::get_data_from_line(std::vector<std::string>& _data_in_row, std::string _line) {
    /* Delete all space */
    _line.erase(std::remove_if(begin(_line), end(_line), [](char symb) {return symb == ' '; }), end(_line));

    const size_t number_of_columns = 6;                            /* The amount of data in a row */
    for (size_t i = 0; i < number_of_columns; ++i) {

        /* Check symb | */
        if (std::find(begin(_line), end(_line), '|') != begin(_line)) {
            _data_in_row.clear();
            return ERROR_INCORRECT_DATA_IN_FILE;
        }
        /* Delete first | */
        _line.erase(0, 1);

        /* Get element */
        auto iter = std::find(begin(_line), end(_line), '|');
        if (iter == end(_line)) {
            _data_in_row.clear();
            return ERROR_INCORRECT_DATA_IN_FILE;
        }
        std::string data = _line.substr(0, iter - begin(_line));
        if (data.empty()) {
            _data_in_row.clear();
            return ERROR_EMPTY_FIELD;
        }
        _data_in_row.push_back(data);

        /* Delete saved data in the line */
        _line.erase(begin(_line), iter);
    }

    /* Check last symb | */
    if (std::find(begin(_line), end(_line), '|') == end(_line)) {
        _data_in_row.clear();
        return ERROR_INCORRECT_DATA_IN_FILE;
    }
    return NO_ERRORS;
}

map_parser_error mp::get_lqi_from_string(std::uint8_t& _lqi, const std::string& _str_lqi)
{
    try {
        unsigned long tmp = std::stoul(_str_lqi);
        if (tmp > std::numeric_limits<std::uint8_t>::max() || tmp <= 0) {
            throw std::invalid_argument("Communication quality indication error");
        }
        _lqi = tmp;
    }
    catch (...) {
        return ERROR_COMMUNICATION_QUALITY_INDICATION;
    }
    return NO_ERRORS;
}

map_parser_error mp::get_addr_from_string(std::uint16_t& _addr, const std::string& _str_addr)
{
    try {
        size_t pos{};                                       /* Position in the address bar */
        const int base = 16;                                /* Hexadecimal base */
        unsigned long tmp = std::stoul(_str_addr, &pos, base);
        if (tmp > std::numeric_limits<std::uint16_t>::max()) {
            throw std::invalid_argument("Invalid address");
        }
        _addr = tmp;
    }
    catch (...) {
        return ERROR_INVALID_ADDRESS;
    }
    return NO_ERRORS;
}


