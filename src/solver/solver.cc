#include "solver.h"

namespace hamt {

Solver::Solver() {}

Solver::Config Solver::GetConfig() const { return config_; }
void Solver::SetConfig(const Config& config) { config_ = config; }

void Solver::SetData(const std::shared_ptr<Data>& data) { data_ = data; }

double Solver::Execute() {
    std::pair<MatrixXd, VectorXd> mat_b;

    switch (config_.solver_type) {
        case HOMOGENEOUS: {
            switch (config_.mesh_type) {
                case REGULAR: {
                    ExecuteHomogenRegMesh(mat_b);
                    break;
                }
                case TRIANGULAR: {
                    ExecuteHomogenTrianglMesh(mat_b);
                    break;
                }
                default: {
                    throw Exception("Undefined mesh type" + std::to_string(config_.mesh_type), __PRETTY_FUNCTION__);
                }
            }
            break;
        }
        default: {
            throw Exception("Undefined solver type" + std::to_string(config_.solver_type), __PRETTY_FUNCTION__);
        }
    }

    SolveSystemOfLinearEquations(mat_b);
    return CheckAccuracy(mat_b);
}

void Solver::ExecuteHomogenRegMesh(std::pair<MatrixXd, VectorXd>& mat_b) {
    if (static_cast<size_t>(data_->results_.rows()) != data_->mesh2d_regular_.nodes_.size()) {
        data_->results_ = VectorXd::Zero(data_->mesh2d_regular_.nodes_.size());
    }

    switch (config_.coord_type) {
        case CARTESIAN: {
            mat_b = heat_equation_homogeneous::ConvertMesh2dRegularCartesian(data_->mesh2d_regular_, data_->results_);
            break;
        }
        case CYLINDER: {
            mat_b = heat_equation_homogeneous::ConvertMesh2dRegularCylindircal(data_->mesh2d_regular_, data_->results_);
            break;
        }
        default: { throw Exception("Undefined coord type" + std::to_string(config_.coord_type), __PRETTY_FUNCTION__); }
    }
}

void Solver::ExecuteHomogenTrianglMesh(std::pair<MatrixXd, VectorXd>& mat_b) {
    if (static_cast<size_t>(data_->results_.rows()) != data_->mesh2d_triangular_.nodes_.size()) {
        data_->results_ = VectorXd::Zero(data_->mesh2d_triangular_.nodes_.size());
    }

    switch (config_.coord_type) {
        case CARTESIAN: {
            mat_b = heat_equation_homogeneous::ConvertMesh2dTriangular(data_->mesh2d_triangular_, data_->results_, true,
                                                                       false);
            break;
        }
        case CYLINDER: {
            mat_b = heat_equation_homogeneous::ConvertMesh2dTriangular(data_->mesh2d_triangular_, data_->results_,
                                                                       false, false);
            break;
        }
        default: {
            throw Exception("Undefined coord type" + std::to_string(config_.coord_type), __PRETTY_FUNCTION__);
        }
    }
}

void Solver::SolveSystemOfLinearEquations(const std::pair<MatrixXd, VectorXd>& mat_b) {
    data_->results_ = mat_b.first.partialPivLu().solve(mat_b.second);
}

double Solver::CheckAccuracy(std::pair<MatrixXd, VectorXd>& mat_b) {
    bool true_radiation = false;

    for (const auto& boundary : data_->mesh2d_triangular_.boundaries_) {
        if (boundary.type == Mesh2DTriangular::BoundaryType::RADIATION) {
            true_radiation = true;
            break;
        }
    }

    if (true_radiation) {
        switch (config_.coord_type) {
            case CARTESIAN: {
                mat_b = heat_equation_homogeneous::ConvertMesh2dTriangular(data_->mesh2d_triangular_, data_->results_,
                                                                           true, true_radiation);
                break;
            }
            case CYLINDER: {
                mat_b = heat_equation_homogeneous::ConvertMesh2dTriangular(data_->mesh2d_triangular_, data_->results_,
                                                                           false, true_radiation);
                break;
            }
            default: {
                throw Exception("Undefined coord type" + std::to_string(config_.coord_type), __PRETTY_FUNCTION__);
            }
        }
    }

    return (mat_b.first * data_->results_ - mat_b.second).norm() / mat_b.second.norm();
}

}  // namespace hamt
