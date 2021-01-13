#include "operation_clear.h"

namespace hamt {

OperationClear::OperationClear() : Operation("clear") {}

void OperationClear::Execute(const std::vector<std::string>& argv, const bool&) {
    if (argv.at(0) == "reg_mesh") {
        hamt_->data_->mesh2d_regular_.Clear();

        std::cout << "REGULAR MESH CLEARED" << std::endl;
    } else {
        throw CommandError("Command 'read' undfedined argument [" + argv.at(0) + "].");
    }
}

void OperationClear::Check(const std::vector<std::string>& argv) { ChecArgvExact(1, argv); }

std::string OperationClear::GetHelp() const {
    const std::string tab("    ");
    std::stringstream ss;

    ss << tab << name_ << " <object> <id> <value, ...> :" << tab;
    ss << "Clears selected data." << std::endl;

    for (auto bin : sub_operations_) {
        ss << tab << tab << tab << tab << "- " << bin.first << std::endl;
    }

    return ss.str();
}

}  // namespace hamt
