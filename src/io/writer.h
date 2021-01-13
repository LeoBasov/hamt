#pragma once

#include <memory>

#include "../exception/incomplete_code_error.h"
#include "../hamt/data.h"

namespace hamt {
using namespace Eigen;
class Writer {
   public:
    enum MeshType { REGULAR };
    enum FileFormat { VTK };

    struct Config {
        MeshType mesh_type = REGULAR;
        FileFormat file_format = VTK;
        uint frequency = 1;
        std::string file_name;
    };

    Writer();
    ~Writer() = default;

    void SetData(const std::shared_ptr<Data>& data);
    void Initialize(const std::vector<Config>& configs);
    void Write(const uint& iter);

   private:
    std::shared_ptr<Data> data_;
    std::vector<Config> configs_;

    void WriteRegularMesh(const Config& config);
};
}  // namespace hamt
