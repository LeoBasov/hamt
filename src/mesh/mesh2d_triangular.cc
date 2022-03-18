#include "mesh2d_triangular.h"

namespace hamt {

Mesh2DTriangular::Mesh2DTriangular() {}

void Mesh2DTriangular::Clear() {
    nodes_.clear();
    cells_.clear();
    surfaces_.clear();
    boundaries_.clear();

    surface_tags_.clear();
    surface_names_.clear();

    boundary_tags_.clear();
    boundary_names_.clear();
}

Vector3d Mesh2DTriangular::GetBarycentre(size_t celld_id) const { return cells_.at(celld_id).barycentre; }

Vector3d Mesh2DTriangular::GetBarycentre(size_t node_id, size_t adjacent_cell_id) const {
    return GetBarycentre(nodes_.at(node_id).adjacent_cells.at(adjacent_cell_id));
}

Vector3d Mesh2DTriangular::GetNodePos(size_t node_id) const { return nodes_.at(node_id).position; }

Vector3d Mesh2DTriangular::GetNodePos(size_t node_id, size_t adjacent_node_id) const {
    return GetNodePos(nodes_.at(node_id).adjacent_nodes.at(adjacent_node_id));
}

size_t Mesh2DTriangular::Cell::GetNodePos(const size_t& node_id) const {
    const auto& iter = std::find(nodes.begin(), nodes.end(), node_id);

    if (iter == nodes.end()) {
        throw Exception("node_id not in cell", __PRETTY_FUNCTION__);
    } else {
        return iter - nodes.begin();
    }
}

bool Mesh2DTriangular::Cell::IsInCell(const size_t& node_id) const {
    return std::find(nodes.begin(), nodes.end(), node_id) != nodes.end();
}

}  // namespace hamt
