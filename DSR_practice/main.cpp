#include "map_parser.h"
#include <iostream>

int main()
{
    mp::Map_parser map_p{};
    map_p.init("withChild.txt");
    for (auto& it : map_p.get_nodes()) {
        std::cout << it.id << " " << it.addr << std::endl;
    }
    std::cout << std::endl;
    for (auto& it : map_p.get_links()) {
        std::cout << it.from << " " << it.to << " " << it.lqi << std::endl;
    }
    return 0;
}
