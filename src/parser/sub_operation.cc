#include "sub_operation.h"

namespace hamt {

SubOperation::SubOperation() : Operation() {}

SubOperation::SubOperation(std::string command_name, std::string name) : Operation(name), command_name_(command_name) {}

void SubOperation::ChecArgvMin(const uint& min, const std::vector<std::string>& argv) const {
    if (argv.size() < min) {
        throw CommandError("command '" + command_name_ + "' parameter '" + name_ + "' must not have less then '" +
                           std::to_string(min) + "' argument(s)");
    }
}

void SubOperation::ChecArgvMax(const uint& max, const std::vector<std::string>& argv) const {
    if (argv.size() > max) {
        throw CommandError("command '" + command_name_ + "' parameter '" + name_ + "' must not have more then '" +
                           std::to_string(max) + "' argument(s)");
    }
}

void SubOperation::ChecArgvExact(const uint& size, const std::vector<std::string>& argv) const {
    if (argv.size() != size) {
        throw CommandError("command '" + command_name_ + "' parameter '" + name_ + "' must have '" +
                           std::to_string(size) + "' argument(s)");
    }
}

void SubOperation::ChecArgvExact(const uint& size, const uint& considered_args,
                                 const std::vector<std::string>& argv) const {
    std::stringstream ss;

    if (argv.size() != size) {
        ss << "command '" + command_name_ + "' parameter '" + name_ + "'";

        for (uint i = 1; i < considered_args; i++) {
            ss << " '" << argv.at(i) << "'";
        }

        ss << " must have '" + std::to_string(size) + "' argument(s)";

        throw CommandError(ss.str());
    }
}

}  // namespace hamt
