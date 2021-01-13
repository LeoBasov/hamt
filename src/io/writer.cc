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
            if (data_->results_.size()) {
                std::pair<std::string, std::vector<double>> vec{"temperature",
                                                                std::vector<double>(data_->results_.size())};

                for (uint i = 0; i < vec.second.size(); i++) {
                    vec.second.at(i) = data_->results_(i);
                }

                vtk::unstructured_grid::WriteMesh2DRegular(data_->mesh2d_regular_, config.file_name, {vec});
            } else {
                vtk::unstructured_grid::WriteMesh2DRegular(data_->mesh2d_regular_, config.file_name, {});
            }
            break;
        }
        default: {
            throw Exception("Undefined file format [" + std::to_string(config.mesh_type) + "].", __PRETTY_FUNCTION__);
        }
    }
}

}  // namespace hamt
