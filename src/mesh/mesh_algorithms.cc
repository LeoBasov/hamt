#include "mesh_algorithms.h"

namespace hamt {
namespace mesh_algorithms {

Mesh2DRegular MSH2ToMesh2DRegular(const gmsh::MSH2& msh2_mesh) {
    Mesh2DRegular mesh;

    SetUpNodesAndCells(mesh, msh2_mesh);
    SetUpPhysicalGroups(mesh, msh2_mesh);

    return mesh;
}

void SetUpNodesAndCells(Mesh2DRegular& mesh, const gmsh::MSH2& msh2_mesh) {
    mesh.nodes_.resize(msh2_mesh.nodes_.size());

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

    for (auto& node : mesh.nodes_) {
        if (node.cell_bl >= 0) {
            node.u_im_j = mesh.cells_.at(node.cell_bl).node4;
            node.u_i_jm = mesh.cells_.at(node.cell_bl).node2;
        }
        if (node.cell_br >= 0) {
            node.u_i_jm = mesh.cells_.at(node.cell_br).node1;
            node.u_ip_j = mesh.cells_.at(node.cell_br).node3;
        }
        if (node.cell_tr >= 0) {
            node.u_ip_j = mesh.cells_.at(node.cell_tr).node2;
            node.u_i_jp = mesh.cells_.at(node.cell_tr).node4;
        }
        if (node.cell_tl >= 0) {
            node.u_i_jp = mesh.cells_.at(node.cell_tl).node3;
            node.u_im_j = mesh.cells_.at(node.cell_tl).node1;
        }

        if ((node.cell_bl < 0) && (node.cell_br < 0) && (node.cell_tr >= 0) && (node.cell_tl >= 0)) {
            node.type = Mesh2DRegular::BUTTOM;
        } else if ((node.cell_bl >= 0) && (node.cell_br >= 0) && (node.cell_tr < 0) && (node.cell_tl < 0)) {
            node.type = Mesh2DRegular::TOP;
        } else if ((node.cell_bl < 0) && (node.cell_br >= 0) && (node.cell_tr >= 0) && (node.cell_tl < 0)) {
            node.type = Mesh2DRegular::LEFT;
        } else if ((node.cell_bl >= 0) && (node.cell_br < 0) && (node.cell_tr < 0) && (node.cell_tl >= 0)) {
            node.type = Mesh2DRegular::RIGHT;
        } else if ((node.cell_bl >= 0) && (node.cell_br < 0) && (node.cell_tr < 0) && (node.cell_tl < 0)) {
            node.type = Mesh2DRegular::TOP_RIGHT;
        } else if ((node.cell_bl < 0) && (node.cell_br >= 0) && (node.cell_tr < 0) && (node.cell_tl < 0)) {
            node.type = Mesh2DRegular::TOP_LEFT;
        } else if ((node.cell_bl < 0) && (node.cell_br < 0) && (node.cell_tr < 0) && (node.cell_tl >= 0)) {
            node.type = Mesh2DRegular::BUTTOM_RIGHT;
        } else if ((node.cell_bl < 0) && (node.cell_br < 0) && (node.cell_tr >= 0) && (node.cell_tl < 0)) {
            node.type = Mesh2DRegular::BUTTOM_LEFT;
        } else {
            node.type = Mesh2DRegular::MID;
        }
    }
}

void SetUpPhysicalGroups(Mesh2DRegular& mesh, const gmsh::MSH2& msh2_mesh) {
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

    for (uint i = 0, k = 0; i < msh2_mesh.elements_.size(); i++) {
        const gmsh::MSH2::Element& element(msh2_mesh.elements_.at(i));

        if (element.elm_type == 3) {
            // mesh.cells_.at(k++).surface_id = mesh.surface_tags_.at(element.tags.at(1));
        } else if (element.elm_type == 1) {
            for (auto& cell : mesh.cells_) {
                if (cell.IsButtom(element.node_number_list.at(0) - 1, element.node_number_list.at(1) - 1)) {
                    cell.bounary_buttom = mesh.boundary_tags_.at(element.tags.at(1));
                } else if (cell.IsRight(element.node_number_list.at(0) - 1, element.node_number_list.at(1) - 1)) {
                    cell.bounary_right = mesh.boundary_tags_.at(element.tags.at(1));
                } else if (cell.IsTop(element.node_number_list.at(0) - 1, element.node_number_list.at(1) - 1)) {
                    cell.bounary_top = mesh.boundary_tags_.at(element.tags.at(1));
                } else if (cell.IsLeft(element.node_number_list.at(0) - 1, element.node_number_list.at(1) - 1)) {
                    cell.bounary_left = mesh.boundary_tags_.at(element.tags.at(1));
                }
            }
        }
    }
}

}  // namespace mesh2d_regular_algorithms
}  // namespace hamt
