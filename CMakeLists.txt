cmake_minimum_required(VERSION 3.16)

project(cpp_benchmarks)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_subdirectory(Catch2)
link_libraries(Catch2WithMain)

add_executable(function_call src/function_call.cpp)
