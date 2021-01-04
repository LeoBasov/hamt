#include "gmsh.h"

namespace hamt {
namespace gmsh {

MSH2 ReadMSH2(const std::string& file_name) {
    MSH2 mesh;
    std::ifstream infile(file_name);
    std::string line;
    bool found(false);

    if (!infile.is_open()) {
        throw Exception("File [" + file_name + "] could not be open.", __PRETTY_FUNCTION__);
    }

    infile.close();

    // ReadGmshMeshFormat(file_name);
    // ReadGmshNodes(file_name);
    // ReadGmshElements(file_name);

    return mesh;
}

void ReadGmshMeshFormat(const std::string& file_name) {
    /*std::ifstream infile(file_name);
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

            if (std::stod(results.at(0)) == 2.2) {
                file_type_ = GMSH_MSH2;
            } else {
                infile.close();
                throw Exception("UNDEFINED GMSH FILFE FORMAT [" + results.at(0) + "]", __PRETTY_FUNCTION__);
            }

            found = false;
        } else if (line == "$EndMeshFormat") {
            infile.close();
            return;
        }
    }

    infile.close();

    throw Exception("GMSH MESH FORMAT NOT FOUND IN FILE", __PRETTY_FUNCTION__);*/
}

void ReadGmshNodes(const std::string& file_name) {
    /*std::ifstream infile(file_name);
    std::string line;
    bool found(false);

    if (!infile.is_open()) {
        throw std::exception();
    }

    while (std::getline(infile, line)) {
        if (line == "$Nodes") {
            found = true;
        } else if (found && (line == "$EndNodes")) {
            return;
        } else if (found) {
            std::istringstream iss(line);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                             std::istream_iterator<std::string>());
            GmshMeshMSH2::Node node;

            if (results.size() == 1) {
                continue;
            }

            node.node_number = std::stoi(results.at(0));
            node.coord = Vector3d(std::stod(results.at(1)), std::stod(results.at(2)), std::stod(results.at(3)));

            if (!mesh_msh2_.nodes_.insert({node.node_number, node}).second) {
                throw Exception("REDEFINED NODE NUMBER [" + std::to_string(node.node_number) + "]",
                                __PRETTY_FUNCTION__);
            }
        }
    }

    throw Exception("GMSH NODES NOT FOUND IN FILE", __PRETTY_FUNCTION__);*/
}

void ReadGmshElements(const std::string& file_name) {
    /*std::ifstream infile(file_name);
    std::string line;
    bool found(false);

    if (!infile.is_open()) {
        throw std::exception();
    }

    while (std::getline(infile, line)) {
        if (line == "$Elements") {
            found = true;
        } else if (found && (line == "$EndElements")) {
            return;
        } else if (found) {
            std::istringstream iss(line);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                             std::istream_iterator<std::string>());
            GmshMeshMSH2::Element element;

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

            mesh_msh2_.elements_.push_back(element);
        }
    }

    throw Exception("GMSH ELEMENTS NOT FOUND IN FILE", __PRETTY_FUNCTION__);*/
}

}  // namespace gmsh
}  // namespace hamt
