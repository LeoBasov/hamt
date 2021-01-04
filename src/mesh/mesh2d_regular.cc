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

}  // namespace hamt
