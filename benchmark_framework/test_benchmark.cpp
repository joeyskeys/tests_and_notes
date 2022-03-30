#include <iostream>

#include <benchmark/benchmark.h>

static void bm_string_creation(benchmark::State& state) {
    for (auto _ : state) {
        std::string emp_string;
    }
}

BENCHMARK(bm_string_creation);

static void bm_string_copy(benchmark::State& state) {
    std::string x = "hello";
    for (auto _ : state)
        std::string copy(x);
}

BENCHMARK(bm_string_copy);

BENCHMARK_MAIN();