#pragma once

#include "../exception/exception.h"
#include "../io/gmsh/msh2.h"
#include "mesh2d_regular.h"
#include "mesh2d_triangular.h"

namespace hamt {
namespace mesh_algorithms {

Mesh2DRegular MSH2ToMesh2DRegular(const gmsh::MSH2& msh2_mesh);
void SetUpNodesAndCells(Mesh2DRegular& mesh, const gmsh::MSH2& msh2_mesh);
void SetUpPhysicalGroups(Mesh2DRegular& mesh, const gmsh::MSH2& msh2_mesh);
void SetUpCellSize(Mesh2DRegular& mesh, const gmsh::MSH2& msh2_mesh);

Mesh2DTriangular MSH2ToMesh2DTriangular(const gmsh::MSH2& msh2_mesh);
void SetUpBoundaries(Mesh2DTriangular& mesh, const gmsh::MSH2& msh2_mesh);
void SetUpNodes(Mesh2DTriangular& mesh, const gmsh::MSH2& msh2_mesh);
void SetUpCells(Mesh2DTriangular& mesh, const gmsh::MSH2& msh2_mesh);
void CombineData(Mesh2DTriangular& mesh, const gmsh::MSH2& msh2_mesh);
}
}  // namespace hamt
