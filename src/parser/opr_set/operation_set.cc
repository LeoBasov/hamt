#include "operation_set.h"

namespace hamt {

OperationSet::OperationSet() : Operation("set") {
    std::shared_ptr<class SetWriter> set_writer(std::make_shared<class SetWriter>(name_));
    std::shared_ptr<class SetSolver> set_solver(std::make_shared<class SetSolver>(name_));
    std::shared_ptr<class SetBoundary> set_boundary(std::make_shared<class SetBoundary>(name_));

    sub_operations_[set_writer->GetName()] = set_writer;
    sub_operations_[set_solver->GetName()] = set_solver;
    sub_operations_[set_boundary->GetName()] = set_boundary;
}

void OperationSet::Check(const std::vector<std::string>& argv) { ChecArgvMin(3, argv); }

std::string OperationSet::GetHelp() const {
    const std::string tab("    ");
    std::stringstream ss;

    ss << tab << name_ << " <object> <id> <value, ...> :" << tab;
    ss << "Set properties of selected element." << std::endl;

    for (auto bin : sub_operations_) {
        ss << tab << tab << tab << tab << "- " << bin.first << std::endl;
    }

    return ss.str();
}

}  // namespace hamt
