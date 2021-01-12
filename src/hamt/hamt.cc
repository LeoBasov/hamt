#include "hamt.h"

namespace hamt {

HAMT::HAMT() {
    data_ = std::make_shared<Data>();

    reader_.SetData(data_);
}

}  // namespace hamt
