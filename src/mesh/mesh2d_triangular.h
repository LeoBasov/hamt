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
        std::vector<size_t> boundaries;
    };

    struct Cell {
        Vector3d barycentre = Vector3d(0.0, 0.0, 0.0);
        std::array<int, 3> nodes = {-1, -1, -1};
        std::array<int, 3> boundaries = {-1, -1, -1};
        int surface_id = -1;

        size_t GetNodePos(const size_t& node_id) const;
        bool IsInCell(const size_t& node_id) const;
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

    Vector3d GetBarycentre(size_t celld_id) const;
    Vector3d GetBarycentre(size_t node_id, size_t adjacent_cell_id) const;

    Vector3d GetNodePos(size_t node_id) const;
    Vector3d GetNodePos(size_t node_id, size_t adjacent_node_id) const;

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
