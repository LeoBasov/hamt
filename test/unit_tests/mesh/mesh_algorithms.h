#pragma once

#include <gtest/gtest.h>

#include "../../../src/io/gmsh/gmsh.h"
#include "../../../src/mesh/mesh_algorithms.h"

namespace hamt {

TEST(mesh_algorithms, MSH2ToMesh2DRegular) {
    // const std::string file_name("../../../hamt/test/test_data/block.msh");
    const std::string file_name("./test/test_data/block.msh");
    const gmsh::MSH2 msh2_mesh = gmsh::ReadMSH2(file_name);
    const Mesh2DRegular mesh = mesh_algorithms::MSH2ToMesh2DRegular(msh2_mesh);

    ASSERT_EQ(mesh.nodes_.at(0).type, Mesh2DRegular::BUTTOM_LEFT);
    ASSERT_EQ(mesh.nodes_.at(1).type, Mesh2DRegular::BUTTOM_RIGHT);
    ASSERT_EQ(mesh.nodes_.at(4).type, Mesh2DRegular::TOP_LEFT);
    ASSERT_EQ(mesh.nodes_.at(6).type, Mesh2DRegular::TOP_RIGHT);
    ASSERT_EQ(mesh.nodes_.at(5).type, Mesh2DRegular::BUTTOM_RIGHT);
    ASSERT_EQ(mesh.nodes_.at(28).type, Mesh2DRegular::MID);
    ASSERT_EQ(mesh.nodes_.at(3).type, Mesh2DRegular::TOP);
    ASSERT_EQ(mesh.nodes_.at(12).type, Mesh2DRegular::BUTTOM);
    ASSERT_EQ(mesh.nodes_.at(21).type, Mesh2DRegular::LEFT);
    ASSERT_EQ(mesh.nodes_.at(14).type, Mesh2DRegular::RIGHT);

    // inner corner
    ASSERT_EQ(mesh.nodes_.at(2).u_i_jm, 14);
    ASSERT_EQ(mesh.nodes_.at(2).u_i_jp, 16);
    ASSERT_EQ(mesh.nodes_.at(2).u_im_j, 31);
    ASSERT_EQ(mesh.nodes_.at(2).u_ip_j, 7);

    ASSERT_EQ(mesh.nodes_.at(2).cell_bl, 17);
    ASSERT_EQ(mesh.nodes_.at(2).cell_br, -1);
    ASSERT_EQ(mesh.nodes_.at(2).cell_tr, 0);
    ASSERT_EQ(mesh.nodes_.at(2).cell_tl, 18);

    ASSERT_EQ(mesh.nodes_.at(15).u_i_jm, 14);
    ASSERT_EQ(mesh.nodes_.at(15).u_i_jp, 16);
    ASSERT_EQ(mesh.nodes_.at(15).u_im_j, 31);
    ASSERT_EQ(mesh.nodes_.at(15).u_ip_j, 7);

    ASSERT_EQ(mesh.nodes_.at(15).cell_bl, 17);
    ASSERT_EQ(mesh.nodes_.at(15).cell_br, -1);
    ASSERT_EQ(mesh.nodes_.at(15).cell_tr, 0);
    ASSERT_EQ(mesh.nodes_.at(15).cell_tl, 18);

    ASSERT_DOUBLE_EQ(1.0, mesh.nodes_.at(2).position(0));
    ASSERT_DOUBLE_EQ(0.5, mesh.nodes_.at(2).position(1));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(2).position(2));

    ASSERT_DOUBLE_EQ(1.0, mesh.nodes_.at(15).position(0));
    ASSERT_DOUBLE_EQ(0.5, mesh.nodes_.at(15).position(1));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(15).position(2));

    // buttom lef
    ASSERT_EQ(mesh.nodes_.at(0).u_i_jm, -1);
    ASSERT_EQ(mesh.nodes_.at(0).u_i_jp, 22);
    ASSERT_EQ(mesh.nodes_.at(0).u_im_j, -1);
    ASSERT_EQ(mesh.nodes_.at(0).u_ip_j, 11);

    ASSERT_EQ(mesh.nodes_.at(0).cell_bl, -1);
    ASSERT_EQ(mesh.nodes_.at(0).cell_br, -1);
    ASSERT_EQ(mesh.nodes_.at(0).cell_tr, 4);
    ASSERT_EQ(mesh.nodes_.at(0).cell_tl, -1);

    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(0).position(0));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(0).position(1));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(0).position(2));

    // buttom right
    // top left
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(4).position(0));
    ASSERT_DOUBLE_EQ(1.0, mesh.nodes_.at(4).position(1));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(4).position(2));

    // top right
    ASSERT_DOUBLE_EQ(1.5, mesh.nodes_.at(6).position(0));
    ASSERT_DOUBLE_EQ(1.0, mesh.nodes_.at(6).position(1));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(6).position(2));

    // left
    // right
    // top
    // buttom

    // mid
    ASSERT_EQ(mesh.nodes_.at(28).u_i_jm, 27);
    ASSERT_EQ(mesh.nodes_.at(28).u_i_jp, 29);
    ASSERT_EQ(mesh.nodes_.at(28).u_im_j, 25);
    ASSERT_EQ(mesh.nodes_.at(28).u_ip_j, 31);

    ASSERT_EQ(mesh.nodes_.at(28).cell_bl, 9);
    ASSERT_EQ(mesh.nodes_.at(28).cell_br, 13);
    ASSERT_EQ(mesh.nodes_.at(28).cell_tr, 14);
    ASSERT_EQ(mesh.nodes_.at(28).cell_tl, 10);

    ASSERT_DOUBLE_EQ(0.25, mesh.dx_);
    ASSERT_DOUBLE_EQ(0.25, mesh.dy_);

    // surfaces
    ASSERT_EQ(2, mesh.surface_names_.size());
    ASSERT_EQ(2, mesh.surface_tags_.size());

    ASSERT_EQ(0, mesh.surface_names_.at("surf_small"));
    ASSERT_EQ(1, mesh.surface_names_.at("surf_big"));

    ASSERT_EQ(0, mesh.surface_tags_.at(1));
    ASSERT_EQ(1, mesh.surface_tags_.at(2));

    // boundaries
    ASSERT_EQ(8, mesh.boundary_names_.size());
    ASSERT_EQ(8, mesh.boundary_tags_.size());

    ASSERT_EQ(0, mesh.boundary_names_.at("bs"));
    ASSERT_EQ(1, mesh.boundary_names_.at("rs"));
    ASSERT_EQ(2, mesh.boundary_names_.at("ts"));
    ASSERT_EQ(3, mesh.boundary_names_.at("ls"));
    ASSERT_EQ(4, mesh.boundary_names_.at("bb"));
    ASSERT_EQ(5, mesh.boundary_names_.at("rb"));
    ASSERT_EQ(6, mesh.boundary_names_.at("tb"));
    ASSERT_EQ(7, mesh.boundary_names_.at("lb"));

    ASSERT_EQ(0, mesh.boundary_tags_.at(1));
    ASSERT_EQ(1, mesh.boundary_tags_.at(2));
    ASSERT_EQ(2, mesh.boundary_tags_.at(3));
    ASSERT_EQ(3, mesh.boundary_tags_.at(4));
    ASSERT_EQ(4, mesh.boundary_tags_.at(5));
    ASSERT_EQ(5, mesh.boundary_tags_.at(6));
    ASSERT_EQ(6, mesh.boundary_tags_.at(7));
    ASSERT_EQ(7, mesh.boundary_tags_.at(8));
}

}  // namespace hamt
