#pragma once

#include <gtest/gtest.h>

#include "../../../src/mesh/mesh2d_regular.h"

namespace hamt {

TEST(Mesh2DRegular, Clear) {
    Mesh2DRegular mesh;

    mesh.dx_ = 3.0;
    mesh.dy_ = 7.0;

    mesh.nodes_.resize(3);
    mesh.cells_.resize(5);
    mesh.surfaces_.resize(7);
    mesh.boundaries_.resize(8);

    mesh.surface_tags_[1] = 2;
    mesh.surface_names_["test"] = 12;

    mesh.boundary_tags_[7] = 11;
    mesh.boundary_names_["test1"] = 82;

    mesh.Clear();

    ASSERT_DOUBLE_EQ(1.0, mesh.dx_);
    ASSERT_DOUBLE_EQ(1.0, mesh.dy_);

    ASSERT_EQ(0, mesh.nodes_.size());
    ASSERT_EQ(0, mesh.cells_.size());
    ASSERT_EQ(0, mesh.surfaces_.size());
    ASSERT_EQ(0, mesh.boundaries_.size());

    ASSERT_EQ(0, mesh.surface_tags_.size());
    ASSERT_EQ(0, mesh.surface_names_.size());

    ASSERT_EQ(0, mesh.boundary_tags_.size());
    ASSERT_EQ(0, mesh.boundary_names_.size());
}

}  // namespace hamt
