#include <pybind11/pybind11.h>

#include "../src/hamt/hamt.h"

namespace py = pybind11;

PYBIND11_MODULE(pyhamt, m) {
    py::class_<hamt::HAMT>(m, "HAMT")
        .def(py::init<>())
        .def_readwrite("reader", &hamt::HAMT::reader_)
        .def_readwrite("writer", &hamt::HAMT::writer_)
        .def_readwrite("solver", &hamt::HAMT::solver_);

    py::class_<hamt::Solver> solver(m, "Solver");
    solver.def(py::init<>())
        .def("execute", &hamt::Solver::Execute)
        .def_property("config", &hamt::Solver::GetConfig, &hamt::Solver::SetConfig);

    py::enum_<hamt::Solver::SolverType>(solver, "SolverType")
        .value("HOMOGENEOUS", hamt::Solver::HOMOGENEOUS)
        .export_values();

    py::enum_<hamt::Solver::CoordinatesType>(solver, "CoordinatesType")
        .value("CARTESIAN", hamt::Solver::CARTESIAN)
        .value("CYLINDER", hamt::Solver::CYLINDER)
        .export_values();

    py::enum_<hamt::Solver::MeshType>(solver, "MeshType").value("REGULAR", hamt::Solver::REGULAR).export_values();

    py::class_<hamt::Solver::Config>(m, "SolverConfig")
        .def(py::init<>())
        .def_readwrite("solver_type", &hamt::Solver::Config::solver_type)
        .def_readwrite("mesh_type", &hamt::Solver::Config::mesh_type)
        .def_readwrite("coord_type", &hamt::Solver::Config::coord_type)
        .def_readwrite("activate", &hamt::Solver::Config::activate);

    py::class_<hamt::Reader>(m, "Reader").def(py::init<>()).def("read_reg_mesh", &hamt::Reader::ReadRegularMesh);

    py::class_<hamt::Writer> writer(m, "Writer");
    writer.def(py::init<>())
        .def("write", &hamt::Writer::Write)
        .def_property("config", &hamt::Writer::GetConfig, &hamt::Writer::SetConfig);

    py::class_<hamt::Writer::Config>(m, "WriterConfig")
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
