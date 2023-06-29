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
    /* Initialization */
    net_by.init(net.get_head());
    do {
        size_t count{};
        int i = 0;
        do {
            /* Polling the node */
            auto list = net_by.hint()->send_request(i * number_of_devices_to_return, count);
            if (!list.empty())
                /* Adding read nodes */
                net_by.add(list);
            ++i;
        } while (i * number_of_devices_to_return < count);
    /* Switching the pointer */ 
    } while (net_by.next());
    net_by.print();
    return 0;
}
