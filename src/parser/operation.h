#pragma once

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../common/timer.h"
#include "../exception/commanderror.h"
#include "../hamt/hamt.h"

namespace hamt {
class Operation {
   public:
    Operation();
    Operation(std::string name);
    virtual ~Operation() = default;

    void SetHAMT(const std::shared_ptr<HAMT>& hamt);
    virtual void Execute(const std::vector<std::string>& argv, const bool& test_mode = false);

    std::string GetName() const;
    virtual std::string GetHelp() const = 0;
    virtual void Check(const std::vector<std::string>& argv) = 0;

   protected:
    std::string name_;
    std::shared_ptr<HAMT> hamt_;
    std::map<std::string, std::shared_ptr<Operation>> sub_operations_;

    virtual void ChecArgvMin(const uint& min, const std::vector<std::string>& argv) const;
    virtual void ChecArgvMax(const uint& max, const std::vector<std::string>& argv) const;
    virtual void ChecArgvExact(const uint& size, const std::vector<std::string>& argv) const;
    virtual void ChecArgvExact(const uint& size, const uint& considered_args,
                               const std::vector<std::string>& argv) const;
};
}  // namespace hamt
