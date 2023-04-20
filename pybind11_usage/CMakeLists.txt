find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)
find_package(TBB REQUIRED)

pybind11_add_module(usage usage.cpp)
target_include_directories(usage PRIVATE ${pybind11_INCLUDE_DIRS})

pybind11_add_module(with_tbb with_tbb.cpp)
target_include_directories(with_tbb
    PRIVATE
        ${pybind11_INCLUDE_DIRS}
        ${TBB_INCLUDE_DIRS})
target_link_libraries(with_tbb
    PRIVATE
        ${TBB_LIBRARIES})