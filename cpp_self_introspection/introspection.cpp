#include <cstddef>
#include <string>

#include <boost/hana.hpp>
#include <benchmark/benchmark.h>

using namespace std::literals;
namespace hana = boost::hana;

struct HanaStruct {
    BOOST_HANA_DEFINE_STRUCT(HanaStruct,
        (float, a),
        (double, b),
        (int, c)
    );
};

// We still get the advantage of compiler optimization when possible
// But in debug build this method is about 10x slower than the plain
// method, need to test on runtime string when optimization cannot be
// performed
void* get_hana_member(HanaStruct& hstruct, const std::string& dst) {
    void* ret = nullptr;
    hana::for_each(hana::accessors<HanaStruct>(), hana::fuse([&](auto name, auto accessor) {
        auto& tmp = accessor(hstruct);
        auto runtime_str = std::string(name.c_str());
        if (runtime_str == dst)
            ret = &tmp;
    }));
    return ret;
}

struct PlainStruct {
    float a;
    double b;
    int c;
};

// These two methods are basically the same, both syntax and performance
void* get_plain_member_with_comparison(PlainStruct& pstruct, const std::string& dst) {
    if (dst == "a")
        return &pstruct.a;
    else if (dst == "b")
        return &pstruct.b;
    else if (dst == "c")
        return &pstruct.c;
    return nullptr;
}

// offsetof macro is sensitive to memory layout in this test will crash
// on Debug build, and no performance advantage over the previous method
void* get_plain_member_with_offset(PlainStruct& pstruct, const std::string& dst) {
    if (dst == "a")
        return &pstruct + offsetof(PlainStruct, a);
    else if (dst == "b")
        return &pstruct + offsetof(PlainStruct, b);
    else if (dst == "c")
        return &pstruct + offsetof(PlainStruct, c);
    return nullptr;
}

static void bm_hana_introspection(benchmark::State& state) {
    HanaStruct hstruct;
    for (auto _ : state) {
        float* aptr = reinterpret_cast<float*>(get_hana_member(hstruct, "a"s));
        *aptr = 1.f;
        double* bptr = reinterpret_cast<double*>(get_hana_member(hstruct, "b"s));
        *bptr = 1.;
        int* cptr = reinterpret_cast<int*>(get_hana_member(hstruct, "c"s));
        *cptr = 1;
    }
}

BENCHMARK(bm_hana_introspection);

static void bm_plain_introspection_1(benchmark::State& state) {
    PlainStruct pstruct;
    for (auto _ : state) {
        float* aptr = reinterpret_cast<float*>(get_plain_member_with_comparison(pstruct, "a"s));
        *aptr = 1.f;
        double* bptr = reinterpret_cast<double*>(get_plain_member_with_comparison(pstruct, "b"s));
        *bptr= 1.;
        int* cptr = reinterpret_cast<int*>(get_plain_member_with_comparison(pstruct, "c"s));
        *cptr = 1;
    }
}

BENCHMARK(bm_plain_introspection_1);

static void bm_plain_introspection_2(benchmark::State& state) {
    PlainStruct pstruct;
    for (auto _ : state) {
        float* aptr = reinterpret_cast<float*>(get_plain_member_with_offset(pstruct, "a"s));
        *aptr = 1.f;
        double* bptr = reinterpret_cast<double*>(get_plain_member_with_offset(pstruct, "b"s));
        *bptr= 1.;
        int* cptr = reinterpret_cast<int*>(get_plain_member_with_offset(pstruct, "c"s));
        *cptr = 1;
    }
}

BENCHMARK(bm_plain_introspection_2);

BENCHMARK_MAIN();