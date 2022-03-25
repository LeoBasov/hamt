#include "solver.h"

namespace hamt {

Solver::Solver() {}

Solver::Config Solver::GetConfig() const { return config_; }
void Solver::SetConfig(const Config& config) { config_ = config; }

void Solver::SetData(const std::shared_ptr<Data>& data) { data_ = data; }

void Solver::Execute() {
    switch (config_.solver_type) {
        case HOMOGENEOUS: {
            switch (config_.mesh_type) {
                case REGULAR: {
                    ExecuteHomogenRegMesh();
                    break;
                }
                case TRIANGULAR: {
                    ExecuteHomogenTrianglMesh();
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
}

void Solver::ExecuteHomogenRegMesh() {
    if (static_cast<size_t>(data_->results_.rows()) != data_->mesh2d_regular_.nodes_.size()) {
        data_->results_ = VectorXd::Zero(data_->mesh2d_regular_.nodes_.size());
    }

    switch (config_.coord_type) {
        case CARTESIAN: {
            const std::pair<MatrixXd, VectorXd> mat_b(
                heat_equation_homogeneous::ConvertMesh2dRegularCartesian(data_->mesh2d_regular_, data_->results_));
            data_->results_ = mat_b.first.partialPivLu().solve(mat_b.second);
            break;
        }
        case CYLINDER: {
            const std::pair<MatrixXd, VectorXd> mat_b(
                heat_equation_homogeneous::ConvertMesh2dRegularCylindircal(data_->mesh2d_regular_, data_->results_));
            data_->results_ = mat_b.first.partialPivLu().solve(mat_b.second);
            break;
        }
        default: { throw Exception("Undefined coord type" + std::to_string(config_.coord_type), __PRETTY_FUNCTION__); }
    }
}

void Solver::ExecuteHomogenTrianglMesh() {
    if (static_cast<size_t>(data_->results_.rows()) != data_->mesh2d_triangular_.nodes_.size()) {
        data_->results_ = VectorXd::Zero(data_->mesh2d_triangular_.nodes_.size());
    }

    switch (config_.coord_type) {
        case CARTESIAN: {
            const std::pair<MatrixXd, VectorXd> mat_b(heat_equation_homogeneous::ConvertMesh2dTriangularCartesian(
                data_->mesh2d_triangular_, data_->results_));
            data_->results_ = mat_b.first.partialPivLu().solve(mat_b.second);
            break;
        }
        case CYLINDER: {
            throw IncompleteCodeError("cylinder coordinates not defined for trangular mesh");
            break;
        }
        default: {
            throw Exception("Undefined coord type" + std::to_string(config_.coord_type), __PRETTY_FUNCTION__);
        }
    }
}

}  // namespace hamt
