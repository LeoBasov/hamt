#include "controller.h"

namespace hamt {

Controller::Controller() {
    hamt_ = std::make_shared<HAMT>();
    SetUpOperations();

    for (auto &bin : operations_) {
        bin.second->SetHAMT(hamt_);
    }
}

void Controller::ProcessCommand(const Command &command, const bool &test_mode) {
    auto itter(operations_.find(command.name));

    if (itter != operations_.end()) {
        itter->second->Execute(command.argv, test_mode);
    } else if (!command.name.empty()) {
        throw CommandError("command '" + command.name + "' is not defined");
    }
}

void Controller::SetUpOperations() {}

std::map<std::string, std::shared_ptr<Operation>> Controller::GetOperations() const { return operations_; }

void Controller::SetRelDir(const std::string &rel_dir) { rel_dir_ = rel_dir; }

}  // namespace hamt
