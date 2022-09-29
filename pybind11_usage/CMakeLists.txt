find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

pybind11_add_module(usage usage.cpp)

target_include_directories(usage PRIVATE ${pybind11_INCLUDE_DIRS})
