#include "hamt.h"

namespace hamt {

HAMT::HAMT() {
    data_ = std::make_shared<Data>();

    reader_.SetData(data_);
    writer_.SetData(data_);
    solver_.SetData(data_);
}

}  // namespace hamt
