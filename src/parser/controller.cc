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
        itter->second->Check(command.argv);
        itter->second->Execute(command.argv, test_mode);
    } else if (!command.name.empty()) {
        throw CommandError("command '" + command.name + "' is not defined");
    }
}

void Controller::SetUpOperations() {
    std::shared_ptr<Operation> load(std::make_shared<OperationLoad>());
    std::shared_ptr<Operation> read(std::make_shared<OperationRead>());
    std::shared_ptr<OperationClear> clear(std::make_shared<OperationClear>());
    std::shared_ptr<OperationInfo> info(std::make_shared<OperationInfo>());
    std::shared_ptr<OperationSet> set(std::make_shared<OperationSet>());
    std::shared_ptr<OperationRun> run(std::make_shared<OperationRun>());

    operations_[load->GetName()] = load;
    operations_[read->GetName()] = read;
    operations_[clear->GetName()] = clear;
    operations_[info->GetName()] = info;
    operations_[set->GetName()] = set;
    operations_[run->GetName()] = run;
}

std::map<std::string, std::shared_ptr<Operation>> Controller::GetOperations() const { return operations_; }

void Controller::SetRelDir(const std::string &rel_dir) {
    for (auto &bin : operations_) {
        bin.second->SetRelDir(rel_dir);
    }
}

}  // namespace hamt
