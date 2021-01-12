#pragma once

#include <map>

#include "../exception/commanderror.h"
#include "../hamt/hamt.h"
#include "operation.h"
#include "opr_clear/operation_clear.h"
#include "opr_info/operation_info.h"
#include "opr_load/operation_load.h"
#include "opr_read/operation_read.h"
#include "opr_set/operation_set.h"
#include "parser.h"

namespace hamt {
class Controller {
   public:
    Controller();
    ~Controller() = default;

    void ProcessCommand(const Command& command, const bool& test_mode);
    std::map<std::string, std::shared_ptr<Operation>> GetOperations() const;
    void SetRelDir(const std::string& rel_dir);

   private:
    std::shared_ptr<HAMT> hamt_;
    std::map<std::string, std::shared_ptr<Operation>> operations_;

    void SetUpOperations();
};
}  // namespace hamt
