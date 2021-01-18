#include "homogeneous.h"

namespace hamt {
namespace heat_equation_homogeneous {

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

void ConvertTop(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell_left(mesh.cells_.at(node.cell_bl));
    const Mesh2DRegular::Cell cell_right(mesh.cells_.at(node.cell_br));
    const Mesh2DRegular::Boundary boundary_left(mesh.boundaries_.at(cell_left.bounary_top));
    const Mesh2DRegular::Boundary boundary_right(mesh.boundaries_.at(cell_right.bounary_top));
    const Mesh2DRegular::Surface surface_left(mesh.surfaces_.at(cell_left.surface_id));
    const Mesh2DRegular::Surface surface_right(mesh.surfaces_.at(cell_right.surface_id));

    if ((boundary_left.type == Mesh2DRegular::DIRICHLET) && (boundary_right.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_left.value + boundary_right.value);
    } else if ((boundary_left.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_left.value;
    } else if ((boundary_right.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_right.value;
    } else {
        const double therm_cond_tot(surface_right.thermal_conductivity + surface_left.thermal_conductivity);

        mat_b.first(row, node.u_ip_j) = surface_right.thermal_conductivity;
        mat_b.first(row, node.u_im_j) = surface_left.thermal_conductivity;
        mat_b.first(row, node.u_i_jm) = -therm_cond_tot;

        mat_b.second(row) = therm_cond_tot * 0.5 * (boundary_right.value + boundary_left.value) * mesh.dy_;
    }
}

void ConvertButtom(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell_left(mesh.cells_.at(node.cell_tl));
    const Mesh2DRegular::Cell cell_right(mesh.cells_.at(node.cell_tr));
    const Mesh2DRegular::Boundary boundary_left(mesh.boundaries_.at(cell_left.bounary_buttom));
    const Mesh2DRegular::Boundary boundary_right(mesh.boundaries_.at(cell_right.bounary_buttom));
    const Mesh2DRegular::Surface surface_left(mesh.surfaces_.at(cell_left.surface_id));
    const Mesh2DRegular::Surface surface_right(mesh.surfaces_.at(cell_right.surface_id));

    if ((boundary_left.type == Mesh2DRegular::DIRICHLET) && (boundary_right.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_left.value + boundary_right.value);
    } else if ((boundary_left.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_left.value;
    } else if ((boundary_right.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_right.value;
    } else {
        const double therm_cond_tot(surface_right.thermal_conductivity + surface_left.thermal_conductivity);

        mat_b.first(row, node.u_ip_j) = surface_right.thermal_conductivity;
        mat_b.first(row, node.u_im_j) = surface_left.thermal_conductivity;
        mat_b.first(row, node.u_i_jp) = -therm_cond_tot;

        mat_b.second(row) = -therm_cond_tot * 0.5 * (boundary_right.value + boundary_left.value) * mesh.dy_;
    }
}

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
                ConvertButtom(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::RIGHT: {
                ConvertRightCartesian(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::TOP: {
                ConvertTop(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::LEFT: {
                ConvertLeftCartesian(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::MID: {
                ConvertMidCartesian(mat_b, mesh, i);
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

void ConvertRightCartesian(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell_top(mesh.cells_.at(node.cell_tl));
    const Mesh2DRegular::Cell cell_buttom(mesh.cells_.at(node.cell_bl));
    const Mesh2DRegular::Boundary boundary_top(mesh.boundaries_.at(cell_top.bounary_right));
    const Mesh2DRegular::Boundary boundary_buttom(mesh.boundaries_.at(cell_buttom.bounary_right));
    const Mesh2DRegular::Surface surface_top(mesh.surfaces_.at(cell_top.surface_id));
    const Mesh2DRegular::Surface surface_buttom(mesh.surfaces_.at(cell_buttom.surface_id));

    if ((boundary_top.type == Mesh2DRegular::DIRICHLET) && (boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_top.value + boundary_buttom.value);
    } else if ((boundary_top.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_top.value;
    } else if ((boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_buttom.value;
    } else {
        const double therm_cond_tot(surface_buttom.thermal_conductivity + surface_top.thermal_conductivity);

        mat_b.first(row, node.u_i_jp) = surface_top.thermal_conductivity;
        mat_b.first(row, node.u_i_jm) = surface_buttom.thermal_conductivity;
        mat_b.first(row, node.u_im_j) = -therm_cond_tot;

        mat_b.second(row) = therm_cond_tot * 0.5 * (boundary_buttom.value + boundary_top.value) * mesh.dx_;
    }
}

void ConvertLeftCartesian(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell_top(mesh.cells_.at(node.cell_tr));
    const Mesh2DRegular::Cell cell_buttom(mesh.cells_.at(node.cell_br));
    const Mesh2DRegular::Boundary boundary_top(mesh.boundaries_.at(cell_top.bounary_left));
    const Mesh2DRegular::Boundary boundary_buttom(mesh.boundaries_.at(cell_buttom.bounary_left));
    const Mesh2DRegular::Surface surface_top(mesh.surfaces_.at(cell_top.surface_id));
    const Mesh2DRegular::Surface surface_buttom(mesh.surfaces_.at(cell_buttom.surface_id));

    if ((boundary_top.type == Mesh2DRegular::DIRICHLET) && (boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_top.value + boundary_buttom.value);
    } else if ((boundary_top.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_top.value;
    } else if ((boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_buttom.value;
    } else {
        const double therm_cond_tot(surface_buttom.thermal_conductivity + surface_top.thermal_conductivity);

        mat_b.first(row, node.u_i_jp) = surface_top.thermal_conductivity;
        mat_b.first(row, node.u_i_jm) = surface_buttom.thermal_conductivity;
        mat_b.first(row, node.u_ip_j) = -therm_cond_tot;

        mat_b.second(row) = -therm_cond_tot * 0.5 * (boundary_buttom.value + boundary_top.value) * mesh.dx_;
    }
}

void ConvertMidCartesian(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    double mean_xb;
    double mean_xt;
    double mean_yl;
    double mean_yr;

    if (node.cell_bl == -1) {
        const Mesh2DRegular::Surface surface_br(mesh.surfaces_.at(mesh.cells_.at(node.cell_br).surface_id));
        const Mesh2DRegular::Surface surface_tr(mesh.surfaces_.at(mesh.cells_.at(node.cell_tr).surface_id));
        const Mesh2DRegular::Surface surface_tl(mesh.surfaces_.at(mesh.cells_.at(node.cell_tl).surface_id));

        mean_xb = 0.5 * (surface_br.thermal_conductivity + surface_br.thermal_conductivity);
        mean_xt = 0.5 * (surface_tl.thermal_conductivity + surface_tr.thermal_conductivity);
        mean_yl = 0.5 * (surface_br.thermal_conductivity + surface_tl.thermal_conductivity);
        mean_yr = 0.5 * (surface_br.thermal_conductivity + surface_tr.thermal_conductivity);
    } else if (node.cell_br == -1) {
        const Mesh2DRegular::Surface surface_bl(mesh.surfaces_.at(mesh.cells_.at(node.cell_bl).surface_id));
        const Mesh2DRegular::Surface surface_tr(mesh.surfaces_.at(mesh.cells_.at(node.cell_tr).surface_id));
        const Mesh2DRegular::Surface surface_tl(mesh.surfaces_.at(mesh.cells_.at(node.cell_tl).surface_id));

        mean_xb = 0.5 * (surface_bl.thermal_conductivity + surface_bl.thermal_conductivity);
        mean_xt = 0.5 * (surface_tl.thermal_conductivity + surface_tr.thermal_conductivity);
        mean_yl = 0.5 * (surface_bl.thermal_conductivity + surface_tl.thermal_conductivity);
        mean_yr = 0.5 * (surface_bl.thermal_conductivity + surface_tr.thermal_conductivity);
    } else if (node.cell_tr == -1) {
        const Mesh2DRegular::Surface surface_bl(mesh.surfaces_.at(mesh.cells_.at(node.cell_bl).surface_id));
        const Mesh2DRegular::Surface surface_br(mesh.surfaces_.at(mesh.cells_.at(node.cell_br).surface_id));
        const Mesh2DRegular::Surface surface_tl(mesh.surfaces_.at(mesh.cells_.at(node.cell_tl).surface_id));

        mean_xb = 0.5 * (surface_bl.thermal_conductivity + surface_br.thermal_conductivity);
        mean_xt = 0.5 * (surface_tl.thermal_conductivity + surface_tl.thermal_conductivity);
        mean_yl = 0.5 * (surface_bl.thermal_conductivity + surface_tl.thermal_conductivity);
        mean_yr = 0.5 * (surface_br.thermal_conductivity + surface_tl.thermal_conductivity);
    } else if (node.cell_tl == -1) {
        const Mesh2DRegular::Surface surface_bl(mesh.surfaces_.at(mesh.cells_.at(node.cell_bl).surface_id));
        const Mesh2DRegular::Surface surface_br(mesh.surfaces_.at(mesh.cells_.at(node.cell_br).surface_id));
        const Mesh2DRegular::Surface surface_tr(mesh.surfaces_.at(mesh.cells_.at(node.cell_tr).surface_id));

        mean_xb = 0.5 * (surface_bl.thermal_conductivity + surface_br.thermal_conductivity);
        mean_xt = 0.5 * (surface_tr.thermal_conductivity + surface_tr.thermal_conductivity);
        mean_yl = 0.5 * (surface_bl.thermal_conductivity + surface_tr.thermal_conductivity);
        mean_yr = 0.5 * (surface_br.thermal_conductivity + surface_tr.thermal_conductivity);
    } else {
        const Mesh2DRegular::Surface surface_bl(mesh.surfaces_.at(mesh.cells_.at(node.cell_bl).surface_id));
        const Mesh2DRegular::Surface surface_br(mesh.surfaces_.at(mesh.cells_.at(node.cell_br).surface_id));
        const Mesh2DRegular::Surface surface_tr(mesh.surfaces_.at(mesh.cells_.at(node.cell_tr).surface_id));
        const Mesh2DRegular::Surface surface_tl(mesh.surfaces_.at(mesh.cells_.at(node.cell_tl).surface_id));

        mean_xb = 0.5 * (surface_bl.thermal_conductivity + surface_br.thermal_conductivity);
        mean_xt = 0.5 * (surface_tl.thermal_conductivity + surface_tr.thermal_conductivity);
        mean_yl = 0.5 * (surface_bl.thermal_conductivity + surface_tl.thermal_conductivity);
        mean_yr = 0.5 * (surface_br.thermal_conductivity + surface_tr.thermal_conductivity);
    }

    const double therm_tot_x(mean_yl + mean_yr);
    const double therm_tot_y(mean_xb + mean_xt);

    mat_b.first(row, node.u_im_j) = mean_yl;
    mat_b.first(row, node.u_ip_j) = mean_yr;
    mat_b.first(row, row) = -(therm_tot_x + therm_tot_y);
    mat_b.first(row, node.u_i_jm) = mean_xb;
    mat_b.first(row, node.u_i_jp) = mean_xt;
}

std::pair<MatrixXd, VectorXd> ConvertMesh2dRegularCylindircal(const Mesh2DRegular& mesh) {
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
                ConvertButtom(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::RIGHT: {
                ConvertRightCylindrical(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::TOP: {
                ConvertTop(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::LEFT: {
                ConvertLeftCylindrical(mat_b, mesh, i);
                break;
            }
            case Mesh2DRegular::NodeType::MID: {
                ConvertMidCartesian(mat_b, mesh, i);
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

void ConvertRightCylindrical(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell_top(mesh.cells_.at(node.cell_tl));
    const Mesh2DRegular::Cell cell_buttom(mesh.cells_.at(node.cell_bl));
    const Mesh2DRegular::Boundary boundary_top(mesh.boundaries_.at(cell_top.bounary_right));
    const Mesh2DRegular::Boundary boundary_buttom(mesh.boundaries_.at(cell_buttom.bounary_right));
    const Mesh2DRegular::Surface surface_top(mesh.surfaces_.at(cell_top.surface_id));
    const Mesh2DRegular::Surface surface_buttom(mesh.surfaces_.at(cell_buttom.surface_id));

    if ((boundary_top.type == Mesh2DRegular::DIRICHLET) && (boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_top.value + boundary_buttom.value);
    } else if ((boundary_top.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_top.value;
    } else if ((boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_buttom.value;
    } else {
        const double r_dash(mesh.dy_ / (2.0 * node.position(1)));
        const double therm_cond_min(surface_top.thermal_conductivity - surface_buttom.thermal_conductivity);
        const double therm_cond_tot(surface_buttom.thermal_conductivity + surface_top.thermal_conductivity);
        const double term(r_dash * therm_cond_min - therm_cond_tot);

        mat_b.first(row, node.u_i_jp) = (1.0 + r_dash) * surface_top.thermal_conductivity;
        mat_b.first(row, node.u_i_jm) = (1.0 - r_dash) * surface_buttom.thermal_conductivity;
        mat_b.first(row, node.u_im_j) = term;

        mat_b.second(row) = -term * 0.5 * (boundary_buttom.value + boundary_top.value) * mesh.dx_;
    }
}

void ConvertLeftCylindrical(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell_top(mesh.cells_.at(node.cell_tr));
    const Mesh2DRegular::Cell cell_buttom(mesh.cells_.at(node.cell_br));
    const Mesh2DRegular::Boundary boundary_top(mesh.boundaries_.at(cell_top.bounary_left));
    const Mesh2DRegular::Boundary boundary_buttom(mesh.boundaries_.at(cell_buttom.bounary_left));
    const Mesh2DRegular::Surface surface_top(mesh.surfaces_.at(cell_top.surface_id));
    const Mesh2DRegular::Surface surface_buttom(mesh.surfaces_.at(cell_buttom.surface_id));

    if ((boundary_top.type == Mesh2DRegular::DIRICHLET) && (boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_top.value + boundary_buttom.value);
    } else if ((boundary_top.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_top.value;
    } else if ((boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_buttom.value;
    } else {
        const double r_dash(mesh.dy_ / (2.0 * node.position(1)));
        const double therm_cond_min(surface_top.thermal_conductivity - surface_buttom.thermal_conductivity);
        const double therm_cond_tot(surface_buttom.thermal_conductivity + surface_top.thermal_conductivity);
        const double term(r_dash * therm_cond_min - therm_cond_tot);

        mat_b.first(row, node.u_i_jp) = (1.0 + r_dash) * surface_top.thermal_conductivity;
        mat_b.first(row, node.u_i_jm) = (1.0 - r_dash) * surface_buttom.thermal_conductivity;
        mat_b.first(row, node.u_ip_j) = term;

        mat_b.second(row) = term * 0.5 * (boundary_buttom.value + boundary_top.value) * mesh.dx_;
    }
}

}  // namespace heat_equation_homogeneous
}  // namespace hamt
