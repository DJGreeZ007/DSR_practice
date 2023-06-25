add_executable (DSR_practice "main.cpp"  "libs/map_parser.h" "libs/node_and_link.h" "libs/node_and_link.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DSR_practice PROPERTY CXX_STANDARD 20)
endif()
