#include "network.h"

using namespace nw;

network_error nw::Network::init(const std::vector<mp::Node>& _nodes, const std::vector<mp::Link>& _links)
{
    network_error code_error;

    /* Creating nodes */
    code_error = adding_nodes(_nodes);
    if (code_error > 0) {
        return code_error;
    }

    /* Creating links*/
    code_error = adding_links(_links);
    if (code_error > 0) {
        clear_nodes();
        return code_error;
    }

    return NO_ERRORS;
}

nal::Node* nw::Network::get_head()
{
    return head;
}

nal::Node* nw::Network::search_for_node_by_id(const std::string& _id) const
{
    auto it = std::find_if(begin(nodes), end(nodes), [&_id](nal::Node* _node) {
        return _node->get_id() == _id;
        });
    if (it == end(nodes)) {
        return nullptr;
    }
    return *it;
}

network_error nw::Network::сhecking_data_in_node(const nal::Node* const _node, const std::uint16_t& _addr, const nal::Nwk_type& _device_type) const
{
    if (!_node) {
        return ERROR_EMPTY_ADDR_IS_CHECKED;
    }

    if (_node->get_addr() != _addr || _node->get_type() != _device_type) {
        return ERROR_SAME_NODE_WITH_DIFF_DATA;
    }

    return NO_ERRORS;
}

void nw::Network::clear_nodes()
{
    for (auto& it : nodes) {
        delete it;
    }
    nodes.clear();
    head = nullptr;
}

nw::Network::~Network()
{
    clear_nodes();
}

network_error nw::Network::adding_nodes(const std::vector<mp::Node>& _nodes)
{
    network_error code_error;
    /* Creating all nodes */
    for (const mp::Node& it : _nodes) {
        nal::Node* node = search_for_node_by_id(it.id);
        if (node) {
            code_error = сhecking_data_in_node(node, it.addr, it.device_type);
            if (code_error > 0) {
                clear_nodes();
                return code_error;
            }
        }
        /* Creating a node */
        else {
            node = new nal::Node{ it.id, it.addr, it.device_type };
            nodes.push_back(node);
            /* Adding a head, if it hasn't been there yet */
            if (it.device_type == nal::Nwk_type::NWKMAP_DEV_COORDINATOR && !head) {
                head = node;
            }
        }
    }
    return NO_ERRORS;
}

network_error nw::Network::adding_links(const std::vector<mp::Link>& _links)
{
    network_error code_error;
    /* Creating all links */

    for (auto& it : _links) {
        /* If it's a coordinator */
        nal::Node* from{};
        if (it.from.substr(0, 4) == "SGW-") {
            /* Checking that the coordinator has been declared */
            if (!head) {
                return ERROR_COORDINATOR_WAS_NOT_ANNOUNCED;
            }
            from = head;
        }
        else {
            from = search_for_node_by_id(it.from);
            if (!from) {
                return ERROR_NODE_WAS_NOT_DECLARED;
            }
        }

        nal::Node* to = search_for_node_by_id(it.to);
        bool found{};
        code_error = search_and_verif_in_node_link(found, from, it.to, it.lqi, it.relation);
        if (code_error > 0) {
            return code_error;
        }

        if (found) {
            return ERROR_IDENTICAL_LINKS;
        }
        else {
            nal::Link link{to, it.lqi, it.relation};
            from->add_link(link);
        }
    }

    return NO_ERRORS;
}

network_error nw::Network::checking_and_installing_label(const std::string& _label) {
    if (label.empty()) {
        label = _label;
        return NO_ERRORS;
    }
    else if (label != _label){
        return ERROR_TWO_DIFFERENT_SWG_LABELS;
    }
    return NO_ERRORS;
}


network_error nw::search_and_verif_in_node_link(bool& found, const nal::Node* const _node, const std::string& _id, const std::uint8_t& _lqi, const nal::Nwk_relation& _relation)
{
    /*  Passage through all neighbors */
    for (auto& it : _node->get_links()) {
        /* Found a neighbor by id */
        if (it.get_node()->get_id() == _id) {
            found = true;
            /* Сhecking the data in the link */
            if (it.get_lqi() != _lqi || it.get_relation() != _relation) {
                return ERROR_TWO_CONNECTIONS;
            }
            return NO_ERRORS;
        }
    }
    found = false;
    return NO_ERRORS;
}
