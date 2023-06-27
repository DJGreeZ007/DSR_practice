#include "map_parser.h"
#include <iostream>
#include <fstream>

int main()
{
    mp::Map_parser map;
    std::cout << map.init("test.txt") << std::endl;
    return 0;
}
