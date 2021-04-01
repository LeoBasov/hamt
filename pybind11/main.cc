#include <pybind11/pybind11.h>

#include "../src/hamt/hamt.h"

namespace py = pybind11;

PYBIND11_MODULE(pyhamt, m) {
    py::class_<hamt::HAMT>(m, "HAMT")
        .def(py::init<>())
        .def_readwrite("reader", &hamt::HAMT::reader_)
        .def_readwrite("writer", &hamt::HAMT::writer_);

    py::class_<hamt::Reader>(m, "Reader").def(py::init<>()).def("read_reg_mesh", &hamt::Reader::ReadRegularMesh);

    py::class_<hamt::Writer> writer(m, "Writer");
    writer.def(py::init<>())
        .def("write", &hamt::Writer::Write)
        .def_property("config", &hamt::Writer::GetConfig, &hamt::Writer::SetConfig);

    py::class_<hamt::Writer::Config>(m, "Config")
        .def(py::init<>())
        .def_readwrite("mesh_type", &hamt::Writer::Config::mesh_type)
        .def_readwrite("file_format", &hamt::Writer::Config::file_format)
        .def_readwrite("frequency", &hamt::Writer::Config::frequency)
        .def_readwrite("file_name", &hamt::Writer::Config::file_name)
        .def_readwrite("activated", &hamt::Writer::Config::activated);

    py::enum_<hamt::Writer::MeshType>(writer, "MeshType").value("REGULAR", hamt::Writer::REGULAR).export_values();

    py::enum_<hamt::Writer::FileFormat>(writer, "FileFormat")
        .value("VTK", hamt::Writer::VTK)
        .value("CSV", hamt::Writer::CSV)
        .export_values();
}
