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
    inline void add_animal(std::shared_ptr<Animal>& a) {
        animals.push_back(a);
    }

    void make_noises() const {
        tbb::global_control global_limit(tbb::global_control::max_allowed_parallelism, 4);

        tbb::parallel_for(tbb::blocked_range<size_t>(0, animals.size()),
            [&](const tbb::blocked_range<size_t>& r) {
                for (int t = r.begin(); t != r.end(); ++t) {
                    animals[t]->make_noise();
                }
            });
    }

    std::vector<std::shared_ptr<Animal>> animals;
};

PYBIND11_MODULE(with_tbb, m) {
    m.doc() = "pybind11 with tbb test";

    py::class_<Animal, PyAnimal>(m, "Animal")
        .def(py::init<>())
        .def("make_noise", &Animal::make_noise, "make some noise");

    py::class_<Zoo>(m, "Zoo")
        .def(py::init<>())
        .def("make_noises", &Zoo::make_noises, "the multithread call");
}