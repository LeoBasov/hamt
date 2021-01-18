#pragma once

#include <Eigen/Dense>

#include "../../exception/exception.h"
#include "../../mesh/mesh2d_regular.h"

namespace hamt {
namespace heat_equation_homogeneous {
using namespace Eigen;

void ConvertButtomLeft(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);
void ConvertButtomRight(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);
void ConvertTopRight(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);
void ConvertTopLeft(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);

std::pair<MatrixXd, VectorXd> ConvertMesh2dRegularCartesian(const Mesh2DRegular& mesh);
void ConvertButtomCartesian(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);
void ConvertRightCartesian(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);
void ConvertTopCartesian(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);
void ConvertLeftCartesian(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);
void ConvertMidCartesian(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);

std::pair<MatrixXd, VectorXd> ConvertMesh2dRegularCylindircal(const Mesh2DRegular& mesh);
void ConvertButtomCylindrical(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);

}  // namespace heat_equation_homogeneous
}  // namespace hamt
