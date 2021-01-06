#include <iostream>

#include "../../src/io/gmsh/gmsh.h"
#include "../../src/io/vtk/unstructured_grid.h"
#include "../../src/mesh/mesh_algorithms.h"

using namespace hamt;

int main(int, char **) {
    const std::string file_name("../../../hamt/test/test_data/block.msh"), file_name_out("./test.vtu");
    const gmsh::MSH2 msh2_mesh = gmsh::ReadMSH2(file_name);
    const Mesh2DRegular mesh = mesh_algorithms::MSH2ToMesh2DRegular(msh2_mesh);
    std::pair<std::string, std::vector<double>> poinst_data{"test_data", std::vector<double>(mesh.nodes_.size(), 10)};
    std::pair<std::string, std::vector<double>> poinst_data1{"test_1", std::vector<double>(mesh.nodes_.size())};

    for (uint i = 0; i < poinst_data1.second.size(); i++) {
        poinst_data1.second.at(i) = i;
    }

    vtk::unstructured_grid::WriteMesh2DRegular(mesh, file_name_out, {poinst_data, poinst_data1});

    std::cout << "DONE" << std::endl;

    return 0;
}
