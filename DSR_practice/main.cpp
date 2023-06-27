#include "map_parser.h"
#include <iostream>
#include <fstream>

int main()
{
    mp::Map_parser map;
    std::cout << map.init("withChild.txt") << std::endl;
    map.print();
    return 0;
}
