#include "operation_info.h"

namespace hamt {

OperationInfo::OperationInfo() : Operation("info") {}

void OperationInfo::Execute(const std::vector<std::string>& argv, const bool&) {
    const std::string tab("    ");

    if (argv.at(0) == "reg_mesh") {
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
            }

            std::cout << "VALUE: " << boundary.value << std::endl;
        }

        std::cout << "SURFACES: " << hamt_->data_->mesh2d_regular_.surfaces_.size() << std::endl;
        for (const auto& bin : hamt_->data_->mesh2d_regular_.surface_names_) {
            const Mesh2DRegular::Surface surface(hamt_->data_->mesh2d_regular_.surfaces_.at(bin.second));

            std::cout << tab << bin.first << " ";
            std::cout << "THERM. CONDUCT.: " << surface.thermal_conductivity << std::endl;
        }
    } else {
        throw CommandError("Command 'read' undfedined argument [" + argv.at(0) + "].");
    }
}

void OperationInfo::Check(const std::vector<std::string>& argv) { ChecArgvExact(1, argv); }

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
