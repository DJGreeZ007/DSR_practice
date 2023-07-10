#ifndef DOT_FILE_GENERATOR_H
#define DOT_FILE_GENERATOR_H

/* Libs */
#include "network_bypass.h"

/* C++ libs */
#include <string>

namespace dfg {

    /* Style */
    const std::string_view style_filled = "filled";
    const std::string_view style_dashed = "dashed";
    const std::string_view style_solid = "solid";
    const std::string_view style_dotted = "dotted";
               
    /* Color */
    const std::string_view color_grey = "grey";
    const std::string_view color_black = "black";
    const std::string_view color_red = "red";

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

    /* Styles for links */
    const std::string_view link_style_solid = "solid";
    const std::string_view link_style_dashed = "dashed";
    const std::string_view link_style_dotted = "dotten";
    const std::string_view link_style_bold = "bold";

    /* Style links */
    const std::string_view link_style_PARENT = link_style_solid;
    const std::string_view link_style_CHILD = link_style_dashed;
    const std::string_view link_style_SIBLING = link_style_dotted;
    const std::string_view link_style_PREV_CHILD = link_style_dashed;
    const std::string_view link_style_UNKNOWN = link_style_bold;


    void converting_and_saving_to_dot_file(const std::string& _out_filename, const std::vector<nwbp::Node>& _nodes,
                                           const std::vector<nwbp::Link>& _links, const std::string& _label);
    std::string node_to_dot(const nwbp::Node& _node, const std::string& _label);
    std::string link_to_dot(const std::vector<nwbp::Node>& _nodes, const nwbp::Link& _link);
}

#endif /* DOT_FILE_GENERATOR_H */