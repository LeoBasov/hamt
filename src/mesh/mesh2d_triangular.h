#pragma once

#include <Eigen/Dense>
#include <map>
#include <vector>

#include "../exception/exception.h"

using uint = unsigned int;

namespace hamt {
using namespace Eigen;
class Mesh2DTriangular {
   public:
    enum BoundaryType { NEUMANN, DIRICHLET, RADIATION };

    struct Node {
        Vector3d position;
        std::vector<size_t> adjacent_nodes;  // ordered counter clockwise
        std::vector<size_t> adjacent_cells;  // ordered counter clockwise
    };

    struct Cell {
        Vector3d barycentre;
        std::array<int, 3> nodes = {-1, -1, -1};
        std::array<int, 3> boundaries = {-1, -1, -1};
        int surface_id = -1;
    };

    struct Surface {
        double thermal_conductivity = 1.0;
    };

    struct Boundary {
        BoundaryType type = DIRICHLET;
        double value = 0.0;
    };

   public:
    Mesh2DTriangular();
    ~Mesh2DTriangular() = default;

    void Clear();

    std::vector<Node> nodes_;
    std::vector<Cell> cells_;
    std::vector<Surface> surfaces_;
    std::vector<Boundary> boundaries_;

    std::map<uint, uint> surface_tags_;
    std::map<std::string, uint> surface_names_;

    std::map<uint, uint> boundary_tags_;
    std::map<std::string, uint> boundary_names_;
};
}  // namespace hamt
