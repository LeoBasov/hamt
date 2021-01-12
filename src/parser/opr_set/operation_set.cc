#include "operation_set.h"

namespace hamt {

OperationSet::OperationSet() : Operation("set") {
    std::shared_ptr<class SetRegularMesh> set_reg_mesh(std::make_shared<class SetRegularMesh>(name_));

    sub_operations_[set_reg_mesh->GetName()] = set_reg_mesh;
}

void OperationSet::Check(const std::vector<std::string>& argv) { ChecArgvExact(4, argv); }

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
