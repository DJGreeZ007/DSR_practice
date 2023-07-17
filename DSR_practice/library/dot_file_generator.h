#ifndef DOT_FILE_GENERATOR_H
#define DOT_FILE_GENERATOR_H

/* Libs */
#include "network_bypass.h"

/* C++ libs */
#include <string>

namespace dfg { /* Dot File Generator */

    /* Possible styles for nodes */
    const std::string_view style_filled = "filled";
    const std::string_view style_dashed = "dashed";
    const std::string_view style_solid = "solid";
    const std::string_view style_dotted = "dotted";
               
    /* Possible colors for nodes */
    const std::string_view color_grey = "grey";
    const std::string_view color_black = "black";
    const std::string_view color_red = "red";

    /* Possible styles for links */
    const std::string_view link_style_solid = "solid";
    const std::string_view link_style_dashed = "dashed";
    const std::string_view link_style_dotted = "dotten";
    const std::string_view link_style_bold = "bold";

    /* Node style */
    const std::string_view style_COORDINATOR = style_filled;
    const std::string_view style_END_DEVICE = style_dashed;
    const std::string_view style_ROUTER = style_solid;
    const std::string_view style_UNKNOWN = style_dotted;

    /* Node color */
    const std::string_view color_COORDINATOR = color_grey;
    const std::string_view color_END_DEVICE = color_black;
    const std::string_view color_ROUTER = color_black;
    const std::string_view color_UNKNOWN = color_red;

    /* Style links */
    const std::string_view link_style_PARENT = link_style_solid;
    const std::string_view link_style_CHILD = link_style_dashed;
    const std::string_view link_style_SIBLING = link_style_dotted;
    const std::string_view link_style_PREV_CHILD = link_style_dashed;
    const std::string_view link_style_UNKNOWN = link_style_bold;

    /**
     * @brief Output in dot format to a file of the list of nodes and links
     * 
     * @param[in] _out_filename - The name of the file to save the DOT representation of the topology map to.
     * @see INwkMap::save_dot()
     * @param[in] _nodes - List of passed nodes.
     * @param[in] _links - List of passed links.
     * @param[in] _label - Label of the capital node
    */
    void converting_and_saving_to_dot_file(const std::string& _out_filename, const std::vector<nwbp::Node>& _nodes,
                                           const std::vector<nwbp::Link>& _links, const std::string& _label);
    /**
     * @brief Converts the node to a dot format string.
     *
     * @param[in] _node - Node for translation
     * @param[in] _coordinator_label - The label of the title link. 
     * If the field is an empty string, then _node is not a header node.
     * 
     * @return A string in dot format.
    */
    std::string node_to_dot(const nwbp::Node& _node, const std::string& _coordinator_label);

    /**
     * @brief Converts the link to a dot format string.
     *
     * @param[in] _nodes - List of all passed nodes
     * @param[in] _link - Link for translation to dot
     * 
     * @return A string in dot format
    */
    std::string link_to_dot(const std::vector<nwbp::Node>& _nodes, const nwbp::Link& _link);
}

#endif /* DOT_FILE_GENERATOR_H */