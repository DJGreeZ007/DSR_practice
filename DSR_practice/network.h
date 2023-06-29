#ifndef NETWORK_H
#define NETWORK_H

/* Libs */
#include "map_parser.h"

/* C++ libs */
#include <vector>
#include <iostream> /* TEST */

namespace nw {

    enum network_error {
        NO_ERRORS,
        ERROR_EMPTY_ADDR_IS_CHECKED,        /* An empty address is checked */
        ERROR_SAME_NODE_WITH_DIFF_DATA      /* The same node with different data */
    };

    class Network {
    public:
        /* Сreating a graph (network model) from the values returned by map_parser */
        network_error init(const std::vector<mp::Node>& _nodes, const std::vector<mp::Link>& _links);
        /* TEST */
        void print () const{
            for (auto it : nodes) {
                std::cout << it->get_id() << std::endl;
            }
        }
        ~Network();
    private:
        network_error adding_nodes(const std::vector<mp::Node>& _nodes); /* Adding nodes */

        void clear_nodes();             /* Deleting all nodes */
        nal::Node* search_for_node_by_id(const std::string& _id) const;
        network_error сhecking_data_in_node(const nal::Node* const _node, const std::uint16_t& _addr, const nal::Nwk_type& _device_type) const;

        std::string label{};            /* Name ZC */
        nal::Node* head{};              /* Pointer to the coordinator */
        std::vector <nal::Node*> nodes; /* All nodes of the network */
    };
}
#endif /* NETWORK_H */

