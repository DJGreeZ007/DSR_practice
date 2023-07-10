add_executable (DSR_practice 
                             "main.cpp" 
                             "map_parser.h" 
                             "map_parser.cpp" 
                             "node_and_link.h" 
                             "node_and_link.cpp" 
                             "network.h" 
                             "network.cpp"  
                             "library/network_bypass.h" 
                             "library/network_bypass.cpp"
                             "library/interface_nw_map.h"
                             "library/dot_file_generator.cpp"
                             "library/dot_file_generator.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DSR_practice PROPERTY CXX_STANDARD 20)
endif()
