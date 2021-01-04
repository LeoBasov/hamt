#include "commanderror.h"

namespace hamt {

CommandError::CommandError(const std::string &what, const std::string &where) : Exception(what, where) {}

}  // namespace hamt
