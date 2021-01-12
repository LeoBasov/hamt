#pragma once

#include <memory>

#include "data.h"

namespace hamt {
class HAMT {
   public:
    HAMT();
    ~HAMT() = default;

    std::shared_ptr<Data> data_;
};
}  // namespace hamt
