#include "pybind11.hpp"

void drawing_submodule(pybind11::module& module);

void drawing_module(pybind11::module& module) {
    drawing_submodule(module);
}
