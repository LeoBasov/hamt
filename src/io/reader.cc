#include "reader.h"

namespace hamt {

Reader::Reader() {}

void Reader::SetData(const std::shared_ptr<Data>& data) { data_ = data; }

void Reader::ReadRegularMesh(const std::string& file_name) {
    std::string result(file_name.substr(file_name.rfind("."), file_name.size()));

    if (result == ".msh") {
        const double file_format(gmsh::GetFileFormat(file_name));

        if (std::floor(file_format) == 2.0) {
            data_->mesh2d_regular_ = mesh_algorithms::MSH2ToMesh2DRegular(gmsh::ReadMSH2(file_name));
        } else {
            throw Exception("Undefined Gmsh file format [" + std::to_string(file_format) + "].", __PRETTY_FUNCTION__);
        }
    } else {
        throw Exception("Undefined file format [" + result + "].", __PRETTY_FUNCTION__);
    }
}

void Reader::ReadTriangularMesh(const std::string& file_name) {
    std::string result(file_name.substr(file_name.rfind("."), file_name.size()));

    if (result == ".msh") {
        const double file_format(gmsh::GetFileFormat(file_name));

        if (std::floor(file_format) == 2.0) {
            data_->mesh2d_triangular_ = mesh_algorithms::MSH2ToMesh2DTriangular(gmsh::ReadMSH2(file_name));
        } else {
            throw Exception("Undefined Gmsh file format [" + std::to_string(file_format) + "].", __PRETTY_FUNCTION__);
        }
    } else {
        throw Exception("Undefined file format [" + result + "].", __PRETTY_FUNCTION__);
    }
}

}  // namespace hamt
