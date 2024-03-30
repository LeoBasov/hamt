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

std::pair<MatrixXd, VectorXd> ConvertMesh2dTriangular(const Mesh2DTriangular& mesh, const VectorXd& results,
                                                      bool cartesian = true, bool true_radiation = false);
void CentreTriangularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b);
void FEMCentreTriangularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b);
void NeumannTriangularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b);
void HeatFluxTriangularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b);
Vector3d CalcNormalDerevativeCoefficients(const Mesh2DTriangular& mesh, const Vector3d& normal_vec,
                                          const size_t cell_id, const size_t node_id);
void RadiationTriangularMesh(const Mesh2DTriangular& mesh, const VectorXd& results, const size_t node_id,
                             std::pair<MatrixXd, VectorXd>& mat_b);
void FEMCentreCylindricalMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b);

void ConvertBoundariesTriangularMesh(const Mesh2DTriangular& mesh, const VectorXd& results, const size_t node_id,
                                     std::pair<MatrixXd, VectorXd>& mat_b, const bool true_radiation);
void SetVolumetricHeatSourceTriangularMesh(const Mesh2DTriangular& mesh, const size_t node_id,
                                           std::pair<MatrixXd, VectorXd>& mat_b);

}  // namespace heat_equation_homogeneous
}  // namespace hamt
