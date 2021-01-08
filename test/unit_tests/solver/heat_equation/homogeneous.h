#pragma once

#include <gtest/gtest.h>

#include "../../../../src/io/gmsh/gmsh.h"
#include "../../../../src/mesh/mesh_algorithms.h"
#include "../../../../src/solver/heat_equation/homogeneous.h"

namespace hamt {
using namespace Eigen;

std::pair<MatrixXd, VectorXd> GetMeshPair() {
    const std::string file_name("../../../hamt/test/test_data/block_4_segments.msh");
    // const std::string file_name("./test/test_data/block_4_segments.msh");
    const gmsh::MSH2 msh2_mesh = gmsh::ReadMSH2(file_name);
    const Mesh2DRegular mesh = mesh_algorithms::MSH2ToMesh2DRegular(msh2_mesh);

    std::pair<MatrixXd, VectorXd> mat_b;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    return mat_b;
}

TEST(heat_equation_homogeneous, ConvertButtomLeft) { std::pair<MatrixXd, VectorXd> mat_b(GetMeshPair()); }

}  // namespace hamt
