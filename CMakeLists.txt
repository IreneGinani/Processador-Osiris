cmake_minimum_required(VERSION 3.3)
project(osiris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lsystemc")
include_directories(/Users/gabriela/Documents/developer/systemc-2.3.1/include)
link_directories(/Users/gabriela/Documents/developer/systemc-2.3.1/lib)

include_directories(include)

set(SOURCE_FILES src/codigo.cpp src/main.cpp)

add_executable(osiris ${SOURCE_FILES})