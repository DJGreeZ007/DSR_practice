#include "map_parser.h"
#include "network.h"
#include "library/network_bypass.h"
#include <iostream>

std::vector<nwkmap_dev_t> converting_link_to_dev_t(std::vector<nal::Link>& _links);

int main()
{
    mp::Map_parser map_p{};
    size_t error_code = map_p.init("withSubChild.txt");
    if (!error_code) {
        std::cout << "The file has been read successfully\n";
    }
    else {
        std::cout << "Error reading the file. Error code " << error_code << '\n';
        return 1;
    }

    nw::Network net{};
    error_code = net.init(map_p.get_nodes(), map_p.get_links());
    if (!error_code) {
        std::cout << "Successful creation of a network model\n";
    }
    else {
        std::cout << "The network has not been created. Error code " << error_code << '\n';
        return 1;
    }
    net.print();


    nwbp::Network_bypass net_by{};
    size_t out_idx{};
    uint32_t start_idx{};
    bool found{};
    std::string id1 = net_by.hint(start_idx);
    std::vector < nal::Link > links = net.get_neighbors(net.get_head()->get_id(), 0, out_idx, found);
    std::vector < nwkmap_dev_t > devices = converting_link_to_dev_t(links);
    /* Initial neighbors of head */
    net_by.add(net.get_label().c_str(), 0, out_idx, devices);

    std::string id = net_by.hint(start_idx);
    while (!id.empty()) {
        bool found;
        std::vector < nal::Link > links = net.get_neighbors(id, start_idx, out_idx, found);
        std::vector < nwkmap_dev_t > devices = converting_link_to_dev_t(links);
        net_by.add(id.c_str(), start_idx, out_idx, devices);
        id = net_by.hint(start_idx);
    }

    net_by.save_dot("output.dot");
    return 0;
}

std::vector<nwkmap_dev_t> converting_link_to_dev_t(std::vector<nal::Link>& _links) {
    std::vector <nwkmap_dev_t> result{};
    for (auto& _link : _links) {
        nwkmap_relation_t relation_t{};
        switch (_link.get_relation()) {
        case nal::Nwk_relation::NWKMAP_RELATION_CHILD:
            relation_t = nwkmap_relation_t::CHILD;
            break;
        case nal::Nwk_relation::NWKMAP_RELATION_PARENT:
            relation_t = nwkmap_relation_t::PARENT;
            break;
        case nal::Nwk_relation::NWKMAP_RELATION_PREV_CHILD:
            relation_t = nwkmap_relation_t::PREV_CHILD;
            break;
        case nal::Nwk_relation::NWKMAP_RELATION_SIBLING:
            relation_t = nwkmap_relation_t::SIBLING;
            break;
        case nal::Nwk_relation::NWKMAP_RELATION_UNKNOWN:
            relation_t = nwkmap_relation_t::UNKNOWN;
            break;
        }
        nwkmap_dev_type_t dev_t{};
        switch (_link.get_node()->get_type()) {
        case nal::Nwk_type::NWKMAP_DEV_COORDINATOR:
            dev_t = nwkmap_dev_type_t::COORDINATOR;
            break;
        case nal::Nwk_type::NWKMAP_DEV_END_DEVICE:
            dev_t = nwkmap_dev_type_t::END_DEVICE;
            break;
        case nal::Nwk_type::NWKMAP_DEV_ROUTER:
            dev_t = nwkmap_dev_type_t::ROUTER;
            break;
        case nal::Nwk_type::NWKMAP_DEV_UNKNOWN:
            dev_t = nwkmap_dev_type_t::UNKNOWN;
            break;
        }
        result.push_back(nwkmap_dev_t{ _link.get_node()->get_id(), _link.get_lqi(), _link.get_node()->get_addr(), relation_t, dev_t });
    }
    return result;
}