cmake_minimum_required(VERSION 3.12)

project(tests_and_notes LANGUAGES CXX C)

cmake_policy(SET CMP0074 NEW)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

if(WIN32)
    add_definitions(-DNOMINMAX)
endif(WIN32)

add_subdirectory(benchmark_framework)
add_subdirectory(cpp_self_introspection)
add_subdirectory(eigen_related)
add_subdirectory(pybind11_usage)