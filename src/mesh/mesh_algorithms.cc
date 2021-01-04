#include "mesh_algorithms.h"

namespace hamt {
namespace mesh2d_regular_algorithms {

Mesh2DRegular MSH2ToMesh2DRegular(const gmsh::MSH2& msh2_mesh) {
    Mesh2DRegular mesh;

    mesh.nodes_.resize(msh2_mesh.nodes_.size());

    // set boundaries
    // set physical surfaces

    for (const auto& element : msh2_mesh.elements_) {
        if (element.elm_type == 3) {
            Mesh2DRegular::Cell cell;

            mesh.nodes_.at(element.node_number_list.at(0) - 1).cell_tr = mesh.cells_.size();
            mesh.nodes_.at(element.node_number_list.at(1) - 1).cell_tl = mesh.cells_.size();
            mesh.nodes_.at(element.node_number_list.at(2) - 1).cell_bl = mesh.cells_.size();
            mesh.nodes_.at(element.node_number_list.at(3) - 1).cell_br = mesh.cells_.size();

            cell.node1 = element.node_number_list.at(0) - 1;
            cell.node2 = element.node_number_list.at(1) - 1;
            cell.node3 = element.node_number_list.at(2) - 1;
            cell.node4 = element.node_number_list.at(3) - 1;

            mesh.cells_.push_back(cell);
        }
    }

    return mesh;
}

}  // namespace mesh2d_regular_algorithms
}  // namespace hamt
