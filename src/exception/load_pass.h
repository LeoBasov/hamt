#pragma once

#include "exception.h"

namespace hamt {
class LoadPass : public Exception {
   public:
    LoadPass(const std::string& what);
    ~LoadPass() = default;
};
}  // namespace hamt
