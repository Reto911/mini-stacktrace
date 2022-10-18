cmake_minimum_required(VERSION 3.23)
project(mini_stacktrace)
set(CMAKE_CXX_STANDARD 20)

add_executable(mini_stacktrace main.cpp include/mini-stacktrace/StacktraceLinux.hpp include/mini-stacktrace/Stacktrace.h include/mini-stacktrace/mini-stacktrace include/mini-stacktrace/StacktraceWindows.hpp)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(mini_stacktrace dbghelp)
endif()


include_directories(include)