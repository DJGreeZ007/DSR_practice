#include "node_and_link.h"

using namespace nal;


/* Node */

Node::Node() {};

Node::Node(std::string _id, std::uint16_t _addr, Nwk_type _device_type, std::string _label) :
    completed{ true }, id{ _id }, addr{ _addr }, device_type{ _device_type }, label{ _label } {}

bool nal::Node::operator==(const std::string& id) const
{
    return this->id == id;
}

/* Link */


