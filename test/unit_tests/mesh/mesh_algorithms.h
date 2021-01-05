#pragma once

#include <gtest/gtest.h>

#include "../../../src/io/gmsh/gmsh.h"
#include "../../../src/mesh/mesh_algorithms.h"

namespace hamt {

TEST(mesh_algorithms, MSH2ToMesh2DRegular) {
    const std::string file_name("../../../hamt/test/unit_tests/mesh/test_data/block_2.msh");
    const gmsh::MSH2 msh2_mesh = gmsh::ReadMSH2(file_name);
    const Mesh2DRegular mesh = mesh_algorithms::MSH2ToMesh2DRegular(msh2_mesh);
}

}  // namespace hamt
