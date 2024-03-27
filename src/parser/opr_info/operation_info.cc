#include "operation_info.h"

namespace hamt {

OperationInfo::OperationInfo() : Operation("info") {}

void OperationInfo::Execute(const std::vector<std::string>& argv, const bool&) {
    const std::string tab("    ");

    if (hamt_->solver_.GetConfig().mesh_type == Solver::REGULAR) {
        std::cout << "REGULAR MESH INFO" << std::endl;
        std::cout << "NUMBER NODES : " << hamt_->data_->mesh2d_regular_.nodes_.size() << std::endl;
        std::cout << "NUMBER CELLS : " << hamt_->data_->mesh2d_regular_.cells_.size() << std::endl;

        std::cout << "BOUNDARIES: " << hamt_->data_->mesh2d_regular_.boundaries_.size() << std::endl;
        for (const auto& boundary_name_bin : hamt_->data_->mesh2d_regular_.boundary_names_) {
            const Mesh2DRegular::Boundary boundary(
                hamt_->data_->mesh2d_regular_.boundaries_.at(boundary_name_bin.second));

            std::cout << tab << boundary_name_bin.first << " ";

            switch (boundary.type) {
                case Mesh2DRegular::DIRICHLET: {
                    std::cout << "TYPE: DIRICHLET"
                              << " ";
                    break;
                }
                case Mesh2DRegular::NEUMANN: {
                    std::cout << "TYPE: NEUMANN"
                              << " ";
                    break;
                }
                case Mesh2DRegular::RADIATION: {
                    std::cout << "TYPE: RADIATION"
                              << " ";
                    break;
                }
            }

            std::cout << "VALUE: " << boundary.value << std::endl;
        }

        std::cout << "SURFACES: " << hamt_->data_->mesh2d_regular_.surfaces_.size() << std::endl;
        for (const auto& bin : hamt_->data_->mesh2d_regular_.surface_names_) {
            const Mesh2DRegular::Surface surface(hamt_->data_->mesh2d_regular_.surfaces_.at(bin.second));

            std::cout << tab << bin.first << " ";
            std::cout << "THERM. CONDUCT.: " << surface.thermal_conductivity << std::endl;
        }
    } else if (hamt_->solver_.GetConfig().mesh_type == Solver::TRIANGULAR) {
        std::cout << "TRIANGULAR MESH INFO" << std::endl;
        std::cout << "NUMBER NODES : " << hamt_->data_->mesh2d_triangular_.nodes_.size() << std::endl;
        std::cout << "NUMBER CELLS : " << hamt_->data_->mesh2d_triangular_.cells_.size() << std::endl;

        std::cout << "BOUNDARIES: " << hamt_->data_->mesh2d_triangular_.boundaries_.size() << std::endl;
        for (const auto& boundary_name_bin : hamt_->data_->mesh2d_triangular_.boundary_names_) {
            const Mesh2DTriangular::Boundary boundary(
                hamt_->data_->mesh2d_triangular_.boundaries_.at(boundary_name_bin.second));

            std::cout << tab << boundary_name_bin.first << " ";

            switch (boundary.type) {
                case Mesh2DTriangular::DIRICHLET: {
                    std::cout << "TYPE: DIRICHLET"
                              << " ";
                    break;
                }
                case Mesh2DTriangular::NEUMANN: {
                    std::cout << "TYPE: NEUMANN"
                              << " ";
                    break;
                }
                case Mesh2DTriangular::RADIATION: {
                    std::cout << "TYPE: RADIATION"
                              << " ";
                    break;
                }
                case Mesh2DTriangular::HEAT_FLUX: {
                    std::cout << "TYPE: HEAT_FLUX"
                              << " ";
                    break;
                }
            }

            std::cout << "VALUE: " << boundary.value << std::endl;
        }

        std::cout << "SURFACES: " << hamt_->data_->mesh2d_triangular_.surfaces_.size() << std::endl;
        for (const auto& bin : hamt_->data_->mesh2d_triangular_.surface_names_) {
            const Mesh2DTriangular::Surface surface(hamt_->data_->mesh2d_triangular_.surfaces_.at(bin.second));

            std::cout << tab << bin.first << " ";
            std::cout << "THERM. CONDUCT.: " << surface.thermal_conductivity << std::endl;
        }
    } else {
        throw CommandError("Command 'read' undfedined argument [" + argv.at(0) + "].");
    }
}

void OperationInfo::Check(const std::vector<std::string>& argv) { ChecArgvExact(0, argv); }

std::string OperationInfo::GetHelp() const {
    const std::string tab("    ");
    std::stringstream ss;

    ss << tab << name_ << " <object> <id> <value, ...> :" << tab;
    ss << "Displays info of selected object." << std::endl;

    for (auto bin : sub_operations_) {
        ss << tab << tab << tab << tab << "- " << bin.first << std::endl;
    }

    return ss.str();
}

}  // namespace hamt
