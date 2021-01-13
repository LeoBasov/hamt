#pragma once

#include <memory>

#include "../exception/incomplete_code_error.h"
#include "../hamt/data.h"
#include "vtk/unstructured_grid.h"

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
        bool activated = false;
    };

    Writer();
    ~Writer() = default;

    void SetData(const std::shared_ptr<Data>& data);
    void Initialize(const MeshType mesh_type, const FileFormat file_format, const Config& config);
    void Write(const uint& iter);

   private:
    std::shared_ptr<Data> data_;
    std::map<MeshType, std::map<FileFormat, Config>> configs_;

    void WriteRegularMesh(const std::map<FileFormat, Config>& configs, const uint& iter);
};
}  // namespace hamt
