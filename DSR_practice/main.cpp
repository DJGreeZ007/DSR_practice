#include "map_parser.h"
#include <iostream>
#include <fstream>
#include <algorithm> //tmp

int main()
{
    mp::Map_parser map;
    std::cout << map.init("withChild.txt") << std::endl;
    map.print();
    return 0;
}
