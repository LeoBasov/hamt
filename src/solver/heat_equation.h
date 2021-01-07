#pragma once

#include <Eigen/Dense>

#include "../exception/exception.h"
#include "../mesh/mesh2d_regular.h"

namespace hamt {
namespace heat_equation {
namespace homogeneous {
using namespace Eigen;

std::pair<MatrixXd, VectorXd> ConvertMesh2dRegularCartesian(const Mesh2DRegular& mesh);
void ConvertButtomLeft(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);

}  // namespace homogeneous
}  // namespace heat_equation
}  // namespace hamt