#pragma once

#include <iostream>

#include "../../exception/commanderror.h"
#include "../../exception/incomplete_code_error.h"
#include "../operation.h"
#include "set_reg_mesh.h"
#include "set_solver.h"
#include "set_writer.h"
#include "set_trinagl_mesh.h"

namespace hamt {
class OperationSet : public Operation {
   public:
    OperationSet();
    ~OperationSet() override = default;

    void Check(const std::vector<std::string>& argv) override;
    std::string GetHelp() const override;
};
}  // namespace hamt
