#include "operation_load.h"

namespace hamt {

OperationLoad::OperationLoad() : Operation("load") {}

void OperationLoad::Execute(const std::vector<std::string>& argv, const bool&) { throw LoadPass(argv.front()); }

void OperationLoad::Check(const std::vector<std::string>& argv) { ChecArgvExact(1, argv); }

std::string OperationLoad::GetHelp() const {
    const std::string tab("    ");
    std::stringstream ss;

    ss << tab << name_ << " <object> <id> <value, ...> :" << tab;
    ss << "Loads an additional input in place." << std::endl;

    for (auto bin : sub_operations_) {
        ss << tab << tab << tab << tab << "- " << bin.first << std::endl;
    }

    return ss.str();
}

}  // namespace hamt
