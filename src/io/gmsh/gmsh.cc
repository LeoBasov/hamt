#include "gmsh.h"

namespace hamt {
namespace gmsh {

MSH2 ReadMSH2(const std::string& file_name) {
    MSH2 mesh;

    CheckFileFormatMSH2(file_name);
    ReadNodesMSH2(file_name, mesh);
    ReadElementsMSH2(file_name, mesh);
    ReadPhysicalNamesMSH2(file_name, mesh);

    return mesh;
}

void CheckFileFormatMSH2(const std::string& file_name) {
    std::ifstream infile(file_name);
    std::string line;
    bool found(false);

    if (!infile.is_open()) {
        throw Exception("File [" + file_name + "] could not be open.", __PRETTY_FUNCTION__);
    }

    while (std::getline(infile, line)) {
        if (line == "$MeshFormat") {
            found = true;
        } else if (found) {
            std::istringstream iss(line);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                             std::istream_iterator<std::string>());

            if (std::stod(results.at(0)) != 2.2) {
                infile.close();
                throw Exception("Undefined Gmsh file format [" + results.at(0) + "]", __PRETTY_FUNCTION__);
            }

            found = false;
        } else if (line == "$EndMeshFormat") {
            infile.close();
            return;
        }
    }

    infile.close();

    throw Exception("GMSH MESH FORMAT NOT FOUND IN FILE", __PRETTY_FUNCTION__);
}

void ReadPhysicalNamesMSH2(const std::string& file_name, MSH2& mesh) {}

void ReadNodesMSH2(const std::string& file_name, MSH2& mesh) {
    std::ifstream infile(file_name);
    std::string line;
    bool found(false);

    if (!infile.is_open()) {
        throw std::exception();
    }

    while (std::getline(infile, line)) {
        if (line == "$Nodes") {
            found = true;
        } else if (found && (line == "$EndNodes")) {
            infile.close();

            return;
        } else if (found) {
            std::istringstream iss(line);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                             std::istream_iterator<std::string>());
            MSH2::Node node;

            if (results.size() == 1) {
                continue;
            }

            node.node_number = std::stoi(results.at(0));
            node.coord = Vector3d(std::stod(results.at(1)), std::stod(results.at(2)), std::stod(results.at(3)));

            if (!mesh.nodes_.insert({node.node_number, node}).second) {
                infile.close();
                throw Exception("REDEFINED NODE NUMBER [" + std::to_string(node.node_number) + "]",
                                __PRETTY_FUNCTION__);
            }
        }
    }

    infile.close();
    throw Exception("GMSH NODES NOT FOUND IN FILE", __PRETTY_FUNCTION__);
}

void ReadElementsMSH2(const std::string& file_name, MSH2& mesh) {
    std::ifstream infile(file_name);
    std::string line;
    bool found(false);

    if (!infile.is_open()) {
        throw std::exception();
    }

    while (std::getline(infile, line)) {
        if (line == "$Elements") {
            found = true;
        } else if (found && (line == "$EndElements")) {
            infile.close();
            return;
        } else if (found) {
            std::istringstream iss(line);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                             std::istream_iterator<std::string>());
            MSH2::Element element;

            if (results.size() == 1) {
                continue;
            }

            element.elm_number = std::stoi(results.at(0));
            element.elm_type = std::stoi(results.at(1));

            for (int i = 3; i < 3 + std::stoi(results.at(2)); i++) {
                element.tags.push_back(std::stoi(results.at(i)));
            }

            for (int i = (3 + std::stoi(results.at(2))); i < static_cast<int>(results.size()); i++) {
                element.node_number_list.push_back(std::stoi(results.at(i)));
            }

            mesh.elements_.push_back(element);
        }
    }

    infile.close();
    throw Exception("GMSH ELEMENTS NOT FOUND IN FILE", __PRETTY_FUNCTION__);
}

}  // namespace gmsh
}  // namespace hamt
