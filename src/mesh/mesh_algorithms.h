#pragma once

#include "../io/gmsh/msh2.h"
#include "mesh2d_regular.h"

namespace hamt {
namespace mesh_algorithms {

Mesh2DRegular MSH2ToMesh2DRegular(const gmsh::MSH2& msh2_mesh);
void SetUpNodesAndCells(Mesh2DRegular& mesh, const gmsh::MSH2& msh2_mesh);
void SetUpPhysicalGroups(Mesh2DRegular& mesh, const gmsh::MSH2& msh2_mesh);
void SetUpCellSize(Mesh2DRegular& mesh, const gmsh::MSH2& msh2_mesh);
}
}  // namespace hamt
