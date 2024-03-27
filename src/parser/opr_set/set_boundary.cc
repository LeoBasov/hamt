#include "set_boundary.h"

namespace hamt {

SetBoundary::SetBoundary(std::string command_name) : SubOperation(command_name, "boundary") {}

SetBoundary::SetBoundary() : SubOperation() {}

std::string SetBoundary::GetHelp() const { return "Sets boundary values if optionaly type"; }

void SetBoundary::Check(const std::vector<std::string>& argv) {
    ChecArgvMin(3, argv);
    ChecArgvMax(4, argv);
}

void SetBoundary::Execute(const std::vector<std::string>& argv, const bool&) {
    if (hamt_->solver_.GetConfig().mesh_type == Solver::REGULAR) {
        auto iter(hamt_->data_->mesh2d_regular_.boundary_names_.find(argv.at(1)));

        if (iter == hamt_->data_->mesh2d_regular_.boundary_names_.end()) {
            throw CommandError("unknown boundary [" + argv.at(1) + "]", __PRETTY_FUNCTION__);
        } else {
            hamt_->data_->mesh2d_regular_.boundaries_.at(iter->second).value = std::stod(argv.at(2));
            std::cout << "SET BOUNDARY: " << argv.at(1)
                      << " TO VALUE: " << hamt_->data_->mesh2d_regular_.boundaries_.at(iter->second).value << std::endl;
        }

        if (argv.size() == 4 && argv.at(3) == "dirichlet") {
            hamt_->data_->mesh2d_regular_.boundaries_.at(iter->second).type = Mesh2DRegular::DIRICHLET;
            std::cout << "SET BOUNDARY: " << argv.at(1) << " TO DIRICHLET" << std::endl;
        } else if (argv.size() == 4 && argv.at(3) == "neumann") {
            hamt_->data_->mesh2d_regular_.boundaries_.at(iter->second).type = Mesh2DRegular::NEUMANN;
            std::cout << "SET BOUNDARY: " << argv.at(1) << " TO NEUMANN" << std::endl;
        } else if (argv.size() == 4 && argv.at(3) == "radiation") {
            hamt_->data_->mesh2d_regular_.boundaries_.at(iter->second).type = Mesh2DRegular::RADIATION;
            std::cout << "SET BOUNDARY: " << argv.at(1) << " TO RADIATION" << std::endl;
        } else if (argv.size() == 4) {
            throw CommandError("unknown boundary type [" + argv.at(3) + "]", __PRETTY_FUNCTION__);
        }
    } else if (hamt_->solver_.GetConfig().mesh_type == Solver::TRIANGULAR) {
        auto iter(hamt_->data_->mesh2d_triangular_.boundary_names_.find(argv.at(1)));

        if (iter == hamt_->data_->mesh2d_triangular_.boundary_names_.end()) {
            throw CommandError("unknown boundary [" + argv.at(1) + "]", __PRETTY_FUNCTION__);
        } else {
            hamt_->data_->mesh2d_triangular_.boundaries_.at(iter->second).value = std::stod(argv.at(2));
            std::cout << "SET BOUNDARY: " << argv.at(1)
                      << " TO VALUE: " << hamt_->data_->mesh2d_triangular_.boundaries_.at(iter->second).value
                      << std::endl;
        }

        if (argv.size() == 4 && argv.at(3) == "dirichlet") {
            hamt_->data_->mesh2d_triangular_.boundaries_.at(iter->second).type = Mesh2DTriangular::DIRICHLET;
            std::cout << "SET BOUNDARY: " << argv.at(1) << " TO DIRICHLET" << std::endl;
        } else if (argv.size() == 4 && argv.at(3) == "neumann") {
            hamt_->data_->mesh2d_triangular_.boundaries_.at(iter->second).type = Mesh2DTriangular::NEUMANN;
            std::cout << "SET BOUNDARY: " << argv.at(1) << " TO NEUMANN" << std::endl;
        } else if (argv.size() == 4 && argv.at(3) == "radiation") {
            hamt_->data_->mesh2d_triangular_.boundaries_.at(iter->second).type = Mesh2DTriangular::RADIATION;
            std::cout << "SET BOUNDARY: " << argv.at(1) << " TO RADIATION" << std::endl;
        } else if (argv.size() == 4 && argv.at(3) == "heat_flux") {
            hamt_->data_->mesh2d_triangular_.boundaries_.at(iter->second).type = Mesh2DTriangular::HEAT_FLUX;
            std::cout << "SET BOUNDARY: " << argv.at(1) << " TO HEAT_FLUX" << std::endl;
        } else if (argv.size() == 4) {
            throw CommandError("unknown boundary type [" + argv.at(3) + "]", __PRETTY_FUNCTION__);
        }
    } else {
        throw CommandError("Command 'set boundary': undfedined mesh type.");
    }
}

}  // namespace hamt
