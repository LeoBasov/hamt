#include "heat_equation.h"

namespace hamt {
namespace heat_equation {
namespace homogeneous {

std::pair<MatrixXd, VectorXd> ConvertMesh2dRegularCartesian(const Mesh2DRegular& mesh) {
    std::pair<MatrixXd, VectorXd> mat_b;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        switch (mesh.nodes_.at(i).type) {
            case Mesh2DRegular::NodeType::BUTTOM_LEFT: {
                ConvertButtomLeft(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::BUTTOM_RIGHT: {
                ConvertButtomRight(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::TOP_RIGHT: {
                ConvertTopRight(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::TOP_LEFT: {
                ConvertTopLeft(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::BUTTOM: {
                break;
            }
            case Mesh2DRegular::NodeType::RIGHT: {
                break;
            }
            case Mesh2DRegular::NodeType::TOP: {
                break;
            }
            case Mesh2DRegular::NodeType::LEFT: {
                break;
            }
            case Mesh2DRegular::NodeType::MID: {
                break;
            }
            default: {
                throw Exception("Unhandeled case [" + std::to_string(mesh.nodes_.at(i).type) + "]",
                                __PRETTY_FUNCTION__);
            }
        }
    }

    return mat_b;
}

void ConvertButtomLeft(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell(mesh.cells_.at(node.cell_tr));
    const Mesh2DRegular::Boundary boundary_left(mesh.boundaries_.at(cell.bounary_left));
    const Mesh2DRegular::Boundary boundary_buttom(mesh.boundaries_.at(cell.bounary_buttom));

    if ((boundary_left.type == Mesh2DRegular::DIRICHLET) && (boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_left.value + boundary_buttom.value);
    } else if ((boundary_left.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_left.value;
    } else if ((boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_buttom.value;
    } else {
        mat_b.first(row, node.u_ip_j) = 1.0;
        mat_b.first(row, node.u_i_jp) = -1.0;

        mat_b.second(row) = boundary_left.value * mesh.dx_ - boundary_buttom.value * mesh.dy_;
    }
}

void ConvertButtomRight(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell(mesh.cells_.at(node.cell_tl));
    const Mesh2DRegular::Boundary boundary_right(mesh.boundaries_.at(cell.bounary_right));
    const Mesh2DRegular::Boundary boundary_buttom(mesh.boundaries_.at(cell.bounary_buttom));

    if ((boundary_right.type == Mesh2DRegular::DIRICHLET) && (boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_right.value + boundary_buttom.value);
    } else if ((boundary_right.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_right.value;
    } else if ((boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_buttom.value;
    } else {
        mat_b.first(row, node.u_i_jp) = 1.0;
        mat_b.first(row, node.u_im_j) = -1.0;

        mat_b.second(row) = boundary_right.value * mesh.dx_ + boundary_buttom.value * mesh.dy_;
    }
}

void ConvertTopRight(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell(mesh.cells_.at(node.cell_bl));
    const Mesh2DRegular::Boundary boundary_right(mesh.boundaries_.at(cell.bounary_right));
    const Mesh2DRegular::Boundary boundary_top(mesh.boundaries_.at(cell.bounary_top));

    if ((boundary_right.type == Mesh2DRegular::DIRICHLET) && (boundary_top.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_right.value + boundary_top.value);
    } else if ((boundary_right.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_right.value;
    } else if ((boundary_top.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_top.value;
    } else {
        mat_b.first(row, node.u_i_jm) = 1.0;
        mat_b.first(row, node.u_im_j) = -1.0;

        mat_b.second(row) = boundary_right.value * mesh.dx_ - boundary_top.value * mesh.dy_;
    }
}

void ConvertTopLeft(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell(mesh.cells_.at(node.cell_br));
    const Mesh2DRegular::Boundary boundary_left(mesh.boundaries_.at(cell.bounary_left));
    const Mesh2DRegular::Boundary boundary_top(mesh.boundaries_.at(cell.bounary_top));

    if ((boundary_left.type == Mesh2DRegular::DIRICHLET) && (boundary_top.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_left.value + boundary_top.value);
    } else if ((boundary_left.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_left.value;
    } else if ((boundary_top.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_top.value;
    } else {
        mat_b.first(row, node.u_ip_j) = 1.0;
        mat_b.first(row, node.u_i_jm) = -1.0;

        mat_b.second(row) = boundary_left.value * mesh.dx_ + boundary_top.value * mesh.dy_;
    }
}

}  // namespace homogeneous
}  // namespace heat_equation
}  // namespace hamt
