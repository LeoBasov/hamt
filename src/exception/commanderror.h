#pragma once

#include "exception.h"

namespace hamt {
class CommandError : public Exception {
   public:
    CommandError(const std::string& what, const std::string& where = "");
    ~CommandError() = default;
};
}  // namespace hamt
