#include "unstructured_grid.h"

namespace hamt {
namespace vtk {
namespace unstructured_grid {

void WriteMesh2DRegular(const Mesh2DRegular &mesh, const std::string &file_name,
                        const std::vector<std::pair<std::string, std::vector<double>>> &point_data) {
    std::ofstream stream(file_name);

    if (!stream.is_open()) {
        throw Exception("Could not open file [" + file_name + "].", __PRETTY_FUNCTION__);
    } else {
        WriteHeader(stream);
        WriteBody(stream, mesh, point_data);
        WriteFooter(stream);
    }

    stream.close();
}

void WriteHeader(std::ofstream &stream) {
    stream << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">" << std::endl;
}

void WriteFooter(std::ofstream &stream) { stream << "</VTKFile>" << std::endl; }

void WriteBody(std::ofstream &stream, const Mesh2DRegular &mesh,
               const std::vector<std::pair<std::string, std::vector<double>>> &point_data) {
    stream << "<UnstructuredGrid>" << std::endl;
    stream << "<Piece NumberOfPoints=\"" << mesh.nodes_.size() << "\" NumberOfCells=\"" << mesh.cells_.size() << "\">"
           << std::endl;

    WritePoints(stream, mesh);
    WriteCells(stream, mesh);
    // WriteCellData();

    if (point_data.size()) {
        WritePointData(stream, point_data);
    }

    stream << "</Piece>" << std::endl;
    stream << "</UnstructuredGrid>" << std::endl;
}

void WritePoints(std::ofstream &stream, const Mesh2DRegular &mesh) {
    stream << "<Points>" << std::endl;
    stream << "<DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">" << std::endl;

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        stream << mesh.nodes_.at(i).position(0) << " ";
        stream << mesh.nodes_.at(i).position(1) << " ";
        stream << mesh.nodes_.at(i).position(2) << " ";
    }

    stream << "</DataArray>" << std::endl;
    stream << "</Points>" << std::endl;
}

void WriteCells(std::ofstream &stream, const Mesh2DRegular &mesh) {
    stream << "<Cells>" << std::endl;

    stream << "<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">" << std::endl;

    for (uint i = 0; i < mesh.cells_.size(); i++) {
        stream << mesh.cells_.at(i).node1 << " ";
        stream << mesh.cells_.at(i).node2 << " ";
        stream << mesh.cells_.at(i).node3 << " ";
        stream << mesh.cells_.at(i).node4 << " ";
    }

    stream << "</DataArray>" << std::endl;

    stream << "<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">" << std::endl;

    for (uint i = 0; i < mesh.cells_.size(); i++) {
        stream << (i + 1) * 4 << " ";
    }

    stream << "</DataArray>" << std::endl;

    stream << "<DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">" << std::endl;

    for (uint i = 0; i < mesh.cells_.size(); i++) {
        stream << 9 << " ";
    }

    stream << "</DataArray>" << std::endl;

    stream << "</Cells>" << std::endl;
}

void WritePointData(std::ofstream &stream, const std::vector<std::pair<std::string, std::vector<double>>> &point_data) {
    stream << "<PointData>" << std::endl;

    for (const auto &data : point_data) {
        stream << "<DataArray type=\"Float32\" Name=\"" + data.first + "\" format=\"ascii\">" << std::endl;

        for (const auto &value : data.second) {
            stream << value << " ";
        }

        stream << "</DataArray>" << std::endl;
    }

    stream << "</PointData>" << std::endl;
}

}  // namespace unstructured_grid
}  // namespace vtk
}  // namespace hamt
