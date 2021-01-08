#pragma once

#include <gtest/gtest.h>

#include "../../../../src/io/gmsh/gmsh.h"
#include "../../../../src/mesh/mesh_algorithms.h"
#include "../../../../src/solver/heat_equation/homogeneous.h"

namespace hamt {
using namespace Eigen;

Mesh2DRegular GetMesh() {
    // const std::string file_name("../../../hamt/test/test_data/block_4_segments.msh");
    const std::string file_name("./test/test_data/block_4_segments.msh");

    return mesh_algorithms::MSH2ToMesh2DRegular(gmsh::ReadMSH2(file_name));
}

TEST(heat_equation_homogeneous, ConvertButtomLeft) {
    Mesh2DRegular mesh(GetMesh());
    std::pair<MatrixXd, VectorXd> mat_b;
    const double left_buttom(7.0);
    const double buttom_left(13.0);

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("butom_left", Mesh2DRegular::NEUMANN);

    mesh.SetBoundaryValue("left_buttom", left_buttom);
    mesh.SetBoundaryValue("butom_left", buttom_left);

    heat_equation_homogeneous::ConvertButtomLeft(mat_b, mesh, 0);

    ASSERT_DOUBLE_EQ(mesh.dx_ * left_buttom - mesh.dy_ * buttom_left, mat_b.second(0));

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(0, 1));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(0, 5));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != 0) && (j != 1)) || ((i != 0) && (j != 5))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertButtomLeft(mat_b, mesh, 0);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(0, 0));
    ASSERT_DOUBLE_EQ(left_buttom, mat_b.second(0));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != 0) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != 0) && (j != 0)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("butom_left", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertButtomLeft(mat_b, mesh, 0);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(0, 0));
    ASSERT_DOUBLE_EQ(buttom_left, mat_b.second(0));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != 0) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != 0) && (j != 0)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }
}

}  // namespace hamt
