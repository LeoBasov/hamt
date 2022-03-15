#include "data.h"

namespace hamt {

Data::Data() {}

void Data::Clear() {
    mesh2d_regular_.Clear();
    mesh2d_triangular_.Clear();
    results_.resize(0);
}

}  // namespace hamt
