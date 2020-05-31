cmake_minimum_required(VERSION 2.8.11)

project(libuv-demo)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ggdb -std=c++11")

add_executable(00-hello-world 00-hello-world.cpp)
add_subdirectory(01-echo-server)

target_link_libraries(00-hello-world uv)
