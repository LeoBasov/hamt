#pragma once

#include "../mesh/mesh2d_regular.h"
#include "../mesh/mesh2d_triangular.h"

namespace hamt {
using namespace Eigen;
class Data {
   public:
    Data();
    ~Data() = default;

    void Clear();

    Mesh2DRegular mesh2d_regular_;
    Mesh2DTriangular mesh2d_triangular_;
    VectorXd results_;
};
}  // namespace hamt
