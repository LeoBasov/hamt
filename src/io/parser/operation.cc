#include "operation.h"

namespace hamt {

Operation::Operation() {}

Operation::Operation(std::string name) : name_(name) {}

void Operation::SetCore(const std::shared_ptr<Core>& core) {
    core_ = core;

    for (auto& bin : sub_operations_) {
        bin.second->SetCore(core_);
    }
}

void Operation::Execute(const std::vector<std::string>& argv, const bool& test_mode) {
    Check(argv);
    auto itter(sub_operations_.find(argv.front()));

    if (itter != sub_operations_.end()) {
        itter->second->Check(argv);
        itter->second->Execute(argv, test_mode);
    } else {
        throw CommandError("command '" + name_ + "' argument '" + argv.at(0) + "' unknown.");
    }
}

void Operation::ChecArgvMin(const uint& min, const std::vector<std::string>& argv) const {
    if (argv.size() < min) {
        throw CommandError("command '" + name_ + "' must not have less then '" + std::to_string(min) + "' argument(s)");
    }
}

void Operation::ChecArgvMax(const uint& max, const std::vector<std::string>& argv) const {
    if (argv.size() > max) {
        throw CommandError("command '" + name_ + "' must not have more then '" + std::to_string(max) + "' argument(s)");
    }
}

void Operation::ChecArgvExact(const uint& size, const std::vector<std::string>& argv) const {
    if (argv.size() != size) {
        throw CommandError("command '" + name_ + "' must have '" + std::to_string(size) + "' argument(s)");
    }
}

void Operation::ChecArgvExact(const uint& size, const uint& considered_args,
                              const std::vector<std::string>& argv) const {
    std::stringstream ss;

    if (argv.size() != size) {
        ss << "command '" + name_ + "'";

        for (uint i = 0; i < considered_args; i++) {
            ss << " '" << argv.at(i) << "'";
        }

        ss << " must not have '" + std::to_string(size) + "' argument(s)";

        throw CommandError(ss.str());
    }
}

std::string Operation::GetName() const { return name_; }

}  // namespace hamt
