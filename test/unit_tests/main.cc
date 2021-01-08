#include <gtest/gtest.h>

#include "io/gmsh/gmsh.h"
#include "mesh/mesh2d_regular.h"
#include "mesh/mesh_algorithms.h"
#include "solver/heat_equation/homogeneous.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
