#include "unstructured_grid.h"

namespace hamt {
namespace vtk {
namespace unstructured_grid {

void WriteMesh2DRegular(const Mesh2DRegular &mesh, const std::string &file_name) {
    std::ofstream stream(file_name);

    if (stream.is_open()) {
        throw Exception("Could not open file [" + file_name + "].", __PRETTY_FUNCTION__);
    } else {
        WriteHeader(stream);
        WriteBody(stream, mesh);
        WriteFooter(stream);
    }

    stream.close();
}

void WriteHeader(std::ofstream &stream) {
    stream << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">" << std::endl;
}

void WriteFooter(std::ofstream &stream) { stream << "</VTKFile>" << std::endl; }

void WriteBody(std::ofstream &stream, const Mesh2DRegular &mesh) {
    stream << "<UnstructuredGrid>" << std::endl;
    stream << "<Piece NumberOfPoints=\"" << mesh.nodes_.size() << "\" NumberOfCells=\"" << mesh.cells_.size() << "\">"
           << std::endl;

    WritePoints(stream, mesh);
    WriteCells(stream, mesh);
    // WriteCellData();
    // WritePointData();

    stream << "</Piece>" << std::endl;
    stream << "</UnstructuredGrid>" << std::endl;
}

void WritePoints(std::ofstream &stream, const Mesh2DRegular &mesh) {
    stream << "<Points>" << std::endl;
    stream << "<DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">" << std::endl;

    for (uint i = 0; i < mesh.cells_.size(); i++) {
        const Mesh2DRegular::Node node1(mesh.nodes_.at(mesh.cells_.at(i).node1));
        const Mesh2DRegular::Node node2(mesh.nodes_.at(mesh.cells_.at(i).node1));
        const Mesh2DRegular::Node node3(mesh.nodes_.at(mesh.cells_.at(i).node1));
        const Mesh2DRegular::Node node4(mesh.nodes_.at(mesh.cells_.at(i).node1));

        stream << node1.position(0) << " ";
        stream << node1.position(1) << " ";
        stream << node1.position(2) << " ";

        stream << node2.position(0) << " ";
        stream << node2.position(1) << " ";
        stream << node2.position(2) << " ";

        stream << node3.position(0) << " ";
        stream << node3.position(1) << " ";
        stream << node3.position(2) << " ";

        stream << node4.position(0) << " ";
        stream << node4.position(1) << " ";
        stream << node4.position(2) << " ";
    }

    stream << "</DataArray>" << std::endl;
    stream << "</Points>" << std::endl;
}

void WriteCells(std::ofstream &stream, const Mesh2DRegular &mesh) {
    uint k = 0;
    stream << "<Cells>" << std::endl;

    stream << "<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">" << std::endl;

    for (uint i = 0; i < mesh.cells_.size(); i++) {
        for (uint j = 0; j < 4; j++) {
            stream << k++ << " ";
        }
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

}  // namespace unstructured_grid
}  // namespace vtk
}  // namespace hamt
