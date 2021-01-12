#include "set_reg_mesh.h"

namespace hamt {

SetRegularMesh::SetRegularMesh(std::string command_name) : SubOperation(command_name, "reg_mesh") {}

SetRegularMesh::SetRegularMesh() : SubOperation() {}

std::string SetRegularMesh::GetHelp() const { return "Sets parameters for regular mesh"; }

void SetRegularMesh::Check(const std::vector<std::string>& argv) { ChecArgvExact(4, argv); }

void SetRegularMesh::Execute(const std::vector<std::string>& argv, const bool&) {
    if (argv.at(1) == "bound_type") {
        auto iter(hamt_->data_->mesh2d_regular_.boundary_names_.find(argv.at(2)));

        if (iter != hamt_->data_->mesh2d_regular_.boundary_names_.end()) {
            if (argv.at(3) == "dirichlet") {
                hamt_->data_->mesh2d_regular_.boundaries_.at(iter->second).type = Mesh2DRegular::DIRICHLET;
                std::cout << "SET BOUNDARY: " << argv.at(2) << " TO DIRICHLET" << std::endl;
            } else if (argv.at(3) == "neumann") {
                hamt_->data_->mesh2d_regular_.boundaries_.at(iter->second).type = Mesh2DRegular::NEUMANN;
                std::cout << "SET BOUNDARY: " << argv.at(2) << " TO NEUMANN" << std::endl;
            } else {
                throw CommandError("unknown boundary type [" + argv.at(3) + "]", __PRETTY_FUNCTION__);
            }
        } else {
            throw CommandError("unknown boundary [" + argv.at(2) + "]", __PRETTY_FUNCTION__);
        }
    } else if (argv.at(1) == "bound_value") {
        throw IncompleteCodeError(__PRETTY_FUNCTION__);
    } else if (argv.at(1) == "bound_value") {
        throw IncompleteCodeError(__PRETTY_FUNCTION__);
    } else {
        throw CommandError("unknown command 'set reg_mesh' [" + argv.at(1) + "]", __PRETTY_FUNCTION__);
    }
}

}  // namespace hamt
