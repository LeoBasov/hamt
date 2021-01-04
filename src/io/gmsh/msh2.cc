#include "msh2.h"

namespace hamt {
namespace gmsh {
using namespace Eigen;

MSH2::MSH2() {}

void MSH2::Clear() {
    nodes_.clear();
    elements_.clear();
}

}  // namespace gmsh
}  // namespace hamt
