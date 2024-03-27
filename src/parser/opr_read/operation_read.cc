#include "operation_read.h"

namespace hamt {

OperationRead::OperationRead() : Operation("read") {}

void OperationRead::Execute(const std::vector<std::string>& argv, const bool&) {
    Solver::Config config(hamt_->solver_.GetConfig());

    if (argv.at(0) == "reg_mesh") {
        hamt_->reader_.ReadRegularMesh(rel_dir_ + argv.at(1));
        hamt_->data_->mesh2d_triangular_.Clear();
        config.mesh_type = Solver::REGULAR;
        hamt_->solver_.SetConfig(config);

        std::cout << "SET SOLVER MESH TYPE: REGULAR" << std::endl;
        std::cout << "REGULAR MESH LOADED" << std::endl;
        std::cout << "NUMBER NODES : " << hamt_->data_->mesh2d_regular_.nodes_.size() << std::endl;
        std::cout << "NUMBER CELLS : " << hamt_->data_->mesh2d_regular_.cells_.size() << std::endl;
        std::cout << "BOUNDARIES: " << hamt_->data_->mesh2d_regular_.boundaries_.size() << std::endl;
        std::cout << "SURFACES: " << hamt_->data_->mesh2d_regular_.surfaces_.size() << std::endl;
    } else if (argv.at(0) == "triangl_mesh") {
        hamt_->reader_.ReadTriangularMesh(rel_dir_ + argv.at(1));
        hamt_->data_->mesh2d_regular_.Clear();
        config.mesh_type = Solver::TRIANGULAR;
        hamt_->solver_.SetConfig(config);

        std::cout << "SET SOLVER MESH TYPE: TRIANGULAR" << std::endl;
        std::cout << "TRIANGULAR MESH LOADED" << std::endl;
        std::cout << "NUMBER NODES : " << hamt_->data_->mesh2d_triangular_.nodes_.size() << std::endl;
        std::cout << "NUMBER CELLS : " << hamt_->data_->mesh2d_triangular_.cells_.size() << std::endl;
        std::cout << "BOUNDARIES: " << hamt_->data_->mesh2d_triangular_.boundaries_.size() << std::endl;
        std::cout << "SURFACES: " << hamt_->data_->mesh2d_triangular_.surfaces_.size() << std::endl;
    } else {
        throw CommandError("Command 'read' undfedined argument [" + argv.at(0) + "].");
    }
}

void OperationRead::Check(const std::vector<std::string>& argv) { ChecArgvExact(2, argv); }

std::string OperationRead::GetHelp() const {
    const std::string tab("    ");
    std::stringstream ss;

    ss << tab << name_ << " <object> <id> <value, ...> :" << tab;
    ss << "Read a file of external format." << std::endl;

    for (auto bin : sub_operations_) {
        ss << tab << tab << tab << tab << "- " << bin.first << std::endl;
    }

    return ss.str();
}

}  // namespace hamt
