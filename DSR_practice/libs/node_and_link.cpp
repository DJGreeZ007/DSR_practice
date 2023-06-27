#include "node_and_link.h"

using namespace nal;


/* Node */

bool nal::Node::get_completed_node() const
{
    return completed_node;
}

bool nal::Node::get_label_is_installed() const
{
    return label_is_installed;
}

std::string nal::Node::get_id() const
{
    return id;
}

std::string nal::Node::get_label() const
{
    return label;
}

std::vector<Link> nal::Node::get_links() const
{
    return links;
}

void nal::Node::set_node(const std::string& _id, const std::uint16_t& _addr, const Nwk_type& _device_type)
{
    this->id = _id;
    this->addr = _addr;
    this->device_type = _device_type;
    this->completed_node = true;
}

void nal::Node::set_label(const std::string& _label)
{
    this->label = _label;
    this->label_is_installed = true;
}

bool nal::Node::add_links(const Link& _link)
{
    auto it = std::find(begin(links), end(links), _link);
    if (it == end(links)) {
        links.push_back(_link);
        return true;
    }
    return false;
}

nal::Node::Node() {};

nal::Node::Node(const std::string& _id) : id{ _id } {};

nal::Node::Node(const std::string& _id, const std::uint16_t& _addr, const Nwk_type& _device_type) :
    completed_node{ true }, id{ _id }, addr{ _addr }, device_type{ _device_type } {}

nal::Node::~Node()
{
}

bool nal::Node::operator==(const std::string& _id) const
{
    return this->id == _id;
}

/* Link */

std::string nal::Link::get_id() const
{
    return this->node->get_id();
}

nal::Link::Link(Node* _node, const std::uint8_t _lqi, const Nwk_relation& _relation)
{
    this->node = _node;
    this->lqi = _lqi;
    this->relation = _relation;
}

nal::Link::~Link()
{
    node = nullptr;
}

bool nal::Link::operator==(const Link& _link)
{
    return this->node == _link.node;
}
