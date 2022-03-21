#pragma once

#include <Eigen/Dense>

#include "../../common/constants.h"
#include "../../exception/exception.h"
#include "../../exception/incomplete_code_error.h"
#include "../../mesh/mesh2d_regular.h"
#include "../../mesh/mesh2d_triangular.h"

namespace hamt {
namespace heat_equation_homogeneous {
using namespace Eigen;

void CheckSurfaceEmissivityFactor(const double& value);

void ConvertButtomLeft(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                       const VectorXd& results);
void ConvertButtomRight(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                        const VectorXd& results);
void ConvertTopRight(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                     const VectorXd& results);
void ConvertTopLeft(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                    const VectorXd& results);
void ConvertTop(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                const VectorXd& results);
void ConvertButtom(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                   const VectorXd& results);
void ConvertRight(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                  const VectorXd& results);
void ConvertLeft(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                 const VectorXd& results);

std::pair<MatrixXd, VectorXd> ConvertMesh2dRegularCartesian(const Mesh2DRegular& mesh, const VectorXd& results);
void ConvertMidCartesian(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);

std::pair<MatrixXd, VectorXd> ConvertMesh2dRegularCylindircal(const Mesh2DRegular& mesh, const VectorXd& results);
void ConvertMidCylindrical(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row);

std::pair<MatrixXd, VectorXd> ConvertMesh2dTriangularCartesian(const Mesh2DTriangular& mesh, const VectorXd& results);
void CentreTriangularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b);

double CalcTriangleSurface(const Vector3d& point1, const Vector3d& point2, const Vector3d& point3);
double CalcElementFactor(const Vector3d& node_pos, const Vector3d& adj_node_pos, const Vector3d& last_barycenter,
                         const Vector3d& next_barycenter);

// calculates the vector from distance vector of two points which when pultiplied with the value distance of two points
// equals the gradient
Vector3d CalcGradientDiff(const Vector3d& pointing_vec);
void NeumannTraingularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b);
std::array<double, 3> GetNeumannCoefficients(const Mesh2DTriangular& mesh, const size_t cell_id,
                                             const size_t boundary_id);

}  // namespace heat_equation_homogeneous
}  // namespace hamt
