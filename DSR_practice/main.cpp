#include "map_parser.h"
#include "network.h"
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
    return 0;
}
