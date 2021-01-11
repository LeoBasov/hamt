#include "mesh2d_regular.h"

namespace hamt {

Mesh2DRegular::Mesh2DRegular() {}

void Mesh2DRegular::Clear() {
    dx_ = 1.0, dy_ = 1.0;
    nodes_.clear();
    cells_.clear();
    surfaces_.clear();
    boundaries_.clear();
    surface_tags_.clear();
    surface_names_.clear();
    boundary_tags_.clear();
    boundary_names_.clear();
}

bool Mesh2DRegular::Cell::IsButtom(uint node_1, uint node_2) const {
    return (node1 == node_1 && node2 == node_2) || (node1 == node_2 && node2 == node_1);
}

bool Mesh2DRegular::Cell::IsRight(uint node_1, uint node_2) const {
    return (node2 == node_1 && node3 == node_2) || (node2 == node_2 && node3 == node_1);
}

bool Mesh2DRegular::Cell::IsTop(uint node_1, uint node_2) const {
    return (node3 == node_1 && node4 == node_2) || (node3 == node_2 && node4 == node_1);
}

bool Mesh2DRegular::Cell::IsLeft(uint node_1, uint node_2) const {
    return (node4 == node_1 && node1 == node_2) || (node4 == node_2 && node1 == node_1);
}

void Mesh2DRegular::SetBoundaryType(const std::string& name, BoundaryType type) {
    auto iter(boundary_names_.find(name));

    if (iter == boundary_names_.end()) {
        throw Exception("Undefined boundary [" + name + "]", __PRETTY_FUNCTION__);
    } else {
        boundaries_.at(iter->second).type = type;
    }
}

void Mesh2DRegular::SetBoundaryValue(const std::string& name, const double& value) {
    auto iter(boundary_names_.find(name));

    if (iter == boundary_names_.end()) {
        throw Exception("Undefined boundary [" + name + "]", __PRETTY_FUNCTION__);
    } else {
        boundaries_.at(iter->second).value = value;
    }
}

void Mesh2DRegular::SetSurfaceThermalConductivity(const std::string& name, const double& value) {
    auto iter(surface_names_.find(name));

    if (iter == surface_names_.end()) {
        throw Exception("Undefined surface [" + name + "]", __PRETTY_FUNCTION__);
    } else {
        surfaces_.at(iter->second).thermal_conductivity = value;
    }
}

}  // namespace hamt
