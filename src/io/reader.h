#pragma once

#include <memory>

#include "../hamt/data.h"
#include "../mesh/mesh_algorithms.h"
#include "gmsh/gmsh.h"

namespace hamt {
class Reader {
   public:
    Reader();
    ~Reader() = default;

    void SetData(const std::shared_ptr<Data>& data);

    void ReadRegularMesh(const std::string& file_name);

   private:
    std::shared_ptr<Data> data_;
};
}  // namespace hamt
