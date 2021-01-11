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

    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("butom_left", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertButtomLeft(mat_b, mesh, 0);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(0, 0));
    ASSERT_DOUBLE_EQ(0.5 * (left_buttom + buttom_left), mat_b.second(0));

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

TEST(heat_equation_homogeneous, ConvertButtomRight) {
    Mesh2DRegular mesh(GetMesh());
    std::pair<MatrixXd, VectorXd> mat_b;
    const double right_buttom(7.0);
    const double buttom_right(13.0);
    const uint node_id(2);
    const uint u_i_jp(3);
    const uint u_im_j(1);

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::NEUMANN);

    mesh.SetBoundaryValue("right_buttom", right_buttom);
    mesh.SetBoundaryValue("butom_right", buttom_right);

    heat_equation_homogeneous::ConvertButtomRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(right_buttom, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertButtomRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(buttom_right, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertButtomRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(0.5 * (right_buttom + buttom_right), mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertButtomRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(mesh.dx_ * buttom_right + mesh.dy_ * right_buttom, mat_b.second(node_id));

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, u_i_jp));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_im_j));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != node_id) && (j != u_i_jp)) || ((i != node_id) && (j != u_im_j))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }
}

TEST(heat_equation_homogeneous, ConvertTopLeft) {
    Mesh2DRegular mesh(GetMesh());
    std::pair<MatrixXd, VectorXd> mat_b;
    const double left_top(7.0);
    const double top_left(13.0);
    const uint node_id(6);
    const uint u_i_jm(5);
    const uint u_ip_j(7);

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryType("left_top", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("top_left", Mesh2DRegular::NEUMANN);

    mesh.SetBoundaryValue("left_top", left_top);
    mesh.SetBoundaryValue("top_left", top_left);

    heat_equation_homogeneous::ConvertTopLeft(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(left_top, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("left_top", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("top_left", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertTopLeft(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(top_left, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("left_top", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("top_left", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertTopLeft(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(0.5 * (left_top + top_left), mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("left_top", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("top_left", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertTopLeft(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(mesh.dx_ * top_left + mesh.dy_ * left_top, mat_b.second(node_id));

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, u_ip_j));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_i_jm));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != node_id) && (j != u_ip_j)) || ((i != node_id) && (j != u_i_jm))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }
}

TEST(heat_equation_homogeneous, ConvertTopRight) {
    Mesh2DRegular mesh(GetMesh());
    std::pair<MatrixXd, VectorXd> mat_b;
    const double top_right(7.0);
    const double right_top(13.0);
    const uint node_id(8);
    const uint u_i_jm(3);
    const uint u_im_j(7);

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryType("top_right", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("right_top", Mesh2DRegular::NEUMANN);

    mesh.SetBoundaryValue("top_right", top_right);
    mesh.SetBoundaryValue("right_top", right_top);

    heat_equation_homogeneous::ConvertTopRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(top_right, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("top_right", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("right_top", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertTopRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(right_top, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("top_right", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("right_top", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertTopRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(0.5 * (top_right + right_top), mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("top_right", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("right_top", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertTopRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(mesh.dx_ * right_top - mesh.dy_ * top_right, mat_b.second(node_id));

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, u_i_jm));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_im_j));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != node_id) && (j != u_i_jm)) || ((i != node_id) && (j != u_im_j))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }
}

TEST(heat_equation_homogeneous, ConvertButtom) {
    Mesh2DRegular mesh(GetMesh());
    std::pair<MatrixXd, VectorXd> mat_b;
    const double butom_left(7.0);
    const double butom_right(13.0);
    const double surf_bl(15.0);
    const double surf_br(17.0);
    const uint node_id(1);
    const uint u_i_jp(4);
    const uint u_im_j(0);
    const uint u_ip_j(2);

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryValue("butom_left", butom_left);
    mesh.SetBoundaryValue("butom_right", butom_right);

    mesh.SetSurfaceThermalConductivity("surf_bl", surf_bl);
    mesh.SetSurfaceThermalConductivity("surf_br", surf_br);

    mesh.SetBoundaryType("butom_left", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertButtom(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(butom_left, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("butom_left", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertButtom(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(butom_right, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("butom_left", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertButtom(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(0.5 * (butom_left + butom_right), mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("butom_left", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertButtom(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(surf_br, mat_b.first(node_id, u_ip_j));
    ASSERT_DOUBLE_EQ(-(surf_bl + surf_br), mat_b.first(node_id, u_i_jp));
    ASSERT_DOUBLE_EQ(surf_bl, mat_b.first(node_id, u_im_j));

    ASSERT_DOUBLE_EQ(-(surf_bl + surf_br) * 0.5 * (butom_left + butom_right) * mesh.dy_, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != node_id) && (j != u_i_jp)) || ((i != node_id) && (j != u_im_j)) ||
                ((i != node_id) && (j != u_ip_j))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }
}

TEST(heat_equation_homogeneous, ConvertRight) {
    Mesh2DRegular mesh(GetMesh());
    std::pair<MatrixXd, VectorXd> mat_b;
    const double right_top(7.0);
    const double right_buttom(13.0);
    const double surf_tr(15.0);
    const double surf_br(17.0);
    const uint node_id(3);
    const uint u_i_jm(2);
    const uint u_i_jp(8);
    const uint u_im_j(4);

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryValue("right_top", right_top);
    mesh.SetBoundaryValue("right_buttom", right_buttom);

    mesh.SetSurfaceThermalConductivity("surf_tr", surf_tr);
    mesh.SetSurfaceThermalConductivity("surf_br", surf_br);

    mesh.SetBoundaryType("right_top", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(right_top, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("right_top", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(right_buttom, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("right_top", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(0.5 * (right_top + right_buttom), mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if ((i != node_id) && (j != node_id)) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("right_top", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertRight(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(surf_tr, mat_b.first(node_id, u_i_jp));
    ASSERT_DOUBLE_EQ(-(surf_br + surf_tr), mat_b.first(node_id, u_im_j));
    ASSERT_DOUBLE_EQ(surf_br, mat_b.first(node_id, u_i_jm));

    ASSERT_DOUBLE_EQ((surf_tr + surf_br) * 0.5 * (right_top + right_buttom) * mesh.dx_, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != node_id) && (j != u_i_jp)) || ((i != node_id) && (j != u_im_j)) ||
                ((i != node_id) && (j != u_i_jm))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }
}

}  // namespace hamt
