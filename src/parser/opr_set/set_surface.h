#pragma once

#include <iostream>

#include "../../exception/incomplete_code_error.h"
#include "../sub_operation.h"

namespace hamt {

class SetSurface : public SubOperation {
   public:
    SetSurface();
    SetSurface(std::string command_name);
    ~SetSurface() = default;

    virtual std::string GetHelp() const override;
    virtual void Execute(const std::vector<std::string>& argv, const bool& test_mode = false) override;

   private:
    virtual void Check(const std::vector<std::string>& argv) override;
};

}  // namespace hamt
