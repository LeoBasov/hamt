#include <iostream>

#include "../../src/io/gmsh/gmsh.h"
#include "../../src/io/vtk/unstructured_grid.h"
#include "../../src/mesh/mesh_algorithms.h"

using namespace hamt;

int main(int, char **) {
    const std::string file_name("../../../hamt/test/test_data/block.msh"), file_name_out("./test.vtu");
    const gmsh::MSH2 msh2_mesh = gmsh::ReadMSH2(file_name);
    const Mesh2DRegular mesh = mesh_algorithms::MSH2ToMesh2DRegular(msh2_mesh);

    vtk::unstructured_grid::WriteMesh2DRegular(mesh, file_name_out);

    std::cout << "DONE" << std::endl;

    return 0;
}
