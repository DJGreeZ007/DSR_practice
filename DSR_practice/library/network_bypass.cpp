#include "network_bypass.h"
#include "dot_file_generator.h"
using namespace nwbp;



std::string nwbp::Network_bypass::hint(uint32_t& out_start_idx)
{
    out_start_idx = 0;
    if (idx_cur_node == std::numeric_limits<size_t>::max()) {
        if (!label.empty()) {
            out_start_idx = iterator_per_neighbor_for_head;
            return label;
        }
        return std::string{};
    }
    else if (idx_cur_node >= nodes.size()) {
        return std::string{};
    }
    else {
        out_start_idx = iterators_per_neighbor[nodes[idx_cur_node].id];
        return nodes[idx_cur_node].id;
    }
}

void nwbp::Network_bypass::add(const char* dev_id, uint8_t start_idx, uint8_t total_cnt, std::vector<inwmap::nwkmap_dev_t> devices)
{
    std::string id { dev_id };
    /* The current node */
    bool is_head{ id.substr(0, 4) == "SGW-" };
    if (is_head && label.empty()) {
        /* Set label */
        label = id;
    }

    for (const inwmap::nwkmap_dev_t& dev_t_ptr : devices) {
        /* Add links */
        Link new_link{ id, dev_t_ptr.dev_id, dev_t_ptr.lqi, dev_t_ptr.relationship };
        /* Checking that there is no such link yet */
        auto it = std::find(begin(links), end(links), new_link);
        if (it == end(links)) {
            links.push_back(std::move(new_link));
        }

        /* Add nodes */
        /* Checking that there is no such node yet */
        auto node_itr = std::find_if(begin(nodes), end(nodes), [&dev_t_ptr](const Node& node) {
            return node.id == dev_t_ptr.dev_id;
            });

        if (node_itr == end(nodes)) {
            nodes.push_back(Node{ dev_t_ptr.dev_id, dev_t_ptr.nwk_addr, dev_t_ptr.device_type });
        }
    }

    size_t next_idx = start_idx + devices.size();
    if (is_head) {
        iterator_per_neighbor_for_head = next_idx;
    }
    else {
        iterators_per_neighbor[id] = next_idx;
    }
    /* It is necessary to move and there is something to move the iterator */
    if (next_idx >= total_cnt && !nodes.empty()) {
        /* 
        Protection against the fact that the user wants to add a new node
        without bypassing the coordinator yet
        */
        if (!is_head && idx_cur_node == std::numeric_limits<size_t>::max())
            return;

        ++idx_cur_node;
        while (idx_cur_node < nodes.size() && (nodes[idx_cur_node].device_type == inwmap::nwkmap_dev_type_t::COORDINATOR ||
                                               nodes[idx_cur_node].device_type == inwmap::nwkmap_dev_type_t::END_DEVICE)) {
            ++idx_cur_node;
        }
    }

}

void nwbp::Network_bypass::save_dot(const std::string& out_filename)
{
    dfg::converting_and_saving_to_dot_file(out_filename, nodes, links, label);
}


/* Node */
nwbp::Node::Node(const std::string& _id, const std::uint16_t& _addr, const inwmap::nwkmap_dev_type_t& _device_type):
    id{ _id }, addr{ _addr }, device_type{ _device_type } {}

bool nwbp::Link::operator==(const Link& _link)
{
    return from == _link.from && to == _link.to;
}

/* Link */
nwbp::Link::Link(const std::string& _from, const std::string& _to, const std::uint8_t& _lqi, const inwmap::nwkmap_relation_t& _relation):
    from{ _from }, to{ _to }, lqi{ _lqi }, relation{ _relation } {}
