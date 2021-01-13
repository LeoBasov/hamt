#include "writer.h"

namespace hamt {

Writer::Writer() {}

void Writer::SetData(const std::shared_ptr<Data>& data) { data_ = data; }

void Writer::Initialize(const std::vector<Config>& configs) { configs_ = configs; }

void Writer::Write(const uint& iter) {
    for (const Config& config : configs_) {
        if (!(iter % config.frequency)) {
            switch (config.mesh_type) {
                case REGULAR: {
                    WriteRegularMesh(config);
                    break;
                }
                default: {
                    throw Exception("Undefined mesh type [" + std::to_string(config.mesh_type) + "].",
                                    __PRETTY_FUNCTION__);
                }
            }
        }
    }
}

void Writer::WriteRegularMesh(const Config& config) {
    switch (config.file_format) {
        case VTK: {
            throw IncompleteCodeError(__PRETTY_FUNCTION__);
            break;
        }
        default: {
            throw Exception("Undefined file format [" + std::to_string(config.mesh_type) + "].", __PRETTY_FUNCTION__);
        }
    }
}

}  // namespace hamt
