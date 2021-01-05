#include "mesh2d_regular.h"

namespace hamt {

Mesh2DRegular::Mesh2DRegular() {}

void Mesh2DRegular::Clear() {
    dx_ = 1.0, dy_ = 1.0;
    nodes_.clear();
    cells_.clear();
    surfaces_.clear();
    boundaries_.clear();
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

}  // namespace hamt
