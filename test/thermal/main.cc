#include <iostream>

#include "../../src/io/gmsh/gmsh.h"
#include "../../src/io/vtk/unstructured_grid.h"
#include "../../src/mesh/mesh_algorithms.h"
#include "../../src/solver/heat_equation.h"

using namespace hamt;
using namespace Eigen;

int main(int, char **) {
    const std::string file_name("../../../hamt/examples/cartesia_two_block/block.msh"), file_name_out("./test.vtu");
    const gmsh::MSH2 msh2_mesh = gmsh::ReadMSH2(file_name);
    Mesh2DRegular mesh = mesh_algorithms::MSH2ToMesh2DRegular(msh2_mesh);
    std::pair<MatrixXd, VectorXd> mat_b;
    std::pair<std::string, std::vector<double>> poinst_data{"temeprature", std::vector<double>(mesh.nodes_.size())};

    // sides
    mesh.SetBoundaryType("buttom", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryValue("buttom", 300);

    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryValue("right_buttom", 0);

    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryValue("left_buttom", 0);

    mesh.SetBoundaryType("left_top", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryValue("left_top", 0);

    mesh.SetBoundaryType("top", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryValue("top", 100);

    mesh.SetBoundaryType("right_top", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryValue("right_top", 0);

    // surfaces
    mesh.SetSurfaceThermalConductivity("top_surf", 50);
    mesh.SetSurfaceThermalConductivity("buttom_surf", 150);

    mat_b = heat_equation::homogeneous::ConvertMesh2dRegularCartesian(mesh);
    VectorXd x = mat_b.first.colPivHouseholderQr().solve(mat_b.second);

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        poinst_data.second.at(i) = x(i);
    }

    vtk::unstructured_grid::WriteMesh2DRegular(mesh, file_name_out, {poinst_data});

    std::cout << "DONE" << std::endl;

    return 0;
}
