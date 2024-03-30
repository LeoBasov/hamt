#include "set_surface.h"

namespace hamt {

SetSurface::SetSurface(std::string command_name) : SubOperation(command_name, "surface") {}

SetSurface::SetSurface() : SubOperation() {}

std::string SetSurface::GetHelp() const { return "Sets surface values"; }

void SetSurface::Check(const std::vector<std::string>& argv) {
    ChecArgvMin(3, argv);

    if (argv.size() > 3 && (argv.size() - 2) % 2) {
        throw CommandError("command '" + command_name_ + "' parameter '" + name_ +
                           "' must not have an even number of arguments. But given are '" +
                           std::to_string(argv.size() - 2) + "' argument(s)");
    }
}

void SetSurface::Execute(const std::vector<std::string>& argv, const bool&) {
    if (hamt_->solver_.GetConfig().mesh_type == Solver::REGULAR) {
        ChecArgvExact(3, argv);
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
            if (argv.size() == 3) {
                hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).thermal_conductivity =
                    std::stod(argv.at(2));
                std::cout << "SET SURFACE: " << argv.at(1) << " TO VALUE: "
                          << hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).thermal_conductivity
                          << std::endl;
            } else {
                const int N = (argv.size() - 2) / 2;
                for (int i = 2; i < 2 + N; i++) {
                    if (argv.at(i) == "k") {
                        hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).thermal_conductivity =
                            std::stod(argv.at(i + N));
                        std::cout << "SET THERMAL CONDUCTIVITY OF SURFACE: " << argv.at(1) << " TO VALUE: "
                                  << hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).thermal_conductivity
                                  << std::endl;
                    } else if (argv.at(i) == "c") {
                        hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).heat_capacity =
                            std::stod(argv.at(i + N));
                        std::cout << "SET HEAT CAPACITY OF SURFACE: " << argv.at(1) << " TO VALUE: "
                                  << hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).heat_capacity
                                  << std::endl;
                    } else if (argv.at(i) == "rho") {
                        hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).density = std::stod(argv.at(i + N));
                        std::cout << "SET DENSITY OF SURFACE: " << argv.at(1) << " TO VALUE: "
                                  << hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).density << std::endl;
                    } else if (argv.at(i) == "q") {
                        hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).volumetric_heat_source =
                            std::stod(argv.at(i + N));
                        std::cout << "SET VOLUMETRIC HEAT SOURCE OF SURFACE: " << argv.at(1) << " TO VALUE: "
                                  << hamt_->data_->mesh2d_triangular_.surfaces_.at(iter->second).volumetric_heat_source
                                  << std::endl;
                    } else {
                        throw CommandError("unknown surface property [" + argv.at(i) + "]", __PRETTY_FUNCTION__);
                    }
                }
            }
        } else {
            throw CommandError("unknown surface [" + argv.at(2) + "]", __PRETTY_FUNCTION__);
        }
    } else {
        throw CommandError("Command 'set boundary': undfedined mesh type.");
    }
}

}  // namespace hamt
