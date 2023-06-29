#ifndef MAP_PARSER_H
#define MAP_PARSER_H

/* Libs */
#include "libs/node_and_link.h"

/* C++ libs */
#include <vector>

namespace mp {

    /* Map_parser error */
    enum map_parser_error {
        NO_ERRORS,
        ERROR_FILE_OPENING,                                             /* Error opening the file */
        ERROR_READING_FILE_HEADER,                                      /* Error reading the file header */
        ERROR_INCORRECT_DATA_IN_FILE,                                   /* Incorrect data in the file */
        ERROR_EMPTY_FIELD,                                              /* Empty field */
        ERROR_ADDRESS_IN_FROM,                                          /* Address error in from */
        ERROR_ADDRESS_IN_TO,                                            /* Address error in to */
        ERROR_COMMUNICATION_QUALITY_INDICATION,                         /* Communication quality indication error */
        ERROR_INVALID_ADDRESS,                                          /* Invalid address */
        ERROR_INCORRECT_LINKS                                           /* Incorrect links */
    };

    struct Node{
        std::string id{};                                               /* Name to display */
        std::uint16_t addr{};                                           /* Network address */
        nal::Nwk_type device_type{ nal::Nwk_type::NWKMAP_DEV_UNKNOWN };
        Node(const std::string& _id, const std::uint16_t& _addr, const nal::Nwk_type& _device_type);
    };

    struct Link {
        std::string from{};
        std::string to{};
        std::uint8_t lqi{};
        nal::Nwk_relation relation{ nal::Nwk_relation::NWKMAP_RELATION_UNKNOWN };
        Link(const std::string& _from, const std::string& _to, const std::uint8_t& _lqi, nal::Nwk_relation _relation);
    };

    class Map_parser {
    public:
        map_parser_error init(const std::string& _filename);    /* Creates lists of nodes and links */

        /* Getters */
        const std::vector<Node>& get_nodes() const;             /* Get a list of nodes */
        const std::vector<Link>& get_links() const;             /* Get a list of links */

    private:
        void clear_nodes_and_links();

        std::vector<Node> nodes{};                              /* The list of nodes */
        std::vector<Link> links{};                              /* The list if links */
    };

    /* Auxiliary functions */
    map_parser_error get_data_from_line(std::vector<std::string>& _data_in_row, std::string _line);
    nal::Nwk_type get_type_from_string(const std::string& _type);
    nal::Nwk_relation get_relationship_from_string(const std::string& _realationship);
    map_parser_error get_lqi_from_string(std::uint8_t& _lqi, const std::string& _str_lqi);
    map_parser_error get_addr_from_string(std::uint16_t& _addr, const std::string& _str_addr);
}

#endif /* MAP_PARSER_H */
