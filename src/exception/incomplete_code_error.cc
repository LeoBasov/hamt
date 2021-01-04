#include "incomplete_code_error.h"

namespace hamt {

IncompleteCodeError::IncompleteCodeError(const std::string &what) : Exception(what, "") {}

}  // namespace hamt
