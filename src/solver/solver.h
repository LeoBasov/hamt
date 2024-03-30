#pragma once

#include <memory>

#include "../exception/incomplete_code_error.h"
#include "../hamt/data.h"
#include "heat_equation/homogeneous.h"

namespace hamt {
class Solver {
   public:
    enum SolverType { HOMOGENEOUS };
    enum MeshType { REGULAR, TRIANGULAR };
    enum CoordinatesType { CARTESIAN, CYLINDER };

    struct Config {
        SolverType solver_type = HOMOGENEOUS;
        MeshType mesh_type = REGULAR;
        CoordinatesType coord_type = CARTESIAN;
    };

    Solver();
    ~Solver() = default;

    Config GetConfig() const;
    void SetConfig(const Config& config);
    void SetData(const std::shared_ptr<Data>& data);
    double Execute();

   private:
    std::shared_ptr<Data> data_;
    Config config_;

    void ExecuteHomogenRegMesh(std::pair<MatrixXd, VectorXd>& mat_b);
    void ExecuteHomogenTrianglMesh(std::pair<MatrixXd, VectorXd>& mat_b);
    void SolveSystemOfLinearEquations(const std::pair<MatrixXd, VectorXd>& mat_b);
    double CheckAccuracy(std::pair<MatrixXd, VectorXd>& mat_b);
};
}  // namespace hamt
