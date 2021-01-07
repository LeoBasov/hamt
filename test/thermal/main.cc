#include <iostream>

#include "../../src/io/gmsh/gmsh.h"
#include "../../src/io/vtk/unstructured_grid.h"
#include "../../src/mesh/mesh_algorithms.h"
#include "../../src/solver/heat_equation.h"

using namespace hamt;
using namespace Eigen;

int main(int, char **) {
    const std::string file_name("../../../hamt/test/test_data/block_fine.msh"), file_name_out("./test.vtu");
    const gmsh::MSH2 msh2_mesh = gmsh::ReadMSH2(file_name);
    Mesh2DRegular mesh = mesh_algorithms::MSH2ToMesh2DRegular(msh2_mesh);
    std::pair<MatrixXd, VectorXd> mat_b;
    std::pair<std::string, std::vector<double>> poinst_data{"temeprature", std::vector<double>(mesh.nodes_.size())};

    // sides
    mesh.SetBoundaryType("rs", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryValue("rs", 450);

    mesh.SetBoundaryType("rb", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryValue("rb", 400);

    mesh.SetBoundaryType("lb", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryValue("lb", 300);

    mesh.SetBoundaryType("tb", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryValue("tb", 0);

    mesh.SetBoundaryType("ts", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryValue("ts", 0);

    mesh.SetBoundaryType("bb", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryValue("bb", 0);

    mesh.SetBoundaryType("bs", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryValue("bs", 0);

    mat_b = heat_equation::homogeneous::ConvertMesh2dRegularCartesian(mesh);
    VectorXd x = mat_b.first.colPivHouseholderQr().solve(mat_b.second);

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        poinst_data.second.at(i) = x(i);
    }

    vtk::unstructured_grid::WriteMesh2DRegular(mesh, file_name_out, {poinst_data});

    std::cout << "DONE" << std::endl;

    return 0;
}
