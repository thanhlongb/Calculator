cmake_minimum_required(VERSION 3.15)
project(Calculator)

set(CMAKE_CXX_STANDARD 11)

add_executable(Calculator main.cpp Stack.cpp Stack.h Node.cpp Node.h Queue.cpp Queue.h)