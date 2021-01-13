#pragma once

#include "operation.h"

namespace hamt {
class SubOperation : public Operation {
   public:
    SubOperation();
    SubOperation(std::string command_name, std::string name);
    ~SubOperation() = default;

    virtual void Execute(const std::vector<std::string>& argv, const bool& test_mode = false) override = 0;

   protected:
    std::string command_name_;

    virtual void ChecArgvMin(const uint& min, const std::vector<std::string>& argv) const override;
    virtual void ChecArgvMax(const uint& max, const std::vector<std::string>& argv) const override;
    virtual void ChecArgvExact(const uint& size, const std::vector<std::string>& argv) const override;
    virtual void ChecArgvExact(const uint& size, const uint& considered_args,
                               const std::vector<std::string>& argv) const override;
};

}  // namespace hamt
