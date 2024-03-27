#include "gmsh.h"

namespace hamt {
namespace gmsh {

double GetFileFormat(const std::string& file_name) {
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

            infile.close();
            return std::stod(results.at(0));
        }
    }

    infile.close();

    throw Exception("GMSH MESH FORMAT NOT FOUND IN FILE", __PRETTY_FUNCTION__);
}

MSH2 ReadMSH2(const std::string& file_name) {
    MSH2 mesh;

    CheckFileFormatMSH2(file_name);
    ReadNodesMSH2(file_name, mesh);
    ReadElementsMSH2(file_name, mesh);
    ReadPhysicalNamesMSH2(file_name, mesh);
    CheckMeshMSH2(mesh);

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

void ReadPhysicalNamesMSH2(const std::string& file_name, MSH2& mesh) {
    std::ifstream infile(file_name);
    std::string line;
    bool found(false);

    if (!infile.is_open()) {
        throw std::exception();
    }

    while (std::getline(infile, line)) {
        if (line == "$PhysicalNames") {
            found = true;
        } else if (found && (line == "$EndPhysicalNames")) {
            infile.close();

            return;
        } else if (found) {
            std::istringstream iss(line);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                             std::istream_iterator<std::string>());
            MSH2::PhysicalName name;

            if (results.size() == 1) {
                continue;
            }

            name.physical_dimension = std::stoi(results.at(0));
            name.physical_tag = std::stoi(results.at(1));
            name.physical_name = results.at(2).substr(1, results.at(2).size() - 2);

            mesh.physical_names_.push_back(name);
        }
    }

    infile.close();
    throw Exception("GMSH PHYSICAL NAMES NOT FOUND IN FILE", __PRETTY_FUNCTION__);
}

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

void CheckMeshMSH2(MSH2& mesh) {
    const Vector3d ref_normal_vec(0.0, 0.0, 1.0);
    Vector3d normal_vec;
    bool first(true);

    for (auto& element : mesh.elements_) {
        if (element.elm_type == 2) {
            const Vector3d node1(mesh.nodes_.at(element.node_number_list.at(0)).coord);
            const Vector3d node2(mesh.nodes_.at(element.node_number_list.at(1)).coord);
            const Vector3d node3(mesh.nodes_.at(element.node_number_list.at(2)).coord);

            normal_vec = (node2 - node1).cross(node3 - node1).normalized();

            if (ref_normal_vec != normal_vec) {
                const int node = element.node_number_list.at(1);
                element.node_number_list.at(1) = element.node_number_list.at(2);
                element.node_number_list.at(2) = node;
            }
        }
    }
}

}  // namespace gmsh
}  // namespace hamt
