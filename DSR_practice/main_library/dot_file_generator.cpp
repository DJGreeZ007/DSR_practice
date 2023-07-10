#include "dot_file_generator.h"

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
            file << converting_data_to_dot(node, _label);
            file << '\n';
        }

        /* Set links */
        file << "\n//Links\n\n";
        for (auto& link : _links) {
            file << converting_data_to_dot(_nodes, link);
            file << '\n';
        }
        file << "\n}";
        file.close();
    }
}

std::string dfg::converting_data_to_dot(const nwbp::Node& _node, const std::string& _label)
{
    /* Style */
    const std::string style_filled = "filled";
    const std::string style_solid = "solid";
    const std::string style_dashed = "dashed";
    const std::string style_dotted = "dotted";

    /* Color */
    const std::string color_grey = "grey";
    const std::string color_black = "black";
    const std::string color_red = "red";

    /* Node style */
    const std::string style_COORDINATOR = style_filled;
    const std::string style_END_DEVICE = style_dashed;
    const std::string style_ROUTER = style_solid;
    const std::string style_UNKNOWN = style_dotted;

    /* Node color */

    const std::string color_COORDINATOR = color_grey;
    const std::string color_END_DEVICE = color_black;
    const std::string color_ROUTER = color_black;
    const std::string color_UNKNOWN = color_red;

    std::string result;

    /* Inserting a style and color */

    result += "node [style=";

    switch (_node.device_type)
    {
    case nwkmap_dev_type_t::COORDINATOR:
        result += style_COORDINATOR + ", color=" + color_COORDINATOR;
        break;
    case nwkmap_dev_type_t::END_DEVICE:
        result += style_END_DEVICE + ", color=" + color_END_DEVICE;
        break;
    case nwkmap_dev_type_t::ROUTER:
        result += style_ROUTER + ", color=" + color_ROUTER;
        break;
    case nwkmap_dev_type_t::UNKNOWN:
        result += style_UNKNOWN + ", color=" + color_UNKNOWN;
        break;
    }

    result += "];\n    \"";

    /* Inserting a device_id */
    result += _node.id + "\"";
    if (_node.device_type == nwkmap_dev_type_t::COORDINATOR) {
        result += " [label = \"" + _label + "\"]";
    }
    result += ";\n";
    return result;
}

std::string dfg::converting_data_to_dot(const std::vector<nwbp::Node>& _nodes, const nwbp::Link& _link)
{
    /* Styles for links */
    const std::string style_solid = "solid";
    const std::string style_dashed = "dashed";
    const std::string style_dotted = "dotten";
    const std::string style_bold = "bold";

    /* Style */
    const std::string style_PARENT = style_solid;
    const std::string style_CHILD = style_dashed;
    const std::string style_SIBLING = style_dotted;
    const std::string style_PREV_CHILD = style_dashed;
    const std::string style_UNKNOWN = style_bold;

    std::string result{};
    result += "    \"";
    if (_link.from.substr(0, 4) == "SGW-") {
        auto it = std::find_if(begin(_nodes), end(_nodes), [](const nwbp::Node& node) {
            return node.device_type == nwkmap_dev_type_t::COORDINATOR;
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
    case nwkmap_relation_t::PARENT:
        result += style_PARENT;
        break;
    case nwkmap_relation_t::CHILD:
        result += style_CHILD;
        break;
    case nwkmap_relation_t::PREV_CHILD:
        result += style_PREV_CHILD;
        break;
    case nwkmap_relation_t::SIBLING:
        result += style_SIBLING;
        break;
    case nwkmap_relation_t::UNKNOWN:
        result += style_UNKNOWN;
        break;
    }
    result += "];";
    return result;
}

