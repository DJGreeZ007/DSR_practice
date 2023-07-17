#include "dot_file_generator.h"
#include <fstream>

using namespace dfg;

void dfg::converting_and_saving_to_dot_file(const std::string& _out_filename, const std::vector<nwbp::Node>& _nodes,
                                            const std::vector<nwbp::Link>& _links, const std::string& _label)
{
    std::ofstream file(_out_filename);
    if (file.is_open()) {
        file << "digraph " << _out_filename.substr(0, _out_filename.find('.')) << " {\n\n";
        /* Set nodes */
        file << "//Nodes\n\n";
        for (auto& node : _nodes) {
            file << node_to_dot(node, _label);
            file << '\n';
        }

        /* Set links */
        file << "\n//Links\n\n";
        for (auto& link : _links) {
            file << link_to_dot(_nodes, link);
            file << '\n';
        }
        file << "\n}";
        file.close();
    }
}

std::string dfg::node_to_dot(const nwbp::Node& _node, const std::string& coordinator_label)
{
    std::string result;

    /* Inserting a style and color */

    result += "node [style=";

    switch (_node.device_type)
    {
    case inwmap::nwkmap_dev_type_t::COORDINATOR:
        result += style_COORDINATOR;
        result += ", color=";
        result += color_COORDINATOR;
        break;
    case inwmap::nwkmap_dev_type_t::END_DEVICE:
        result += style_END_DEVICE; 
        result += ", color=";
        result += color_END_DEVICE;
        break;
    case inwmap::nwkmap_dev_type_t::ROUTER:
        result += style_ROUTER;
        result += ", color=";
        result += color_ROUTER;
        break;
    case inwmap::nwkmap_dev_type_t::UNKNOWN:
        result += style_UNKNOWN;
        result += ", color=";
        result += color_UNKNOWN;
        break;
    }

    result += "];\n    \"";

    /* Inserting a device_id */
    result += _node.id + "\"";
    if (_node.device_type == inwmap::nwkmap_dev_type_t::COORDINATOR) {
        result += " [label = \"" + coordinator_label + "\"]";
    }
    result += ";\n";
    return result;
}

std::string dfg::link_to_dot(const std::vector<nwbp::Node>& _nodes, const nwbp::Link& _link)
{
    std::string result{};
    result += "    \"";
    if (_link.from.substr(0, 4) == "SGW-") {
        auto it = std::find_if(begin(_nodes), end(_nodes), [](const nwbp::Node& node) {
            return node.device_type == inwmap::nwkmap_dev_type_t::COORDINATOR;
            });
        if (it != end(_nodes)) {
            result += it->id;
        }
    }
    else {
        result += _link.from;
    }
    result += "\"  ->  \"" + _link.to + "\" [label=\"LQI=" + std::to_string(_link.lqi) + "\", style=";
    switch (_link.relation)
    {
    case inwmap::nwkmap_relation_t::PARENT:
        result += link_style_PARENT;
        break;
    case inwmap::nwkmap_relation_t::CHILD:
        result += link_style_CHILD;
        break;
    case inwmap::nwkmap_relation_t::PREV_CHILD:
        result += link_style_PREV_CHILD;
        break;
    case inwmap::nwkmap_relation_t::SIBLING:
        result += link_style_SIBLING;
        break;
    case inwmap::nwkmap_relation_t::UNKNOWN:
        result += link_style_UNKNOWN;
        break;
    }
    result += "];";
    return result;
}

