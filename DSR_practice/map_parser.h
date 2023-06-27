#ifndef MAP_PARSER_H
#define MAP_PARSER_H

/* Libs */
#include "libs/node_and_link.h"

/* C++ libs */
#include <vector>
#include <fstream>
#include <iostream> /* tmp */

using namespace nal;                                         /* Node and Link classes */

namespace mp {

    /* Map_parser error */
    enum map_parser_error {
        NO_ERRORS,
        ERROR_FILE_OPENING,                                  /* Error opening the file */
        ERROR_READING_FILE_HEADER,                           /* Error reading the file header */
        ERROR_INCORRECT_DATA_IN_FILE,                        /* Incorrect data in the file */
        ERROR_ADDRESS_IN_FROM,                               /* Address error in from */
        ERROR_ADDRESS_IN_TO,                                 /* Address error in to */
        ERROR_COMMUNICATION_QUALITY_INDICATION,              /* Communication quality indication error */
        ERROR_INVALID_ADDRESS,                               /* Invalid address */
        ERROR_INCORRECT_LINKS                                /* Incorrect links */
    };

    nal::Nwk_type get_type_from_string(const std::string& _type);

    nal::Nwk_relation get_relationship_from_string(const std::string& _realationship);

    class Map_parser {
    public:
        map_parser_error init(const std::string& _filename); /* Creating a graph from data in a file */

        ~Map_parser() {
            delete head;
            for (auto& it : nodes) {
                delete it;
            }
        }
        /* tmp ======================================================================== */
        void print() {
            std::cout << head->get_id() << " : " << head->get_label() << std::endl;
            for (const Link& link : head->get_links()) {
                std::cout << "      " << link.get_id() << std::endl;
            }
            for (auto& it : nodes) {
                std::cout << it->get_id() << std::endl;
                for (const Link& link : it->get_links()) {
                    std::cout << "      " << link.get_id() << std::endl;
                }
            }
        }
        /* ============================================================================ */
    private:
        Node* head{};                                        /* Reference to the main element, i.e. ZC */
        std::vector <Node*> nodes{};                         /* List of all nodes. Head is not included in the list */
        
        Node* find(const std::string& _id);                  /* Searching for an item in the list */
    };

    //uint64_t convert_hex_string_to_uint(const std::string& str_hex);
}

#endif /* MAP_PARSER_H */