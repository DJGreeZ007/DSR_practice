#include "map_parser.h"
#include "network.h"
#include "network_bypass.h"
#include <iostream>

int main()
{
    mp::Map_parser map_p{};
    std::cout << map_p.init("withChild.txt") << std::endl;

    /*for (auto& it : map_p.get_nodes()) {
        std::cout << it.id << " " << it.addr << std::endl;
    }
    std::cout << std::endl;
    for (auto& it : map_p.get_links()) {
        std::cout << it.from << " " << it.to << " " << it.lqi << std::endl;
    }

    std::cout << "++++++++++++++++++++++++++++++++" << std::endl;*/

    nw::Network net{};
    std::cout << net.init(map_p.get_nodes(), map_p.get_links()) << std::endl;
    net.print();

    /*if (net.search_for_node_by_id("zxcvb")) {
        std::cout << "Found" << std::endl;
    }
    else {
        std::cout << "Not found" << std::endl;
    }*/

    static const size_t number_of_devices_to_return = 2;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    nwbp::Network_bypass net_by{};
    std::vector<nwkmap_dev_t> devices1 {
        nwkmap_dev_t{ "zb.646519001044ef54", 180, 0xd201, nwkmap_relation_t::SIBLING, nwkmap_dev_type_t::ROUTER },
        nwkmap_dev_t{ "zb.7e8b1302008d1500", 190, 0x0001, nwkmap_relation_t::CHILD, nwkmap_dev_type_t::END_DEVICE }
    };
    std::vector<nwkmap_dev_t> devices3 {
        nwkmap_dev_t{ "zb.d27a51cdc036cef4", 201, 0x0, nwkmap_relation_t::PARENT, nwkmap_dev_type_t::COORDINATOR }
    };
    uint32_t out_idx{};
    std::cout << net_by.hint(out_idx);
    net_by.add("SGW-02a004d310aa", 0, 2, devices1);
    net_by.print();
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << net_by.hint(out_idx);

    net_by.add("zb.646519001044ef54", out_idx, 1, devices3);
    net_by.print();
    std::cout << net_by.hint(out_idx);

    net_by.save_dot("input.dot");
    /* Initialization */
    return 0;
}
