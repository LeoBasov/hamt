#include "exception.h"

namespace hamt {

Exception::Exception(const std::string& what, const std::string& where) : what_(what), where_(where) {}

const char* Exception::what() const throw() { return what_.c_str(); }

std::string Exception::where() const throw() { return where_; }

}  // namespace hamt
