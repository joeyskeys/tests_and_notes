find_package(benchmark CONFIG REQUIRED)

add_executable(gbenchmark_test test_benchmark.cpp)

target_link_libraries(gbenchmark_test benchmark::benchmark)