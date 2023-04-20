#include <iostream>
#include <memory>
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

    virtual void print_info() const {
        std::cout << "This is cpp vec : " << arr[0] << ", " << arr[1]
            << ", " << arr[2] << std::endl;
    }
};

Vec vec_add(const Vec& v1, const Vec& v2) {
    Vec tmp;
    for (int i = 0; i < 3; i++)
        tmp.arr[i] = v1.arr[i] + v2.arr[i];
    return tmp;
}

void call_print(const Vec& v) {
    v.print_info();
}

class PyVec : public Vec {
public:
    using Vec::Vec;

    void print_info() const override {
        PYBIND11_OVERRIDE(
            void,
            Vec,
            print_info
        );
    }
};

class VecWrapper {
public:
    VecWrapper(Vec* const vp) : vec_ptr(vp) {}

    void print_info() const {
        vec_ptr->print_info();
    }

    Vec* vec_ptr;
};

PYBIND11_MODULE(usage, m) {
    m.doc() = "pybind11 usage test";

    py::class_<Vec, PyVec>(m, "Vec")
        .def(py::init<>())
        .def(py::init<const float, const float, const float>())
        .def("print_info", &Vec::print_info, "print info");

    m.def("vec_add", &vec_add, "a function that adds two vec")
     .def("call_print", &call_print, "call vec print info func");

    py::class_<VecWrapper>(m, "VecWrapper")
        .def(py::init<Vec* const>())
        .def("print_info", &VecWrapper::print_info, "print info");
}