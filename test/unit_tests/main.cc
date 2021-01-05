#include <gtest/gtest.h>

#include "io/gmsh/gmsh.h"
#include "mesh/mesh_algorithms.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
