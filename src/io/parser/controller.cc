#include "controller.h"

namespace hamt {

Controller::Controller() {
    core_ = std::make_shared<Core>();
    SetUpOperations();

    for (auto &bin : operations_) {
        bin.second->SetCore(core_);
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

void Controller::SetRelDir(const std::string &rel_dir) { core_->rel_dir_ = rel_dir; }

}  // namespace hamt
