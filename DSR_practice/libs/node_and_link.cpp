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

nal::Node::Node(const std::string& _id, const std::uint16_t& _addr, const Nwk_type& _device_type):
    id{ _id }, addr{ _addr }, device_type{ _device_type } {}


/* Link */

std::string nal::Link::get_id() const
{
    return this->node->get_id();
}

Node* const nal::Link::get_node() const
{
    return node;
}

nal::Link::Link(Node* _node, const std::uint8_t _lqi, const Nwk_relation& _relation)
{
    this->node = _node;
    this->lqi = _lqi;
    this->relation = _relation;
}
