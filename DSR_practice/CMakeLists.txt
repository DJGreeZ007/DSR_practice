add_executable (DSR_practice "main.cpp" "map_parser.h" "map_parser.cpp" "libs/node_and_link.h" "libs/node_and_link.cpp" "network.h" "network.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DSR_practice PROPERTY CXX_STANDARD 20)
endif()
