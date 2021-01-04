#pragma once

#include <gtest/gtest.h>

#include "../../../../src/exception/exception.h"
#include "../../../../src/io/gmsh/gmsh.h"

namespace hamt {
namespace gmsh {
TEST(gmsh, ReadMSH2) {
    const std::string file_name("./test/unit_tests/io/gmsh/test_data/test_domain_msh2.msh");
    MSH2 mesh;

    ASSERT_THROW(ReadMSH2(""), Exception);
    mesh = ReadMSH2(file_name);

    ASSERT_EQ(36, mesh.nodes_.size());
    ASSERT_EQ(36, mesh.elements_.size());
    ASSERT_EQ(4, mesh.physical_names_.size());

    // node-number x-coord y-coord z-coord
    ASSERT_EQ(1, mesh.nodes_.at(1).node_number);
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(1).coord(0));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(1).coord(1));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(1).coord(2));

    ASSERT_EQ(2, mesh.nodes_.at(2).node_number);
    ASSERT_DOUBLE_EQ(1.0, mesh.nodes_.at(2).coord(0));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(2).coord(1));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(2).coord(2));

    ASSERT_EQ(3, mesh.nodes_.at(3).node_number);
    ASSERT_DOUBLE_EQ(1.0, mesh.nodes_.at(3).coord(0));
    ASSERT_DOUBLE_EQ(1.0, mesh.nodes_.at(3).coord(1));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(3).coord(2));

    ASSERT_EQ(4, mesh.nodes_.at(4).node_number);
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(4).coord(0));
    ASSERT_DOUBLE_EQ(1.0, mesh.nodes_.at(4).coord(1));
    ASSERT_DOUBLE_EQ(0.0, mesh.nodes_.at(4).coord(2));

    // elm-number elm-type number-of-tags < tag > … node-number-list
    ASSERT_EQ(1, mesh.elements_.at(0).elm_number);
    ASSERT_EQ(1, mesh.elements_.at(0).elm_type);
    ASSERT_EQ(2, mesh.elements_.at(0).tags.size());
    ASSERT_EQ(4, mesh.elements_.at(0).tags.at(0));
    ASSERT_EQ(1, mesh.elements_.at(0).tags.at(1));
    ASSERT_EQ(2, mesh.elements_.at(0).node_number_list.size());
    ASSERT_EQ(1, mesh.elements_.at(0).node_number_list.at(0));
    ASSERT_EQ(5, mesh.elements_.at(0).node_number_list.at(1));

    ASSERT_EQ(2, mesh.elements_.at(1).elm_number);
    ASSERT_EQ(1, mesh.elements_.at(1).elm_type);
    ASSERT_EQ(2, mesh.elements_.at(1).tags.size());
    ASSERT_EQ(4, mesh.elements_.at(1).tags.at(0));
    ASSERT_EQ(1, mesh.elements_.at(1).tags.at(1));
    ASSERT_EQ(2, mesh.elements_.at(1).node_number_list.size());
    ASSERT_EQ(5, mesh.elements_.at(1).node_number_list.at(0));
    ASSERT_EQ(6, mesh.elements_.at(1).node_number_list.at(1));

    // physical-dimension physical-tag "physical-name"
    ASSERT_EQ(1, mesh.physical_names_.at(1).physical_dimension);
    ASSERT_EQ(1, mesh.physical_names_.at(1).physical_tag);
    ASSERT_EQ("buttom", mesh.physical_names_.at(1).physical_name);

    ASSERT_EQ(1, mesh.physical_names_.at(2).physical_dimension);
    ASSERT_EQ(2, mesh.physical_names_.at(2).physical_tag);
    ASSERT_EQ("right", mesh.physical_names_.at(2).physical_name);

    ASSERT_EQ(1, mesh.physical_names_.at(3).physical_dimension);
    ASSERT_EQ(3, mesh.physical_names_.at(3).physical_tag);
    ASSERT_EQ("top", mesh.physical_names_.at(3).physical_name);

    ASSERT_EQ(1, mesh.physical_names_.at(4).physical_dimension);
    ASSERT_EQ(4, mesh.physical_names_.at(4).physical_tag);
    ASSERT_EQ("left", mesh.physical_names_.at(4).physical_name);
}
}  // namespace gmsh
}  // namespace hamt
