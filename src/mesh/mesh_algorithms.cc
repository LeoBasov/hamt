#include "mesh_algorithms.h"

namespace hamt {
namespace mesh_algorithms {

Mesh2DRegular MSH2ToMesh2DRegular(const gmsh::MSH2& msh2_mesh) {
    Mesh2DRegular mesh;

    SetUpNodesAndCells(mesh, msh2_mesh);
    SetUpPhysicalGroups(mesh, msh2_mesh);
    SetUpCellSize(mesh, msh2_mesh);

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
        if (name.physical_dimension == 1) {
            Mesh2DRegular::Boundary boundary;

            auto ret_pair1 = mesh.boundary_tags_.insert({name.physical_tag, mesh.boundaries_.size()});
            auto ret_pair2 = mesh.boundary_names_.insert({name.physical_name, mesh.boundaries_.size()});

            if (!ret_pair1.second) {
                throw Exception("Could not insert boundary tag [" + std::to_string(name.physical_tag) + "]",
                                __PRETTY_FUNCTION__);
            } else if (!ret_pair2.second) {
                throw Exception("Could not insert boundary name [" + name.physical_name + "]", __PRETTY_FUNCTION__);
            }

            mesh.boundaries_.push_back(boundary);
        } else if (name.physical_dimension == 2) {
            Mesh2DRegular::Surface surface;

            auto ret_pair1 = mesh.surface_tags_.insert({name.physical_tag, mesh.surfaces_.size()});
            auto ret_pair2 = mesh.surface_names_.insert({name.physical_name, mesh.surfaces_.size()});

            if (!ret_pair1.second) {
                throw Exception("Could not insert surface tag [" + std::to_string(name.physical_tag) + "]",
                                __PRETTY_FUNCTION__);
            } else if (!ret_pair2.second) {
                throw Exception("Could not insert surface name [" + name.physical_name + "]", __PRETTY_FUNCTION__);
            }

            mesh.surfaces_.push_back(surface);
        }
    }

    for (uint i = 0, k = 0; i < msh2_mesh.elements_.size(); i++) {
        const gmsh::MSH2::Element& element(msh2_mesh.elements_.at(i));

        if (element.elm_type == 3) {
            // The setting of surface tags doesn't seem to wrok

            mesh.cells_.at(k++).surface_id = mesh.surface_tags_.at(element.tags.at(1));
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

void SetUpCellSize(Mesh2DRegular& mesh, const gmsh::MSH2& msh2_mesh) {
    for (uint i = 0; i < msh2_mesh.elements_.size(); i++) {
        const gmsh::MSH2::Element& element(msh2_mesh.elements_.at(i));

        if (element.elm_type == 3) {
            const gmsh::MSH2::Node node1(msh2_mesh.nodes_.at(element.node_number_list.at(0)));
            const gmsh::MSH2::Node node2(msh2_mesh.nodes_.at(element.node_number_list.at(1)));
            const gmsh::MSH2::Node node3(msh2_mesh.nodes_.at(element.node_number_list.at(2)));

            mesh.dx_ = std::abs(node1.coord(0) - node2.coord(0));
            mesh.dy_ = std::abs(node2.coord(1) - node3.coord(1));

            break;
        }
    }
}

}  // namespace mesh2d_regular_algorithms
}  // namespace hamt
