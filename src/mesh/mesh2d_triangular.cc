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

std::array<double, 3> Mesh2DTriangular::GetNeumannCoefficients(const size_t cell_id, const size_t boundary_id) const {
    const Cell& cell = cells_.at(cell_id);
    std::array<double, 3> coeffs;
    Vector3d boundary_normal;
    Matrix3d rot_mat = Matrix3d::Zero();
    int node_pos2, node_pos1 = -1;
    size_t node_id1, node_id2;

    rot_mat(0, 1) = 1.0;
    rot_mat(1, 0) = -1.0;
    rot_mat(2, 2) = 1.0;

    for (int i = 0; i < 3; i++) {
        if (cell.boundaries.at(i) == boundary_id) {
            node_pos1 = i;
            break;
        }
    }

    rot_mat(0, 0) = 0.0;

    node_pos2 = node_pos1 == 2 ? 0 : node_pos1 + 1;
    node_id1 = cell.nodes.at(node_pos1);
    node_id2 = cell.nodes.at(node_pos2);

    boundary_normal = (GetNodePos(node_id2) - GetNodePos(node_id1)).normalized();
    boundary_normal = rot_mat * boundary_normal;

    for (size_t i = 0; i < 3; i++) {
        Vector3d r;

        node_pos1 = i == 0 ? 2 : i - 1;
        node_pos2 = i == 2 ? 0 : i + 1;
        r = GetNodePos(cell.nodes.at(node_pos2)) - GetNodePos(cell.nodes.at(node_pos1));
        coeffs.at(i) = 0.5 * (rot_mat * r).dot(boundary_normal);
    }

    return coeffs;
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
