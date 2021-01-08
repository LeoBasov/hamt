#pragma once

#include <gtest/gtest.h>

#include "../../../../src/io/gmsh/gmsh.h"
#include "../../../../src/mesh/mesh_algorithms.h"
#include "../../../../src/solver/heat_equation/homogeneous.h"

namespace hamt {
using namespace Eigen;

Mesh2DRegular GetMesh() {
    const std::string file_name("../../../hamt/test/test_data/block_4_segments.msh");
    // const std::string file_name("./test/test_data/block_4_segments.msh");

    return mesh_algorithms::MSH2ToMesh2DRegular(gmsh::ReadMSH2(file_name));
}

TEST(heat_equation_homogeneous, ConvertButtomLeft) {
    Mesh2DRegular mesh(GetMesh());
    std::pair<MatrixXd, VectorXd> mat_b;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());
}

}  // namespace hamt
