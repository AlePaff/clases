cmake_minimum_required(VERSION 2.6)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic")

set(CMAKE_BUILD_TYPE "Release")

project(ctypes)

add_executable(simple-grep main.c simple_grep.c)
add_library(simplegrep SHARED simple_grep.c)

FILE(GLOB PY_FILES "python/*.py")

install(FILES ${PY_FILES} DESTINATION ${CMAKE_BINARY_DIR})
