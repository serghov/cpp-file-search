{
  "targets": [
    {
      "target_name": "nativeFileSearch",
      "defines": [
        "V8_DEPRECATION_WARNINGS=1"
      ],
      "sources": [
        "nativeFileSearch.cpp",
        "cppFileSearch.cpp",
        "cppFileSearch.h",
        "SearchWorker.cpp",
        "SearchWorker.h"
      ],
      "include_dirs": [
        "/usr/include/boost",
        "<!(node -e \"require('nan')\")"
      ],
      "libraries": [
        "/usr/lib/x86_64-linux-gnu/libboost_system.so",
        "/usr/lib/x86_64-linux-gnu/libboost_filesystem.so"
      ],
      "cflags_cc!": [
        "-fno-rtti",
        "-fno-exceptions"
      ],
      "cflags!": [
        "-Wall",
        "-std=c++11",
        "-fno-exceptions"
      ]
    }
  ]
}