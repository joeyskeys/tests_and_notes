find_package(Boost REQUIRED)
find_package(benchmark REQUIRED)

add_executable(introspection introspection.cpp)

target_include_directories(introspection PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(introspection benchmark::benchmark)