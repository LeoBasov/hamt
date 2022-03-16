#include "mesh_algorithms.h"

namespace hamt {
namespace mesh_algorithms {

Mesh2DRegular MSH2ToMesh2DRegular(const gmsh::MSH2& msh2_mesh) {
    Mesh2DRegular mesh;

    SetUpCellSize(mesh, msh2_mesh);
    SetUpNodesAndCells(mesh, msh2_mesh);
    SetUpPhysicalGroups(mesh, msh2_mesh);

    return mesh;
}

void SetUpNodesAndCells(Mesh2DRegular& mesh, const gmsh::MSH2& msh2_mesh) {
    mesh.nodes_.resize(msh2_mesh.nodes_.size());

    for (uint i = 1; i <= msh2_mesh.nodes_.size(); i++) {
        mesh.nodes_.at(i - 1).position = msh2_mesh.nodes_.at(i).coord;
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

            mesh.cells_.push_back(cell);
        }
    }


    for(uint i = 0; i< mesh.nodes_.size() ; i++){
        for(uint j = i + 1; j < mesh.nodes_.size() ; j++){
            if ((std::abs(mesh.nodes_.at(i).position(0) - mesh.nodes_.at(j).position(0)) < 0.5 * mesh.dx_) &&
                (std::abs(mesh.nodes_.at(i).position(1) - mesh.nodes_.at(j).position(1)) < 0.5 * mesh.dy_)) {
                if (mesh.nodes_.at(i).cell_bl >= 0) {
                    mesh.nodes_.at(j).cell_bl = mesh.nodes_.at(i).cell_bl;
                }
                if (mesh.nodes_.at(i).cell_br >= 0) {
                    mesh.nodes_.at(j).cell_br = mesh.nodes_.at(i).cell_br;
                }
                if (mesh.nodes_.at(i).cell_tr >= 0) {
                    mesh.nodes_.at(j).cell_tr = mesh.nodes_.at(i).cell_tr;
                }
                if (mesh.nodes_.at(i).cell_tl >= 0) {
                    mesh.nodes_.at(j).cell_tl = mesh.nodes_.at(i).cell_tl;
                }

                if (mesh.nodes_.at(j).cell_bl >= 0) {
                    mesh.nodes_.at(i).cell_bl = mesh.nodes_.at(j).cell_bl;
                }
                if (mesh.nodes_.at(j).cell_br >= 0) {
                    mesh.nodes_.at(i).cell_br = mesh.nodes_.at(j).cell_br;
                }
                if (mesh.nodes_.at(j).cell_tr >= 0) {
                    mesh.nodes_.at(i).cell_tr = mesh.nodes_.at(j).cell_tr;
                }
                if (mesh.nodes_.at(j).cell_tl >= 0) {
                    mesh.nodes_.at(i).cell_tl = mesh.nodes_.at(j).cell_tl;
                }
            }
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
            mesh.cells_.at(k++).surface_id = mesh.surface_tags_.at(element.tags.at(0));
        } else if (element.elm_type == 1) {
            for (auto& cell : mesh.cells_) {
                if (cell.IsButtom(element.node_number_list.at(0) - 1, element.node_number_list.at(1) - 1)) {
                    cell.bounary_buttom = mesh.boundary_tags_.at(element.tags.at(0));
                } else if (cell.IsRight(element.node_number_list.at(0) - 1, element.node_number_list.at(1) - 1)) {
                    cell.bounary_right = mesh.boundary_tags_.at(element.tags.at(0));
                } else if (cell.IsTop(element.node_number_list.at(0) - 1, element.node_number_list.at(1) - 1)) {
                    cell.bounary_top = mesh.boundary_tags_.at(element.tags.at(0));
                } else if (cell.IsLeft(element.node_number_list.at(0) - 1, element.node_number_list.at(1) - 1)) {
                    cell.bounary_left = mesh.boundary_tags_.at(element.tags.at(0));
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

Mesh2DTriangular MSH2ToMesh2DTriangular(const gmsh::MSH2& msh2_mesh) {
    Mesh2DTriangular mesh;

    SetUpBoundaries(mesh, msh2_mesh);
    SetUpCellsAndNodes(mesh, msh2_mesh);
    ConnectMesh(mesh);

    return mesh;
}

void SetUpBoundaries(Mesh2DTriangular& mesh, const gmsh::MSH2& msh2_mesh) {
    for (const auto& name : msh2_mesh.physical_names_) {
        if (name.physical_dimension == 1) {
            Mesh2DTriangular::Boundary boundary;

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
            Mesh2DTriangular::Surface surface;

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
}

void SetUpCellsAndNodes(Mesh2DTriangular& mesh, const gmsh::MSH2& msh2_mesh) {
    std::map<int, size_t> node_number_map;

    for (const auto& node : msh2_mesh.nodes_) {
        Mesh2DTriangular::Node node_new;

        node_number_map[node.second.node_number] = mesh.nodes_.size();
        node_new.position = node.second.coord;
        mesh.nodes_.push_back(node_new);
    }

    for (uint i = 0; i < msh2_mesh.elements_.size(); i++) {
        const gmsh::MSH2::Element& element(msh2_mesh.elements_.at(i));

        if (element.elm_type == 2) {
            Mesh2DTriangular::Cell cell;

            cell.surface_id = mesh.surface_tags_.at(element.tags.at(0));

            for (size_t n = 0; n < 3; n++) {
                cell.nodes.at(n) = node_number_map.at(element.node_number_list.at(n));
                cell.barycentre += mesh.nodes_.at(cell.nodes.at(n)).position;
            }

            cell.barycentre /= 3.0;

            mesh.cells_.push_back(cell);
        }
    }

    for (uint i = 0; i < msh2_mesh.elements_.size(); i++) {
        const gmsh::MSH2::Element& element(msh2_mesh.elements_.at(i));

        if (element.elm_type == 1) {
            for (size_t c = 0; c < mesh.cells_.size(); c++) {
                Mesh2DTriangular::Cell& cell = mesh.cells_.at(c);
                const int node1(node_number_map.at(element.node_number_list.at(0)));
                const int node2(node_number_map.at(element.node_number_list.at(1)));
                const auto& iter1 = std::find(cell.nodes.begin(), cell.nodes.end(), node1);
                const auto& iter2 = std::find(cell.nodes.begin(), cell.nodes.end(), node2);

                if (iter1 != cell.nodes.end() && iter2 != cell.nodes.end()) {
                    const int pos1 = std::min(iter1 - cell.nodes.begin(), iter2 - cell.nodes.begin());
                    const int pos2 = std::max(iter1 - cell.nodes.begin(), iter2 - cell.nodes.begin());

                    if (pos1 == 0 && pos2 == 1) {
                        cell.boundaries.at(0) = mesh.boundary_tags_.at(element.elm_number);
                    } else if (pos1 == 1 && pos2 == 2) {
                        cell.boundaries.at(1) = mesh.boundary_tags_.at(element.elm_number);
                    } else if (pos1 == 0 && pos2 == 2) {
                        cell.boundaries.at(2) = mesh.boundary_tags_.at(element.elm_number);
                    } else {
                        throw Exception("unacceptrable combination of cell indices", __PRETTY_FUNCTION__);
                    }
                }
            }
        }
    }
}

void ConnectMesh(Mesh2DTriangular& mesh) {
    for (size_t i = 0; i < mesh.cells_.size(); i++) {
        const Mesh2DTriangular::Cell& cell = mesh.cells_.at(i);

        for (auto& node_id : cell.nodes) {
            mesh.nodes_.at(node_id).adjacent_cells.push_back(i);
        }
    }

    for (size_t n = 0; n < mesh.nodes_.size(); n++) {
        Mesh2DTriangular::Node& node = mesh.nodes_.at(n);
        std::vector<size_t> adjacent_cells = {FindStartingCell(n, mesh)};

        while (adjacent_cells.size() < node.adjacent_cells.size()) {
            adjacent_cells.push_back(FindNextCell(n, adjacent_cells.back(), mesh));
        }

        node.adjacent_cells = adjacent_cells;
    }

    // TODO (LB): created list of sorted andjacent nodes
}

size_t FindStartingCell(const size_t& node_id, const Mesh2DTriangular& mesh) {
    const std::vector<Mesh2DTriangular::Cell>& cells = mesh.cells_;

    for (const auto& next_cell_id : mesh.nodes_.at(node_id).adjacent_cells) {
        const size_t pos = cells.at(next_cell_id).GetNodePos(node_id);

        if (cells.at(next_cell_id).boundaries.at(pos) != -1) {
            return next_cell_id;
        }
    }

    return mesh.nodes_.at(node_id).adjacent_cells.front();
}

size_t FindNextCell(const size_t& node_id, const size_t& cell_id, const Mesh2DTriangular& mesh) {
    const std::vector<Mesh2DTriangular::Cell>& cells = mesh.cells_;
    const size_t pos = cells.at(cell_id).GetNodePos(node_id);
    const size_t node_id2 = cells.at(cell_id).nodes.at(pos == 0 ? 2 : pos - 1);

    for (const auto& next_cell_id : mesh.nodes_.at(node_id).adjacent_cells) {
        if (cells.at(next_cell_id).IsInCell(node_id2)) {
            const size_t pos1 = cells.at(next_cell_id).GetNodePos(node_id);
            const size_t pos2 = cells.at(next_cell_id).GetNodePos(node_id2);

            if (pos2 == (pos1 == 2 ? 0 : pos1 + 1)) {
                return next_cell_id;
            }
        }
    }

    throw Exception("next cell not found", __PRETTY_FUNCTION__);
}

}  // namespace mesh2d_regular_algorithms
}  // namespace hamt
