#pragma once

#include <gtest/gtest.h>

#include "../../../src/io/gmsh/gmsh.h"
#include "../../../src/mesh/mesh_algorithms.h"

namespace hamt {

TEST(mesh_algorithms, MSH2ToMesh2DRegular) {
    const std::string file_name("../../../hamt/test/unit_tests/mesh/test_data/block_3.msh");
    const gmsh::MSH2 msh2_mesh = gmsh::ReadMSH2(file_name);
    const Mesh2DRegular mesh = mesh_algorithms::MSH2ToMesh2DRegular(msh2_mesh);

    ASSERT_EQ(mesh.nodes_.at(0).type, Mesh2DRegular::BUTTOM_LEFT);
    ASSERT_EQ(mesh.nodes_.at(1).type, Mesh2DRegular::BUTTOM_RIGHT);
    ASSERT_EQ(mesh.nodes_.at(4).type, Mesh2DRegular::TOP_LEFT);
    ASSERT_EQ(mesh.nodes_.at(6).type, Mesh2DRegular::TOP_RIGHT);
    ASSERT_EQ(mesh.nodes_.at(5).type, Mesh2DRegular::BUTTOM_RIGHT);

    ASSERT_EQ(mesh.nodes_.at(0).u_i_jm, -1);
    ASSERT_EQ(mesh.nodes_.at(0).u_i_jp, 22);
    ASSERT_EQ(mesh.nodes_.at(0).u_im_j, -1);
    ASSERT_EQ(mesh.nodes_.at(0).u_ip_j, 11);

    ASSERT_EQ(mesh.nodes_.at(0).cell_bl, -1);
    ASSERT_EQ(mesh.nodes_.at(0).cell_br, -1);
    ASSERT_EQ(mesh.nodes_.at(0).cell_tr, 4);
    ASSERT_EQ(mesh.nodes_.at(0).cell_tl, -1);

    ASSERT_EQ(mesh.nodes_.at(28).type, Mesh2DRegular::MID);

    ASSERT_EQ(mesh.nodes_.at(28).u_i_jm, 27);
    ASSERT_EQ(mesh.nodes_.at(28).u_i_jp, 29);
    ASSERT_EQ(mesh.nodes_.at(28).u_im_j, 25);
    ASSERT_EQ(mesh.nodes_.at(28).u_ip_j, 31);

    ASSERT_EQ(mesh.nodes_.at(28).cell_bl, 9);
    ASSERT_EQ(mesh.nodes_.at(28).cell_br, 13);
    ASSERT_EQ(mesh.nodes_.at(28).cell_tr, 14);
    ASSERT_EQ(mesh.nodes_.at(28).cell_tl, 10);
}

}  // namespace hamt
