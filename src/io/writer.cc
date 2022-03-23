#include "writer.h"

namespace hamt {

Writer::Writer() {
    std::map<FileFormat, Config> file_configs;

    // extend here for more file formats
    file_configs[VTK] = Config();
    file_configs[CSV] = Config();

    // extend here for more meshes
    configs_[REGULAR] = file_configs;
    configs_[TRIANGULAR] = file_configs;
}

void Writer::SetData(const std::shared_ptr<Data>& data) { data_ = data; }

void Writer::SetConfig(const MeshType mesh_type, const FileFormat file_format, const Config& config) {
    configs_.at(mesh_type).at(file_format) = config;
}

Writer::Config Writer::GetConfig(const MeshType mesh_type, const FileFormat file_format) const {
    const auto iter_mesh(configs_.find(mesh_type));

    if (iter_mesh != configs_.end()) {
        const auto iter_type(iter_mesh->second.find(file_format));

        if (iter_type != iter_mesh->second.end()) {
            return iter_type->second;
        } else {
            throw Exception("Undefined FileFormat [" + std::to_string(file_format) + "]", __PRETTY_FUNCTION__);
        }
    } else {
        throw Exception("Undefined MeshType [" + std::to_string(mesh_type) + "]", __PRETTY_FUNCTION__);
    }
}

void Writer::Write(const uint& iter) {
    for (const auto& config_bins : configs_) {
        switch (config_bins.first) {
            case REGULAR: {
                WriteRegularMesh(config_bins.second, iter);
                break;
            }
            case TRIANGULAR: {
                WriteTriangularMesh(config_bins.second, iter);
                break;
            }
            default: {
                throw Exception("Undefined mesh type [" + std::to_string(config_bins.first) + "].",
                                __PRETTY_FUNCTION__);
            }
        }
    }
}

void Writer::WriteRegularMesh(const std::map<FileFormat, Config>& configs, const uint& iter) {
    for (const auto& bin : configs) {
        if (!(iter % bin.second.frequency) && bin.second.activated) {
            switch (bin.first) {
                case VTK: {
                    if (data_->results_.size()) {
                        std::pair<std::string, std::vector<double>> vec{"temperature",
                                                                        std::vector<double>(data_->results_.size())};

                        for (uint i = 0; i < vec.second.size(); i++) {
                            vec.second.at(i) = data_->results_(i);
                        }

                        vtk::unstructured_grid::WriteMesh2DRegular(data_->mesh2d_regular_,
                                                                   bin.second.file_name + ".vtu", {vec});
                    } else {
                        vtk::unstructured_grid::WriteMesh2DRegular(data_->mesh2d_regular_,
                                                                   bin.second.file_name + ".vtu", {});
                    }
                    break;
                }
                case CSV: {
                    std::ofstream stream(bin.second.file_name + ".csv");

                    if (!stream.is_open()) {
                        throw Exception("Could not open file [" + bin.second.file_name + ".csv" + "]",
                                        __PRETTY_FUNCTION__);
                    }

                    if (data_->results_.size()) {
                        for (uint i = 0; i < data_->mesh2d_regular_.nodes_.size(); i++) {
                            const Vector3d position(data_->mesh2d_regular_.nodes_.at(i).position);

                            stream << data_->results_(i) << "," << position(0) << "," << position(1) << ","
                                   << position(2) << std::endl;
                        }
                    } else {
                        for (uint i = 0; i < data_->mesh2d_regular_.nodes_.size(); i++) {
                            const Vector3d position(data_->mesh2d_regular_.nodes_.at(i).position);

                            stream << 0.0 << "," << position(0) << "," << position(1) << "," << position(2)
                                   << std::endl;
                        }
                    }

                    stream.close();
                    break;
                }
                default: {
                    throw Exception("Undefined file format [" + std::to_string(bin.first) + "].", __PRETTY_FUNCTION__);
                }
            }
        }
    }
}

void Writer::WriteTriangularMesh(const std::map<FileFormat, Config>& configs, const uint& iter) {
    for (const auto& bin : configs) {
        if (!(iter % bin.second.frequency) && bin.second.activated) {
            switch (bin.first) {
                case VTK: {
                    if (data_->results_.size()) {
                        std::pair<std::string, std::vector<double>> vec{"temperature",
                                                                        std::vector<double>(data_->results_.size())};

                        for (uint i = 0; i < vec.second.size(); i++) {
                            vec.second.at(i) = data_->results_(i);
                        }

                        vtk::unstructured_grid::WriteMesh2DTriangular(data_->mesh2d_triangular_,
                                                                      bin.second.file_name + ".vtu", {vec});
                    } else {
                        vtk::unstructured_grid::WriteMesh2DTriangular(data_->mesh2d_triangular_,
                                                                      bin.second.file_name + ".vtu", {});
                    }
                    break;
                }
                case CSV: {
                    std::ofstream stream(bin.second.file_name + ".csv");

                    if (!stream.is_open()) {
                        throw Exception("Could not open file [" + bin.second.file_name + ".csv" + "]",
                                        __PRETTY_FUNCTION__);
                    }

                    if (data_->results_.size()) {
                        for (uint i = 0; i < data_->mesh2d_triangular_.nodes_.size(); i++) {
                            const Vector3d position(data_->mesh2d_triangular_.nodes_.at(i).position);

                            stream << data_->results_(i) << "," << position(0) << "," << position(1) << ","
                                   << position(2) << std::endl;
                        }
                    } else {
                        for (uint i = 0; i < data_->mesh2d_triangular_.nodes_.size(); i++) {
                            const Vector3d position(data_->mesh2d_triangular_.nodes_.at(i).position);

                            stream << 0.0 << "," << position(0) << "," << position(1) << "," << position(2)
                                   << std::endl;
                        }
                    }

                    stream.close();
                    break;
                }
                default: {
                    throw Exception("Undefined file format [" + std::to_string(bin.first) + "].", __PRETTY_FUNCTION__);
                }
            }
        }
    }
}

}  // namespace hamt
