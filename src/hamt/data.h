#pragma once

#include "../mesh/mesh2d_regular.h"

namespace hamt {
using namespace Eigen;
class Data {
   public:
    Data();
    ~Data() = default;

    void Clear();

    Mesh2DRegular mesh2d_regular_;
    VectorXd results_;
};
}  // namespace hamt
