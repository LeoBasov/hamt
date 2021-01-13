#pragma once

#include <iostream>

#include "../../exception/commanderror.h"
#include "../../exception/incomplete_code_error.h"
#include "../operation.h"

namespace hamt {
class OperationRead : public Operation {
   public:
    OperationRead();
    ~OperationRead() override = default;

    void Check(const std::vector<std::string>& argv) override;
    std::string GetHelp() const override;
    virtual void Execute(const std::vector<std::string>& argv, const bool& test_mode = false) override;
};
}  // namespace hamt
