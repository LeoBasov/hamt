#pragma once

#include <gtest/gtest.h>

#include "../../../../src/io/gmsh/gmsh.h"
#include "../../../../src/mesh/mesh_algorithms.h"
#include "../../../../src/solver/heat_equation/homogeneous.h"

namespace hamt {

TEST(heat_equation_homogeneous, ConvertButtomLeft) {
    const std::string file_name("../../../hamt/test/test_data/block_4_segments.msh");
    // const std::string file_name("./test/test_data/block_4_segments.msh");
    const gmsh::MSH2 msh2_mesh = gmsh::ReadMSH2(file_name);
    const Mesh2DRegular mesh = mesh_algorithms::MSH2ToMesh2DRegular(msh2_mesh);
}

}  // namespace hamt
