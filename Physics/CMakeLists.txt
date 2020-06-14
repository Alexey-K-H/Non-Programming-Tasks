cmake_minimum_required(VERSION 3.16)
project(Physics C)

set(CMAKE_C_STANDARD 11)

add_executable(Physics main.c)
target_link_libraries(Physics m)