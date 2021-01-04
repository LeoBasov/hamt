#pragma once

#include "exception.h"

namespace hamt {
class IncompleteCodeError : public Exception {
   public:
    IncompleteCodeError(const std::string& what);
    ~IncompleteCodeError() = default;
};
}  // namespace hamt
