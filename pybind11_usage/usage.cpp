#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Vec {
    Vec() {
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 0;
    }

    Vec(const float a, const float b, const float c) {
        arr[0] = a;
        arr[1] = b;
        arr[2] = c;
    }

    float arr[3];
};

Vec vec_add(const Vec& v1, const Vec& v2) {
    Vec tmp;
    for (int i = 0; i < 3; i++)
        tmp.arr[i] = v1.arr[i] + v2.arr[i];
    return tmp;
}

PYBIND11_MODULE(usage, m) {
    m.doc() = "pybind11 usage test";

    py::class_<Vec>(m, "Vec")
        .def(py::init<>())
        .def(py::init<const float, const float, const float>());

    m.def("vec_add", &vec_add, "a function that adds two vec");
}