#pragma once

#include <string>

namespace hamt {
class Core {
   public:
    Core();
    ~Core() = default;

    std::string rel_dir_;
};
}  // namespace hamt
