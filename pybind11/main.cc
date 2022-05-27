#include <pybind11/pybind11.h>

#include "../src/hamt/hamt.h"

namespace py = pybind11;

void SetUpHAMT(::pybind11::module_ &m);
void SetUpSolver(::pybind11::module_ &m);
void SetUpReader(::pybind11::module_ &m);
void SetUpWriter(::pybind11::module_ &m);
void SetUpData(::pybind11::module_ &m);

PYBIND11_MODULE(pyhamt, m) {
    SetUpHAMT(m);
    SetUpSolver(m);
    SetUpReader(m);
    SetUpWriter(m);
    SetUpData(m);
}

void SetUpHAMT(::pybind11::module_ &m) {
    py::class_<hamt::HAMT>(m, "HAMT")
        .def(py::init<>())
        .def_readwrite("reader", &hamt::HAMT::reader_)
        .def_readwrite("writer", &hamt::HAMT::writer_)
        .def_readwrite("solver", &hamt::HAMT::solver_)
        .def_readonly("data", &hamt::HAMT::data_);
}

void SetUpSolver(::pybind11::module_ &m) {
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

    py::enum_<hamt::Solver::MeshType>(solver, "MeshType")
            .value("REGULAR", hamt::Solver::REGULAR)
            .value("TRIANGULAR", hamt::Solver::TRIANGULAR)
            .export_values();

    py::class_<hamt::Solver::Config>(m, "SolverConfig")
        .def(py::init<>())
        .def_readwrite("solver_type", &hamt::Solver::Config::solver_type)
        .def_readwrite("mesh_type", &hamt::Solver::Config::mesh_type)
        .def_readwrite("coord_type", &hamt::Solver::Config::coord_type);
}

void SetUpReader(::pybind11::module_ &m) {
    py::class_<hamt::Reader>(m, "Reader")
            .def(py::init<>())
            .def("read_reg_mesh", &hamt::Reader::ReadRegularMesh)
            .def("read_triangl_mesh", &hamt::Reader::ReadTriangularMesh);
}

void SetUpWriter(::pybind11::module_ &m) {
    py::class_<hamt::Writer> writer(m, "Writer");
    writer.def(py::init<>())
        .def("write", &hamt::Writer::Write, py::arg("iter") = 0)
        .def("get_config", &hamt::Writer::GetConfig)
        .def("set_config", &hamt::Writer::SetConfig);

    py::class_<hamt::Writer::Config>(m, "WriterConfig")
        .def(py::init<>())
        .def_readwrite("frequency", &hamt::Writer::Config::frequency)
        .def_readwrite("file_name", &hamt::Writer::Config::file_name)
        .def_readwrite("activated", &hamt::Writer::Config::activated);

    py::enum_<hamt::Writer::MeshType>(writer, "MeshType")
            .value("REGULAR", hamt::Writer::REGULAR)
            .value("TRIANGULAR", hamt::Writer::TRIANGULAR)
            .export_values();

    py::enum_<hamt::Writer::FileFormat>(writer, "FileFormat")
        .value("VTK", hamt::Writer::VTK)
        .value("CSV", hamt::Writer::CSV)
        .export_values();
}

void SetUpData(::pybind11::module_ &m) {
    //  to use for shared pointers
    py::class_<hamt::Data, std::shared_ptr<hamt::Data>>(m, "Data")
        .def(py::init<>())
        .def_readwrite("mesh2d_regular", &hamt::Data::mesh2d_regular_)
        .def_readwrite("mesh2d_triangular", &hamt::Data::mesh2d_triangular_);

    py::class_<hamt::Mesh2DRegular> mesh2d_regular(m, "Mesh2DRegular");
    mesh2d_regular.def(py::init<>());
    mesh2d_regular.def("set_boundary_type", &hamt::Mesh2DRegular::SetBoundaryType)
        .def("set_boundary_value", &hamt::Mesh2DRegular::SetBoundaryValue)
        .def("set_surface_thermal_conductivity", &hamt::Mesh2DRegular::SetSurfaceThermalConductivity)
        .def("clear", &hamt::Mesh2DRegular::Clear);

    py::enum_<hamt::Mesh2DRegular::BoundaryType>(mesh2d_regular, "BoundaryType")
        .value("NEUMANN", hamt::Mesh2DRegular::NEUMANN)
        .value("DIRICHLET", hamt::Mesh2DRegular::DIRICHLET)
        .value("RADIATION", hamt::Mesh2DRegular::RADIATION)
        .export_values();

    py::class_<hamt::Mesh2DTriangular> mesh2d_triangular(m, "Mesh2DTriangular");
    mesh2d_triangular.def(py::init<>())
        .def("set_boundary_type", &hamt::Mesh2DTriangular::SetBoundaryType)
        .def("set_boundary_value", &hamt::Mesh2DTriangular::SetBoundaryValue)
        .def("set_surface_thermal_conductivity", &hamt::Mesh2DTriangular::SetSurfaceThermalConductivity)
        .def("clear", &hamt::Mesh2DTriangular::Clear);

    py::enum_<hamt::Mesh2DTriangular::BoundaryType>(mesh2d_triangular, "BoundaryType")
        .value("NEUMANN", hamt::Mesh2DTriangular::NEUMANN)
        .value("DIRICHLET", hamt::Mesh2DTriangular::DIRICHLET)
        .value("RADIATION", hamt::Mesh2DTriangular::RADIATION)
        .export_values();

}
