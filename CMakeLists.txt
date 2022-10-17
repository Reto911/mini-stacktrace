cmake_minimum_required(VERSION 3.23)
project(mini_stacktrace)

set(CMAKE_CXX_STANDARD 20)

add_executable(mini_stacktrace main.cpp include/mini-stacktrace/StacktraceLinux.h)

include_directories(include)