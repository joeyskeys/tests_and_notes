#include <iostream>
#include <memory>
#include <pybind11/pybind11.h>
#include <tbb/tbb.h>

namespace py = pybind11;

struct Animal {
    Animal() {}

    virtual void make_noise() const {
        std::cout << "This is an animal" << std::endl;
    }
};

class PyAnimal : public Animal {
public:
    using Animal::Animal;

    void make_noise() const override {
        PYBIND11_OVERRIDE(
            void,
            Animal,
            make_noise
        );
    }
};

class Zoo {
public:
    Zoo(Animal* const a) : animal(a) {}

    void make_noises() const {
        std::cout << "in make noises function" << std::endl;
        tbb::global_control global_limit(tbb::global_control::max_allowed_parallelism, 4);

        tbb::parallel_for(tbb::blocked_range<size_t>(0, 16),
            [&](const tbb::blocked_range<size_t>& r) {
                for (int t = r.begin(); t != r.end(); ++t) {
                    std::cout << "about to call make noise in thread " << t << std::endl;
                    animal->make_noise();
                    std::cout << "finished python call" << std::endl;
                }
            });

        std::cout << "end of make noises" << std::endl;
    }

    Animal* animal;
};

PYBIND11_MODULE(with_tbb, m) {
    m.doc() = "pybind11 with tbb test";

    py::class_<Animal, PyAnimal>(m, "Animal")
        .def(py::init<>())
        .def("make_noise", //&Animal::make_noise,
            [](Animal& a) {
                py::gil_scoped_acquire acquire;
                a.make_noise();
            }, "make some noise");

    py::class_<Zoo>(m, "Zoo")
        .def(py::init<Animal* const>())
        .def("make_noises", //&Zoo::make_noises,
            [](Zoo& zoo) {
                py::gil_scoped_release release;
                zoo.make_noises();
            }, "the multithread call");
}