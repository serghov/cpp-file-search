cmake_minimum_required(VERSION 3.6)
project(Rodin_File_Search)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp)

add_executable(Rodin_File_Search ${SOURCE_FILES})

target_link_libraries(Rodin_File_Search ${Boost_LIBRARIES})
