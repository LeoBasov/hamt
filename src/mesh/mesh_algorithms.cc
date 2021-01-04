#include "mesh_algorithms.h"

namespace hamt {
namespace mesh2d_regular_algorithms {

Mesh2DRegular MSH2ToMesh2DRegular(const gmsh::MSH2& msh2_mesh) {
    Mesh2DRegular mesh;

    mesh.nodes_.resize(msh2_mesh.nodes_.size());

    for (const auto& name : msh2_mesh.physical_names_) {
        if (name.second.physical_dimension == 1) {
            Mesh2DRegular::Boundary boundary;

            mesh.boundary_tags_.insert({name.second.physical_tag, mesh.boundaries_.size()});
            mesh.boundary_names_.insert({name.second.physical_name, mesh.boundaries_.size()});

            mesh.boundaries_.push_back(boundary);
        } else if (name.second.physical_dimension == 2) {
            Mesh2DRegular::Surface boundary;

            mesh.surface_tags_.insert({name.second.physical_tag, mesh.boundaries_.size()});
            mesh.surface_names_.insert({name.second.physical_name, mesh.boundaries_.size()});

            mesh.surfaces_.push_back(boundary);
        }
    }

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

            // here one should be able to set correct surfaces

            mesh.cells_.push_back(cell);
        }
    }

    // asign cell and surfaces to correct types
    // assigned correct surfaces and boundary conditions

    return mesh;
}

}  // namespace mesh2d_regular_algorithms
}  // namespace hamt
