{
  "targets": [
    {
      "target_name": "native-search",
      "defines": [
        "V8_DEPRECATION_WARNINGS=1"
      ],
      "sources": [
        "nativeSearch.cpp",
        "cppFileSearch.cpp",
        "cppFileSearch.h",
        "SearchWorker.cpp",
        "SearchWorker.h"
      ],
      "include_dirs": [
        "/usr/include/boost",
        "/usr/local/include",
        "<!(node -e \"require('nan')\")"
      ],
      "cflags_cc!": [
        "-fno-rtti",
        "-fno-exceptions"
      ],
      "cflags!": [
        "-std=c++11",
        "-fno-exceptions"
      ],
      "conditions": [
        [
          "OS==\"mac\"",
          {
            "xcode_settings": {
              "MACOSX_DEPLOYMENT_TARGET": "10.9",
              "CLANG_CXX_LIBRARY": "libc++",
              "GCC_ENABLE_CPP_RTTI": "YES",
              "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
            },
            "libraries": [
              "/usr/local/lib/libboost_system.dylib",
              "/usr/local/lib/libboost_filesystem.dylib"
            ]
          }
        ],
        [
          "OS==\"linux\"",
          {
            "libraries": [
              "/usr/lib/x86_64-linux-gnu/libboost_system.so",
              "/usr/lib/x86_64-linux-gnu/libboost_filesystem.so"
            ]
          }
        ]
      ]
    }
  ]
}