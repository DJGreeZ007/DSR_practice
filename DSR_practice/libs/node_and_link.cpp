#include "node_and_link.h"

using namespace nal;


/* Node */


std::string nal::Node::get_id() const
{
    return id;
}

std::uint16_t nal::Node::get_addr() const
{
    return addr;
}


Nwk_type nal::Node::get_type() const
{
    return device_type;
}

const std::vector<Link>& nal::Node::get_links() const
{
    return links;
}

std::vector<Link> nal::Node::send_request(const size_t& start_index, size_t& total_cnt) const
{
    total_cnt = links.size();
    if (start_index >= total_cnt) {
        return std::vector<Link>{};
    }
    return std::vector<Link>{begin(links) + start_index, begin(links) + std::min(start_index + number_of_devices_to_return, total_cnt)};
}

void nal::Node::add_link(const Link& link)
{
    links.push_back(link);
}

nal::Node::Node(const std::string& _id, const std::uint16_t& _addr, const Nwk_type& _device_type):
    id{ _id }, addr{ _addr }, device_type{ _device_type } {}


/* Link */

Node* const nal::Link::get_node() const
{
    return node;
}

std::uint8_t nal::Link::get_lqi() const
{
    return lqi;
}

Nwk_relation nal::Link::get_relation() const
{
    return relation;
}

nal::Link::Link(Node* _node, const std::uint8_t& _lqi, const Nwk_relation& _relation) :
    node{ _node }, lqi{ _lqi }, relation{ _relation } {}
