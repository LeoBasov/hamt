#pragma once

#include <gtest/gtest.h>

#include "../../../../src/io/gmsh/gmsh.h"
#include "../../../../src/mesh/mesh_algorithms.h"
#include "../../../../src/solver/heat_equation/homogeneous.h"

#include "../../../../src/io/vtk/unstructured_grid.h"

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
    VectorXd dummy_results(VectorXd::Zero(mesh.nodes_.size()));
    const double left_buttom(7.0);
    const double buttom_left(13.0);
    // const double k(constants::kStefanBoltzmann * mesh.dx_ / (1.0));

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("butom_left", Mesh2DRegular::NEUMANN);

    mesh.SetBoundaryValue("left_buttom", left_buttom);
    mesh.SetBoundaryValue("butom_left", buttom_left);

    heat_equation_homogeneous::ConvertButtomLeft(mat_b, mesh, 0, dummy_results);

    ASSERT_DOUBLE_EQ(mesh.dx_ * left_buttom + mesh.dy_ * buttom_left, mat_b.second(0));

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(0, 1));
    ASSERT_DOUBLE_EQ(1.0, mat_b.first(0, 5));
    ASSERT_DOUBLE_EQ(-2.0, mat_b.first(0, 0));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != 0) && (j != 1)) || ((i != 0) && (j != 5))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertButtomLeft(mat_b, mesh, 0, dummy_results);

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

    heat_equation_homogeneous::ConvertButtomLeft(mat_b, mesh, 0, dummy_results);

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

    heat_equation_homogeneous::ConvertButtomLeft(mat_b, mesh, 0, dummy_results);

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

    mesh.SetBoundaryValue("left_buttom", 1.0);
    mesh.SetBoundaryValue("butom_left", 1.0);
    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::RADIATION);
    mesh.SetBoundaryType("butom_left", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertButtomLeft(mat_b, mesh, 0, dummy_results);

    // ASSERT_DOUBLE_EQ(1.0, mat_b.first(0, 0));
    // ASSERT_DOUBLE_EQ(0.5 * (left_buttom + buttom_left), mat_b.second(0));

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
    VectorXd dummy_results(VectorXd::Zero(mesh.nodes_.size()));
    const double right_buttom(7.0);
    const double buttom_right(13.0);
    const double k(constants::kStefanBoltzmann * mesh.dx_ / (1.0));
    const uint node_id(2);
    const uint u_i_jp(3);
    const uint u_im_j(1);

    dummy_results(node_id) = 300.0;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::NEUMANN);

    mesh.SetBoundaryValue("right_buttom", right_buttom);
    mesh.SetBoundaryValue("butom_right", buttom_right);

    heat_equation_homogeneous::ConvertButtomRight(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertButtomRight(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertButtomRight(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertButtomRight(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(mesh.dx_ * right_buttom - mesh.dy_ * buttom_right, mat_b.second(node_id));

    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_i_jp));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_im_j));
    ASSERT_DOUBLE_EQ(2.0, mat_b.first(node_id, node_id));

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

    mesh.SetBoundaryValue("right_buttom", 1.0);
    mesh.SetBoundaryValue("butom_right", 1.0);
    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::RADIATION);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertButtomRight(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(2.0 + 8.0 * k * std::pow(dummy_results(node_id), 3), mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_i_jp));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_im_j));

    ASSERT_DOUBLE_EQ(6.0 * k * std::pow(dummy_results(node_id), 4), mat_b.second(node_id));

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
    VectorXd dummy_results(VectorXd::Zero(mesh.nodes_.size()));
    const double left_top(7.0);
    const double top_left(13.0);
    const double k(constants::kStefanBoltzmann * mesh.dx_ / (1.0));
    const uint node_id(6);
    const uint u_i_jm(5);
    const uint u_ip_j(7);

    dummy_results(node_id) = 300.0;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryType("left_top", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("top_left", Mesh2DRegular::NEUMANN);

    mesh.SetBoundaryValue("left_top", left_top);
    mesh.SetBoundaryValue("top_left", top_left);

    heat_equation_homogeneous::ConvertTopLeft(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertTopLeft(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertTopLeft(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertTopLeft(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(mesh.dy_ * top_left - mesh.dx_ * left_top, mat_b.second(node_id));

    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_ip_j));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_i_jm));
    ASSERT_DOUBLE_EQ(2.0, mat_b.first(node_id, node_id));

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

    mesh.SetBoundaryValue("left_top", 1.0);
    mesh.SetBoundaryValue("top_left", 1.0);
    mesh.SetBoundaryType("left_top", Mesh2DRegular::RADIATION);
    mesh.SetBoundaryType("top_left", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertTopLeft(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(2.0 + 8.0 * k * std::pow(dummy_results(node_id), 3), mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_ip_j));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_i_jm));

    ASSERT_DOUBLE_EQ(6.0 * k * std::pow(dummy_results(node_id), 4), mat_b.second(node_id));

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
    VectorXd dummy_results(VectorXd::Zero(mesh.nodes_.size()));
    const double top_right(7.0);
    const double right_top(13.0);
    const double k(constants::kStefanBoltzmann * mesh.dx_ / (1.0));
    const uint node_id(8);
    const uint u_i_jm(3);
    const uint u_im_j(7);

    dummy_results(node_id) = 300.0;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryType("top_right", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("right_top", Mesh2DRegular::NEUMANN);

    mesh.SetBoundaryValue("top_right", top_right);
    mesh.SetBoundaryValue("right_top", right_top);

    heat_equation_homogeneous::ConvertTopRight(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertTopRight(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertTopRight(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertTopRight(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(mesh.dx_ * right_top + mesh.dy_ * top_right, mat_b.second(node_id));

    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_i_jm));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_im_j));
    ASSERT_DOUBLE_EQ(2.0, mat_b.first(node_id, node_id));

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

    mesh.SetBoundaryValue("top_right", 1.0);
    mesh.SetBoundaryValue("right_top", 1.0);
    mesh.SetBoundaryType("top_right", Mesh2DRegular::RADIATION);
    mesh.SetBoundaryType("right_top", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertTopRight(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(2.0 + 8.0 * k * std::pow(dummy_results(node_id), 3), mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_im_j));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_i_jm));

    ASSERT_DOUBLE_EQ(6.0 * k * std::pow(dummy_results(node_id), 4), mat_b.second(node_id));

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
    VectorXd dummy_results(VectorXd::Zero(mesh.nodes_.size()));
    const double butom_left(7.0);
    const double butom_right(13.0);
    const double surf_bl(15.0);
    const double surf_br(17.0);
    const double k(constants::kStefanBoltzmann * mesh.dx_ / (0.5 * (surf_bl + surf_br)));
    const uint node_id(1);
    const uint u_i_jp(4);
    const uint u_im_j(0);
    const uint u_ip_j(2);

    dummy_results(u_i_jp) = 300.0;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryValue("butom_left", butom_left);
    mesh.SetBoundaryValue("butom_right", butom_right);

    mesh.SetSurfaceThermalConductivity("surf_bl", surf_bl);
    mesh.SetSurfaceThermalConductivity("surf_br", surf_br);

    mesh.SetBoundaryType("butom_left", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertButtom(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertButtom(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertButtom(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertButtom(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, u_i_jp));

    ASSERT_DOUBLE_EQ(-0.5 * (butom_left + butom_right) * mesh.dy_, mat_b.second(node_id));

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

    mesh.SetBoundaryValue("butom_left", 1.0);
    mesh.SetBoundaryValue("butom_right", 1.0);
    mesh.SetBoundaryType("butom_left", Mesh2DRegular::RADIATION);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertButtom(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_i_jp));
    ASSERT_DOUBLE_EQ(1.0 + 4.0 * k * std::pow(dummy_results(node_id), 3), mat_b.first(node_id, node_id));

    ASSERT_DOUBLE_EQ(3.0 * k * std::pow(dummy_results(node_id), 4), mat_b.second(node_id));

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
    VectorXd dummy_results(VectorXd::Zero(mesh.nodes_.size()));
    const double right_top(7.0);
    const double right_buttom(13.0);
    const double surf_tr(15.0);
    const double surf_br(17.0);
    const double k(constants::kStefanBoltzmann * mesh.dx_ / (0.5 * (surf_tr + surf_br)));
    const uint node_id(3);
    const uint u_i_jm(2);
    const uint u_i_jp(8);
    const uint u_im_j(4);

    dummy_results(node_id) = 300.0;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryValue("right_top", right_top);
    mesh.SetBoundaryValue("right_buttom", right_buttom);

    mesh.SetSurfaceThermalConductivity("surf_tr", surf_tr);
    mesh.SetSurfaceThermalConductivity("surf_br", surf_br);

    mesh.SetBoundaryType("right_top", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertRight(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertRight(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertRight(mat_b, mesh, node_id, dummy_results);

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

    heat_equation_homogeneous::ConvertRight(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_im_j));

    ASSERT_DOUBLE_EQ(0.5 * (right_top + right_buttom) * mesh.dx_, mat_b.second(node_id));

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

    mesh.SetBoundaryValue("right_top", 1.0);
    mesh.SetBoundaryValue("right_buttom", 1.0);
    mesh.SetBoundaryType("right_top", Mesh2DRegular::RADIATION);
    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertRight(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_im_j));
    ASSERT_DOUBLE_EQ(1.0 + 4.0 * k * std::pow(dummy_results(node_id), 3), mat_b.first(node_id, node_id));

    ASSERT_DOUBLE_EQ(3.0 * k * std::pow(dummy_results(node_id), 4), mat_b.second(node_id));

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

TEST(heat_equation_homogeneous, ConvertTop) {
    Mesh2DRegular mesh(GetMesh());
    std::pair<MatrixXd, VectorXd> mat_b;
    VectorXd dummy_results(VectorXd::Zero(mesh.nodes_.size()));
    const double top_left(7.0);
    const double top_right(13.0);
    const double surf_tl(15.0);
    const double surf_tr(17.0);
    const double k(constants::kStefanBoltzmann * mesh.dy_ / (0.5 * (surf_tr + surf_tl)));
    const uint node_id(7);
    const uint u_i_jm(4);
    const uint u_im_j(6);
    const uint u_ip_j(8);

    dummy_results(node_id) = 300.0;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryValue("top_left", top_left);
    mesh.SetBoundaryValue("top_right", top_right);

    mesh.SetSurfaceThermalConductivity("surf_tl", surf_tl);
    mesh.SetSurfaceThermalConductivity("surf_tr", surf_tr);

    mesh.SetBoundaryType("top_left", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("top_right", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertTop(mat_b, mesh, node_id, dummy_results);

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

    mesh.SetBoundaryType("top_left", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("top_right", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertTop(mat_b, mesh, node_id, dummy_results);

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

    mesh.SetBoundaryType("top_left", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("top_right", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertTop(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(0.5 * (top_left + top_right), mat_b.second(node_id));

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

    mesh.SetBoundaryType("top_left", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("top_right", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertTop(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_i_jm));

    ASSERT_DOUBLE_EQ(0.5 * (top_left + top_right) * mesh.dx_, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != node_id) && (j != u_ip_j)) || ((i != node_id) && (j != u_i_jm)) ||
                ((i != node_id) && (j != u_im_j))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryValue("top_left", 1.0);
    mesh.SetBoundaryValue("top_right", 1.0);
    mesh.SetBoundaryType("top_left", Mesh2DRegular::RADIATION);
    mesh.SetBoundaryType("top_right", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertTop(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_i_jm));
    ASSERT_DOUBLE_EQ(1.0 + 4.0 * k * std::pow(dummy_results(node_id), 3), mat_b.first(node_id, node_id));

    ASSERT_DOUBLE_EQ(3.0 * k * std::pow(dummy_results(node_id), 4), mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != node_id) && (j != u_i_jm)) || ((i != node_id) && (j != u_im_j)) ||
                ((i != node_id) && (j != u_ip_j))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }
}

TEST(heat_equation_homogeneous, ConvertLeft) {
    Mesh2DRegular mesh(GetMesh());
    std::pair<MatrixXd, VectorXd> mat_b;
    VectorXd dummy_results(VectorXd::Zero(mesh.nodes_.size()));
    const double left_top(7.0);
    const double left_buttom(13.0);
    const double surf_tl(15.0);
    const double surf_bl(17.0);
    const double k(constants::kStefanBoltzmann * mesh.dx_ / (0.5 * (surf_tl + surf_bl)));
    const uint node_id(5);
    const uint u_i_jm(0);
    const uint u_i_jp(6);
    const uint u_ip_j(4);

    dummy_results(u_ip_j) = 300.0;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetBoundaryValue("left_top", left_top);
    mesh.SetBoundaryValue("left_buttom", left_buttom);

    mesh.SetSurfaceThermalConductivity("surf_tl", surf_tl);
    mesh.SetSurfaceThermalConductivity("surf_bl", surf_bl);

    mesh.SetBoundaryType("left_top", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertLeft(mat_b, mesh, node_id, dummy_results);

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
    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertLeft(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(left_buttom, mat_b.second(node_id));

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
    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::DIRICHLET);

    heat_equation_homogeneous::ConvertLeft(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(0.5 * (left_top + left_buttom), mat_b.second(node_id));

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
    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertLeft(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(1.0, mat_b.first(node_id, u_ip_j));

    ASSERT_DOUBLE_EQ(-0.5 * (left_top + left_buttom) * mesh.dx_, mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != node_id) && (j != u_i_jp)) || ((i != node_id) && (j != u_ip_j)) ||
                ((i != node_id) && (j != u_i_jm))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }

    mesh.SetBoundaryValue("left_top", 1.0);
    mesh.SetBoundaryValue("left_buttom", 1.0);
    mesh.SetBoundaryType("left_top", Mesh2DRegular::RADIATION);
    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::NEUMANN);

    heat_equation_homogeneous::ConvertLeft(mat_b, mesh, node_id, dummy_results);

    ASSERT_DOUBLE_EQ(1.0 + 4.0 * k * std::pow(dummy_results(node_id), 3), mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(-1.0, mat_b.first(node_id, u_ip_j));

    ASSERT_DOUBLE_EQ(3.0 * k * std::pow(dummy_results(node_id), 4), mat_b.second(node_id));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (i != node_id) {
            ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));
        }

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != node_id) && (j != u_i_jp)) || ((i != node_id) && (j != u_ip_j)) ||
                ((i != node_id) && (j != u_i_jm))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }
}

TEST(heat_equation_homogeneous, ConvertMidCartesian) {
    Mesh2DRegular mesh(GetMesh());
    std::pair<MatrixXd, VectorXd> mat_b;
    const double surf_tl(7.0);
    const double surf_tr(13.0);
    const double surf_bl(15.0);
    const double surf_br(17.0);
    const uint node_id(4);
    const uint u_i_jm(1);
    const uint u_i_jp(7);
    const uint u_im_j(5);
    const uint u_ip_j(3);

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    mesh.SetSurfaceThermalConductivity("surf_tl", surf_tl);
    mesh.SetSurfaceThermalConductivity("surf_tr", surf_tr);
    mesh.SetSurfaceThermalConductivity("surf_bl", surf_bl);
    mesh.SetSurfaceThermalConductivity("surf_br", surf_br);

    const double mean_xb = 0.5 * (surf_bl + surf_br);
    const double mean_xt = 0.5 * (surf_tl + surf_tr);
    const double mean_yl = 0.5 * (surf_bl + surf_tl);
    const double mean_yr = 0.5 * (surf_br + surf_tr);

    const double therm_tot_x(mean_yl + mean_yr);
    const double therm_tot_y(mean_xb + mean_xt);

    heat_equation_homogeneous::ConvertMidCartesian(mat_b, mesh, node_id);

    ASSERT_DOUBLE_EQ(mean_yl, mat_b.first(node_id, u_im_j));
    ASSERT_DOUBLE_EQ(mean_yr, mat_b.first(node_id, u_ip_j));
    ASSERT_DOUBLE_EQ(-(therm_tot_x + therm_tot_y), mat_b.first(node_id, node_id));
    ASSERT_DOUBLE_EQ(mean_xb, mat_b.first(node_id, u_i_jm));
    ASSERT_DOUBLE_EQ(mean_xt, mat_b.first(node_id, u_i_jp));

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        ASSERT_DOUBLE_EQ(0.0, mat_b.second(i));

        for (uint j = 0; j < mesh.nodes_.size(); j++) {
            if (((i != node_id) && (j != u_i_jp)) || ((i != node_id) && (j != u_ip_j)) ||
                ((i != node_id) && (j != u_i_jm)) || ((i != node_id) && (j != u_im_j))) {
                ASSERT_DOUBLE_EQ(0.0, mat_b.first(i, j));
            }
        }
    }
}

TEST(heat_equation_homogeneous, ConvertMesh2dRegularCartesian) {
    // const std::string file_name("../../../hamt/test/test_data/block_4_segments_fine.msh");
    const std::string file_name("./test/test_data/block_4_segments_fine.msh");
    Mesh2DRegular mesh(mesh_algorithms::MSH2ToMesh2DRegular(gmsh::ReadMSH2(file_name)));
    std::pair<MatrixXd, VectorXd> mat_b;
    VectorXd results;
    const double butom_left(100.0);
    const double butom_right(100.0);
    const double right_buttom(0.0);
    const double right_top(0.0);
    const double top_right(300.0);
    const double top_left(300.0);
    const double left_top(0.0);
    const double left_buttom(0.0);

    mesh.SetBoundaryValue("butom_left", butom_left);
    mesh.SetBoundaryValue("butom_right", butom_right);
    mesh.SetBoundaryValue("right_buttom", right_buttom);
    mesh.SetBoundaryValue("right_top", right_top);
    mesh.SetBoundaryValue("top_right", top_right);
    mesh.SetBoundaryValue("top_left", top_left);
    mesh.SetBoundaryValue("left_top", left_top);
    mesh.SetBoundaryValue("left_buttom", left_buttom);

    mesh.SetBoundaryType("butom_left", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("butom_right", Mesh2DRegular::DIRICHLET);

    mesh.SetBoundaryType("right_buttom", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("right_top", Mesh2DRegular::NEUMANN);

    mesh.SetBoundaryType("left_top", Mesh2DRegular::NEUMANN);
    mesh.SetBoundaryType("left_buttom", Mesh2DRegular::NEUMANN);

    mesh.SetBoundaryType("top_right", Mesh2DRegular::DIRICHLET);
    mesh.SetBoundaryType("top_left", Mesh2DRegular::DIRICHLET);

    mat_b = heat_equation_homogeneous::ConvertMesh2dRegularCartesian(mesh, results);
    results = mat_b.first.colPivHouseholderQr().solve(mat_b.second);

    // buttom: 0, 1, 2
    for (uint i = 0; i < 3; i++) {
        ASSERT_NEAR(100.0, results(i), 1e-9);
    }

    // mid: 3, 4,  5
    for (uint i = 3; i < 6; i++) {
        ASSERT_NEAR(200.0, results(i), 1e-9);
    }

    // top: 6, 7, 8
    for (uint i = 6; i < 9; i++) {
        ASSERT_NEAR(300.0, results(i), 1e-9);
    }
}

TEST(heat_equation_homogeneous, GradientDiff) {
    const Vector3d pointing_vec(-3.0, 5.0, 0.0);
    const Vector3d ref(-1.0 / 3.0, 1.0 / 5.0, 0.0);
    const Vector3d resutls = heat_equation_homogeneous::CalcGradientDiff(pointing_vec);

    for (long i = 0; i < 3; i++) {
        ASSERT_DOUBLE_EQ(ref(i), resutls(i));
    }
}

TEST(heat_equation_homogeneous, CalcElementFactor) {
    const Vector3d node_pos(0.0, 0.0, 0.0);
    const Vector3d adj_node_pos(3.0, 0.0, 0.0);
    const Vector3d last_barycenter(1.0, -1.0, 0.0);
    const Vector3d next_barycenter(1.0, 1.0, 0.0);

    const double L = 2.0;
    const double dx = 3.0;
    const double ref = L / dx;

    const double result =
        heat_equation_homogeneous::CalcElementFactor(node_pos, adj_node_pos, last_barycenter, next_barycenter);

    ASSERT_DOUBLE_EQ(ref, result);
}

}  // namespace hamt
