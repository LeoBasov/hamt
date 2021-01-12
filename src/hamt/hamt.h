#pragma once

#include <memory>

#include "../io/reader.h"
#include "data.h"

namespace hamt {
class HAMT {
   public:
    HAMT();
    ~HAMT() = default;

    std::shared_ptr<Data> data_;
    Reader reader_;
};
}  // namespace hamt
