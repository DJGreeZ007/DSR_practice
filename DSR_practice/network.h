#ifndef NETWORK_H
#define NETWORK_H

/* Libs */
#include "map_parser.h"

/* C++ libs */
#include <vector>
#include <iostream> /* TEST  Will be deleted*/

namespace nw {

    enum network_error {
        NO_ERRORS,
        ERROR_EMPTY_ADDR_IS_CHECKED,            /* An empty address is checked */
        ERROR_SAME_NODE_WITH_DIFF_DATA,         /* The same node with different data */
        ERROR_TWO_DIFFERENT_SWG_LABELS,         /* Two different SWG labels */
        ERROR_COORDINATOR_WAS_NOT_ANNOUNCED,    /* The coordinator was not announced */
        ERROR_NODE_WAS_NOT_DECLARED,            /* The node was not declared */
        ERROR_TWO_CONNECTIONS,                  /* Two connections */
        ERROR_IDENTICAL_LINKS                   /* Identical links */
    };

    class Network {
    public:
        /* Сreating a graph (network model) from the values returned by map_parser */
        network_error init(const std::vector<mp::Node>& _nodes, const std::vector<mp::Link>& _links);

        /* Getters */
        nal::Node* get_head();

        /* TEST  Will be deleted*/
        void print () const{
            for (auto it : nodes) {
                std::cout << it->get_id() << std::endl;
                for (auto itr : it->get_links()) {
                    std::cout << "     " << itr.get_node()->get_id() << std::endl;
                }
            }
        }
        /* ============================================================================ */
        ~Network();
    private:
        network_error adding_nodes(const std::vector<mp::Node>& _nodes);                /* Adding nodes */
        network_error adding_links(const std::vector<mp::Link>& _links);                /* Adding links */
        network_error checking_and_installing_label(const std::string& _label);         /* Checking and installing label */
        void clear_nodes();                                                             /* Deleting all nodes */
        nal::Node* search_for_node_by_id(const std::string& _id) const;
        network_error сhecking_data_in_node(const nal::Node* const _node, const std::uint16_t& _addr, const nal::Nwk_type& _device_type) const;

        std::string label{};                /* Name ZC */
        nal::Node* head{};                  /* Pointer to the coordinator */
        std::vector <nal::Node*> nodes;     /* All nodes of the network */
    };

    network_error search_and_verif_in_node_link(bool& found, const nal::Node* const _node, const std::string& _id, const std::uint8_t& _lqi,
                                                const nal::Nwk_relation& _relation);
}
#endif /* NETWORK_H */
