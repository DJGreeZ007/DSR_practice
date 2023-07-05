#ifndef DOT_FILE_GENERATOR_H
#define DOT_FILE_GENERATOR_H

/* Libs */
#include "network_bypass.h"

/* C++ libs */
#include <string>

namespace dfg {
    void converting_and_saving_to_dot_file(const std::string& _out_filename, const std::vector<nwbp::Node>& _nodes,
                                           const std::vector<nwbp::Link>& _links, const std::string& _label);
    std::string converting_data_to_dot(const nwbp::Node& _node, const std::string& _label);
    std::string converting_data_to_dot(const std::vector<nwbp::Node>& _nodes, const nwbp::Link& _link);
}

#endif /* DOT_FILE_GENERATOR_H */