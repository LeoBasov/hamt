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

TEST(Mesh2DRegular, Cell) {
    Mesh2DRegular::Cell cell;

    cell.node1 = 0;
    cell.node2 = 1;
    cell.node3 = 2;
    cell.node4 = 3;

    ASSERT_TRUE(cell.IsButtom(0, 1));
    ASSERT_TRUE(cell.IsButtom(1, 0));

    ASSERT_TRUE(cell.IsRight(1, 2));
    ASSERT_TRUE(cell.IsRight(2, 1));

    ASSERT_TRUE(cell.IsTop(2, 3));
    ASSERT_TRUE(cell.IsTop(3, 2));

    ASSERT_TRUE(cell.IsLeft(3, 0));
    ASSERT_TRUE(cell.IsLeft(0, 3));

    ASSERT_FALSE(cell.IsButtom(1, 2));
    ASSERT_FALSE(cell.IsButtom(2, 3));
    ASSERT_FALSE(cell.IsButtom(3, 0));

    ASSERT_FALSE(cell.IsRight(2, 3));
    ASSERT_FALSE(cell.IsRight(3, 0));
    ASSERT_FALSE(cell.IsRight(0, 1));

    ASSERT_FALSE(cell.IsTop(3, 0));
    ASSERT_FALSE(cell.IsTop(0, 1));
    ASSERT_FALSE(cell.IsTop(1, 2));

    ASSERT_FALSE(cell.IsLeft(0, 1));
    ASSERT_FALSE(cell.IsLeft(1, 2));
    ASSERT_FALSE(cell.IsLeft(2, 3));
}

}  // namespace hamt
