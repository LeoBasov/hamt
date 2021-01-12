#include "operation_read.h"

namespace hamt {

OperationRead::OperationRead() : Operation("read") {}

void OperationRead::Execute(const std::vector<std::string>& argv, const bool&) {
    throw IncompleteCodeError(__PRETTY_FUNCTION__);
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
