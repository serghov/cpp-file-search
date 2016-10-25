{
  "targets": [
    {
      "target_name": "node_native_search",
      "defines": [
        "V8_DEPRECATION_WARNINGS=1"
      ],
      "sources": [
        "node_native_search.cpp",
        "cpp_file_search.cpp",
        "cpp_file_search.h"
      ],

      "include_dirs": [
        "/usr/include/boost"
      ],
      "libraries": [
        "/usr/lib/x86_64-linux-gnu/libboost_system.so",
        "/usr/lib/x86_64-linux-gnu/libboost_filesystem.so",
        "/usr/lib/x86_64-linux-gnu/libboost_regex.so"
      ],
      "cflags_cc!": [
        "-fno-rtti",
        "-fno-exceptions"
      ],
      "cflags!": [
        "-std=c++11",
        "-fno-exceptions"
      ]
    }
  ]
}