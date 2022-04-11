#include <benchmark/benchmark.h>

static void bm_string_creation(benchmark::State& state) {
    for (auto _ : state)
        std::string empty_string;
}

BENCHMARK(bm_string_creation);

BENCHMARK_MAIN();
