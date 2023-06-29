#include "network.h"

using namespace nw;

network_error nw::Network::init(const std::vector<mp::Node>& _nodes, const std::vector<mp::Link>& _links)
{

    network_error code_error;
    code_error = adding_nodes(_nodes);
    if (code_error > 0) {
        return code_error;
    }



    return NO_ERRORS;
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
