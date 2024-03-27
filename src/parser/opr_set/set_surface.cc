#include "set_surface.h"

namespace hamt {

SetSurface::SetSurface(std::string command_name) : SubOperation(command_name, "surface") {}

SetSurface::SetSurface() : SubOperation() {}

std::string SetSurface::GetHelp() const { return "Sets surface values"; }

void SetSurface::Check(const std::vector<std::string>& argv) { ChecArgvExact(3, argv); }

void SetSurface::Execute(const std::vector<std::string>& argv, const bool&) {
    if (hamt_->solver_.GetConfig().mesh_type == Solver::REGULAR) {
        auto iter(hamt_->data_->mesh2d_regular_.surface_names_.find(argv.at(1)));

        if (iter != hamt_->data_->mesh2d_regular_.surface_names_.end()) {
            hamt_->data_->mesh2d_regular_.surfaces_.at(iter->second).thermal_conductivity = std::stod(argv.at(2));

            std::cout << "SET SURFACE: " << argv.at(1)
                      << " TO VALUE: " << hamt_->data_->mesh2d_regular_.surfaces_.at(iter->second).thermal_conductivity
                      << std::endl;
        } else {
            throw CommandError("unknown surface [" + argv.at(2) + "]", __PRETTY_FUNCTION__);
        }
    } else if (hamt_->solver_.GetConfig().mesh_type == Solver::TRIANGULAR) {
        auto iter(hamt_->data_->mesh2d_triangular_.surface_names_.find(argv.at(1)));

        if (iter != hamt_->data_->mesh2d_triangular_.surface_names_.end()) {
            hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).thermal_conductivity = std::stod(argv.at(2));

            std::cout << "SET SURFACE: " << argv.at(1) << " TO VALUE: "
                      << hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).thermal_conductivity << std::endl;
        } else {
            throw CommandError("unknown surface [" + argv.at(2) + "]", __PRETTY_FUNCTION__);
        }
    } else {
        throw CommandError("Command 'set boundary': undfedined mesh type.");
    }
}

}  // namespace hamt
