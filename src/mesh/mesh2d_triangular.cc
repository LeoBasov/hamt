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

void Mesh2DTriangular::SetBoundaryType(const std::string& name, BoundaryType type) {
    auto iter(boundary_names_.find(name));

    if (iter == boundary_names_.end()) {
        throw Exception("Undefined boundary [" + name + "]", __PRETTY_FUNCTION__);
    } else {
        boundaries_.at(iter->second).type = type;
    }
}

void Mesh2DTriangular::SetBoundaryValue(const std::string& name, const double& value) {
    auto iter(boundary_names_.find(name));

    if (iter == boundary_names_.end()) {
        throw Exception("Undefined boundary [" + name + "]", __PRETTY_FUNCTION__);
    } else {
        boundaries_.at(iter->second).value = value;
    }
}

void Mesh2DTriangular::SetSurfaceThermalConductivity(const std::string& name, const double& value) {
    auto iter(surface_names_.find(name));

    if (iter == surface_names_.end()) {
        throw Exception("Undefined surface [" + name + "]", __PRETTY_FUNCTION__);
    } else {
        surfaces_.at(iter->second).thermal_conductivity = value;
    }
}

size_t Mesh2DTriangular::GetAdjNodeId(size_t node_id, size_t adjacent_node_pos) const {
    return nodes_.at(node_id).adjacent_nodes.at(adjacent_node_pos);
}

size_t Mesh2DTriangular::GetAdjCellId(size_t node_id, size_t adjacent_cell_pos) const {
    return nodes_.at(node_id).adjacent_cells.at(adjacent_cell_pos);
}

Vector3d Mesh2DTriangular::GetBarycentre(size_t celld_id) const { return cells_.at(celld_id).barycentre; }

Vector3d Mesh2DTriangular::GetBarycentre(size_t node_id, size_t adjacent_cell_pos) const {
    return GetBarycentre(GetAdjCellId(node_id, adjacent_cell_pos));
}

Vector3d Mesh2DTriangular::GetNodePos(size_t node_id) const { return nodes_.at(node_id).position; }

Vector3d Mesh2DTriangular::GetNodePos(size_t node_id, size_t adjacent_node_pos) const {
    return GetNodePos(GetAdjNodeId(node_id, adjacent_node_pos));
}

double Mesh2DTriangular::GetCellArea(const size_t cell_id) const {
    const Cell& cell = cells_.at(cell_id);
    const Vector3d point1 = GetNodePos(cell.nodes.at(0));
    const Vector3d point2 = GetNodePos(cell.nodes.at(1));
    const Vector3d point3 = GetNodePos(cell.nodes.at(2));
    const Vector3d dist1 = point2 - point1;
    const Vector3d dist2 = point3 - point1;
    const Vector3d cross = dist1.cross(dist2);

    return 0.5 * cross.norm();
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
