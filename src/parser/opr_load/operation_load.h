#pragma once

#include <iostream>
#include <sstream>

#include "../../exception/commanderror.h"
#include "../../exception/load_pass.h"
#include "../operation.h"

namespace hamt {
class OperationLoad : public Operation {
   public:
    OperationLoad();
    ~OperationLoad() override = default;

    void Check(const std::vector<std::string>& argv) override;
    std::string GetHelp() const override;
    virtual void Execute(const std::vector<std::string>& argv, const bool& test_mode = false) override;
};
}  // namespace hamt
