#include "set_solver.h"

namespace hamt {

SetSolver::SetSolver(std::string command_name) : SubOperation(command_name, "solver") {}

SetSolver::SetSolver() : SubOperation() {}

std::string SetSolver::GetHelp() const { return "Sets parameters for solver"; }

void SetSolver::Check(const std::vector<std::string>& argv) { ChecArgvExact(3, argv); }

void SetSolver::Execute(const std::vector<std::string>& argv, const bool&) {
    Solver::Config config(hamt_->solver_.GetConfig());

    if (argv.at(1) == "coord_type") {
        if (argv.at(2) == "cartesian") {
            config.coord_type = Solver::CARTESIAN;

            std::cout << "SET SOLVER COORDINATE TYPE: CARTESIAN" << std::endl;
        } else if (argv.at(2) == "cylinder") {
            config.coord_type = Solver::CYLINDER;

            std::cout << "SET SOLVER COORDINATE TYPE: CYLINDER" << std::endl;
        } else {
            throw CommandError("unknown command 'set solver coord_type' [" + argv.at(2) + "]", __PRETTY_FUNCTION__);
        }
    } else if (argv.at(1) == "mesh_type") {
        if (argv.at(2) == "regular") {
            config.mesh_type = Solver::REGULAR;

            std::cout << "SET SOLVER MESH TYPE: REGULAR" << std::endl;
        } else if (argv.at(2) == "triangular") {
            config.mesh_type = Solver::TRIANGULAR;

            std::cout << "SET SOLVER MESH TYPE: TRIANGULAR" << std::endl;
        } else {
            throw CommandError("unknown command 'set solver meshtype' [" + argv.at(2) + "]", __PRETTY_FUNCTION__);
        }
    } else {
        throw CommandError("unknown command 'set solver' [" + argv.at(1) + "]", __PRETTY_FUNCTION__);
    }

    hamt_->solver_.SetConfig(config);
}

}  // namespace hamt
