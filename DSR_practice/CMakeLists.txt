add_executable (DSR_practice 
                             "main.cpp" 
                             "map_parser.cpp" 
                             "node_and_link.cpp" 
                             "network.cpp"  
                             "library/network_bypass.cpp"
                             "library/dot_file_generator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DSR_practice PROPERTY CXX_STANDARD 20)
endif()
