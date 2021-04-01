#include <pybind11/pybind11.h>

#include "../src/hamt/hamt.h"

namespace py = pybind11;

PYBIND11_MODULE(pyhamt, m) {
    py::class_<hamt::HAMT>(m, "HAMT").def(py::init<>()).def_readwrite("reader", &hamt::HAMT::reader_);

    py::class_<hamt::Reader>(m, "Reader").def(py::init<>()).def("read_reg_mesh", &hamt::Reader::ReadRegularMesh);
}
