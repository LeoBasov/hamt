#include "homogeneous.h"

namespace hamt {
namespace heat_equation_homogeneous {

void CheckSurfaceEmissivityFactor(const double& value) {
    if (value < 0.0 || value > 1.0) {
        throw Exception("Surface emissivity factor [" + std::to_string(value) + "] outside boundary.", __FUNCTION__);
    }
}

void ConvertButtomLeft(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                       const VectorXd& results) {
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
    } else if ((boundary_left.type == Mesh2DRegular::RADIATION) || (boundary_buttom.type == Mesh2DRegular::RADIATION)) {
        if (boundary_left.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_left.value);
        }
        if (boundary_buttom.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_buttom.value);
        }

        const Mesh2DRegular::Surface surface_tr(mesh.surfaces_.at(mesh.cells_.at(node.cell_tr).surface_id));
        const double surface_emissivity_factor(0.5 * (boundary_left.value + boundary_buttom.value));
        const double thermal_conductivity(surface_tr.thermal_conductivity);
        const double k(surface_emissivity_factor * constants::kStefanBoltzmann * mesh.dy_ / thermal_conductivity);

        mat_b.first(row, row) = 2.0 + 8.0 * k * std::pow(results(row), 3);
        mat_b.first(row, node.u_ip_j) = -1.0;
        mat_b.first(row, node.u_i_jp) = -1.0;

        mat_b.second(row) = 6.0 * k * std::pow(results(row), 4);
    } else {
        mat_b.first(row, node.u_ip_j) = 1.0;
        mat_b.first(row, node.u_i_jp) = 1.0;
        mat_b.first(row, row) = -2.0;

        mat_b.second(row) = boundary_left.value * mesh.dx_ + boundary_buttom.value * mesh.dy_;
    }
}

void ConvertButtomRight(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                        const VectorXd& results) {
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
    } else if ((boundary_right.type == Mesh2DRegular::RADIATION) ||
               (boundary_buttom.type == Mesh2DRegular::RADIATION)) {
        if (boundary_right.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_right.value);
        }
        if (boundary_buttom.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_buttom.value);
        }

        const Mesh2DRegular::Surface surface_tl(mesh.surfaces_.at(mesh.cells_.at(node.cell_tl).surface_id));
        const double surface_emissivity_factor(0.5 * (boundary_right.value + boundary_buttom.value));
        const double thermal_conductivity(surface_tl.thermal_conductivity);
        const double k(surface_emissivity_factor * constants::kStefanBoltzmann * mesh.dy_ / thermal_conductivity);

        mat_b.first(row, row) = 2 + 8.0 * k * std::pow(results(row), 3);
        mat_b.first(row, node.u_im_j) = -1.0;
        mat_b.first(row, node.u_i_jp) = -1.0;

        mat_b.second(row) = 6.0 * k * std::pow(results(row), 4);
    } else {
        mat_b.first(row, node.u_i_jp) = -1.0;
        mat_b.first(row, node.u_im_j) = -1.0;
        mat_b.first(row, row) = 2.0;

        mat_b.second(row) = boundary_right.value * mesh.dx_ - boundary_buttom.value * mesh.dy_;
    }
}

void ConvertTopRight(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                     const VectorXd& results) {
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
    } else if ((boundary_right.type == Mesh2DRegular::RADIATION) || (boundary_top.type == Mesh2DRegular::RADIATION)) {
        if (boundary_right.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_right.value);
        }
        if (boundary_top.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_top.value);
        }

        const Mesh2DRegular::Surface surface_bl(mesh.surfaces_.at(mesh.cells_.at(node.cell_bl).surface_id));
        const double surface_emissivity_factor(0.5 * (boundary_right.value + boundary_top.value));
        const double thermal_conductivity(surface_bl.thermal_conductivity);
        const double k(surface_emissivity_factor * constants::kStefanBoltzmann * mesh.dy_ / thermal_conductivity);

        mat_b.first(row, row) = 2.0 + 8.0 * k * std::pow(results(row), 3);
        mat_b.first(row, node.u_im_j) = -1.0;
        mat_b.first(row, node.u_i_jm) = -1.0;

        mat_b.second(row) = 6.0 * k * std::pow(results(row), 4);
    } else {
        mat_b.first(row, node.u_i_jm) = -1.0;
        mat_b.first(row, node.u_im_j) = -1.0;
        mat_b.first(row, row) = 2.0;

        mat_b.second(row) = boundary_right.value * mesh.dx_ + boundary_top.value * mesh.dy_;
    }
}

void ConvertTopLeft(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                    const VectorXd& results) {
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
    } else if ((boundary_left.type == Mesh2DRegular::RADIATION) || (boundary_top.type == Mesh2DRegular::RADIATION)) {
        if (boundary_left.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_left.value);
        }
        if (boundary_top.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_top.value);
        }

        const Mesh2DRegular::Surface surface_br(mesh.surfaces_.at(mesh.cells_.at(node.cell_br).surface_id));
        const double surface_emissivity_factor(0.5 * (boundary_left.value + boundary_top.value));
        const double thermal_conductivity(surface_br.thermal_conductivity);
        const double k(surface_emissivity_factor * constants::kStefanBoltzmann * mesh.dy_ / thermal_conductivity);

        mat_b.first(row, row) = 2.0 + 8.0 * k * std::pow(results(row), 3);
        mat_b.first(row, node.u_ip_j) = -1.0;
        mat_b.first(row, node.u_i_jm) = -1.0;

        mat_b.second(row) = 6.0 * k * std::pow(results(row), 4);
    } else {
        mat_b.first(row, node.u_ip_j) = -1.0;
        mat_b.first(row, node.u_i_jm) = -1.0;
        mat_b.first(row, row) = 2.0;

        mat_b.second(row) = -boundary_left.value * mesh.dx_ + boundary_top.value * mesh.dy_;
    }
}

void ConvertTop(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                const VectorXd& results) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell_left(mesh.cells_.at(node.cell_bl));
    const Mesh2DRegular::Cell cell_right(mesh.cells_.at(node.cell_br));
    const Mesh2DRegular::Boundary boundary_left(mesh.boundaries_.at(cell_left.bounary_top));
    const Mesh2DRegular::Boundary boundary_right(mesh.boundaries_.at(cell_right.bounary_top));

    if ((boundary_left.type == Mesh2DRegular::DIRICHLET) && (boundary_right.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_left.value + boundary_right.value);
    } else if ((boundary_left.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_left.value;
    } else if ((boundary_right.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_right.value;
    } else if ((boundary_left.type == Mesh2DRegular::RADIATION) || (boundary_right.type == Mesh2DRegular::RADIATION)) {
        if (boundary_left.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_left.value);
        }
        if (boundary_right.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_right.value);
        }

        const Mesh2DRegular::Surface surface_bl(mesh.surfaces_.at(mesh.cells_.at(node.cell_bl).surface_id));
        const Mesh2DRegular::Surface surface_br(mesh.surfaces_.at(mesh.cells_.at(node.cell_br).surface_id));
        const double surface_emissivity_factor(0.5 * (boundary_left.value + boundary_right.value));
        const double thermal_conductivity(0.5 * (surface_bl.thermal_conductivity + surface_br.thermal_conductivity));
        const double k(surface_emissivity_factor * constants::kStefanBoltzmann * mesh.dy_ / thermal_conductivity);

        mat_b.first(row, row) = 1.0 + 4.0 * k * std::pow(results(row), 3);
        mat_b.first(row, node.u_i_jm) = -1.0;

        mat_b.second(row) = 3.0 * k * std::pow(results(row), 4);
    } else {
        mat_b.first(row, node.u_i_jm) = -1.0;
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_right.value + boundary_left.value) * mesh.dy_;
    }
}

void ConvertButtom(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                   const VectorXd& results) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell_left(mesh.cells_.at(node.cell_tl));
    const Mesh2DRegular::Cell cell_right(mesh.cells_.at(node.cell_tr));
    const Mesh2DRegular::Boundary boundary_left(mesh.boundaries_.at(cell_left.bounary_buttom));
    const Mesh2DRegular::Boundary boundary_right(mesh.boundaries_.at(cell_right.bounary_buttom));

    if ((boundary_left.type == Mesh2DRegular::DIRICHLET) && (boundary_right.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_left.value + boundary_right.value);
    } else if ((boundary_left.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_left.value;
    } else if ((boundary_right.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_right.value;
    } else if ((boundary_left.type == Mesh2DRegular::RADIATION) || (boundary_right.type == Mesh2DRegular::RADIATION)) {
        if (boundary_left.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_left.value);
        }
        if (boundary_right.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_right.value);
        }

        const Mesh2DRegular::Surface surface_tl(mesh.surfaces_.at(mesh.cells_.at(node.cell_tl).surface_id));
        const Mesh2DRegular::Surface surface_tr(mesh.surfaces_.at(mesh.cells_.at(node.cell_tr).surface_id));
        const double surface_emissivity_factor(0.5 * (boundary_left.value + boundary_right.value));
        const double thermal_conductivity(0.5 * (surface_tl.thermal_conductivity + surface_tr.thermal_conductivity));
        const double k(surface_emissivity_factor * constants::kStefanBoltzmann * mesh.dy_ / thermal_conductivity);

        mat_b.first(row, node.u_i_jp) = -1.0;
        mat_b.first(row, row) = 1.0 + 4.0 * k * std::pow(results(row), 3);

        mat_b.second(row) = 3.0 * k * std::pow(results(row), 4);
    } else {
        mat_b.first(row, node.u_i_jp) = 1.0;
        mat_b.first(row, row) = -1.0;

        mat_b.second(row) = -0.5 * (boundary_right.value + boundary_left.value) * mesh.dy_;
    }
}

void ConvertRight(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                  const VectorXd& results) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell_top(mesh.cells_.at(node.cell_tl));
    const Mesh2DRegular::Cell cell_buttom(mesh.cells_.at(node.cell_bl));
    const Mesh2DRegular::Boundary boundary_top(mesh.boundaries_.at(cell_top.bounary_right));
    const Mesh2DRegular::Boundary boundary_buttom(mesh.boundaries_.at(cell_buttom.bounary_right));

    if ((boundary_top.type == Mesh2DRegular::DIRICHLET) && (boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_top.value + boundary_buttom.value);
    } else if ((boundary_top.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_top.value;
    } else if ((boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_buttom.value;
    } else if ((boundary_top.type == Mesh2DRegular::RADIATION) || (boundary_buttom.type == Mesh2DRegular::RADIATION)) {
        if (boundary_top.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_top.value);
        }
        if (boundary_buttom.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_buttom.value);
        }

        const Mesh2DRegular::Surface surface_bl(mesh.surfaces_.at(mesh.cells_.at(node.cell_bl).surface_id));
        const Mesh2DRegular::Surface surface_tl(mesh.surfaces_.at(mesh.cells_.at(node.cell_tl).surface_id));
        const double surface_emissivity_factor(0.5 * (boundary_top.value + boundary_buttom.value));
        const double thermal_conductivity(0.5 * (surface_bl.thermal_conductivity + surface_tl.thermal_conductivity));
        const double k(surface_emissivity_factor * constants::kStefanBoltzmann * mesh.dx_ / thermal_conductivity);

        mat_b.first(row, row) = 1.0 + 4.0 * k * std::pow(results(row), 3);
        mat_b.first(row, node.u_im_j) = -1.0;

        mat_b.second(row) = 3.0 * k * std::pow(results(row), 4);
    } else {
        mat_b.first(row, node.u_im_j) = -1.0;
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_buttom.value + boundary_top.value) * mesh.dx_;
    }
}

void ConvertLeft(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row,
                 const VectorXd& results) {
    const Mesh2DRegular::Node node(mesh.nodes_.at(row));
    const Mesh2DRegular::Cell cell_top(mesh.cells_.at(node.cell_tr));
    const Mesh2DRegular::Cell cell_buttom(mesh.cells_.at(node.cell_br));
    const Mesh2DRegular::Boundary boundary_top(mesh.boundaries_.at(cell_top.bounary_left));
    const Mesh2DRegular::Boundary boundary_buttom(mesh.boundaries_.at(cell_buttom.bounary_left));

    if ((boundary_top.type == Mesh2DRegular::DIRICHLET) && (boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = 0.5 * (boundary_top.value + boundary_buttom.value);
    } else if ((boundary_top.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_top.value;
    } else if ((boundary_buttom.type == Mesh2DRegular::DIRICHLET)) {
        mat_b.first(row, row) = 1.0;

        mat_b.second(row) = boundary_buttom.value;
    } else if ((boundary_top.type == Mesh2DRegular::RADIATION) || (boundary_buttom.type == Mesh2DRegular::RADIATION)) {
        if (boundary_top.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_top.value);
        }
        if (boundary_buttom.type == Mesh2DRegular::RADIATION) {
            CheckSurfaceEmissivityFactor(boundary_buttom.value);
        }

        const Mesh2DRegular::Surface surface_br(mesh.surfaces_.at(mesh.cells_.at(node.cell_br).surface_id));
        const Mesh2DRegular::Surface surface_tr(mesh.surfaces_.at(mesh.cells_.at(node.cell_tr).surface_id));
        const double surface_emissivity_factor(0.5 * (boundary_top.value + boundary_buttom.value));
        const double thermal_conductivity(0.5 * (surface_br.thermal_conductivity + surface_tr.thermal_conductivity));
        const double k(surface_emissivity_factor * constants::kStefanBoltzmann * mesh.dx_ / thermal_conductivity);

        mat_b.first(row, node.u_ip_j) = -1.0;
        mat_b.first(row, row) = 1.0 + 4.0 * k * std::pow(results(row), 3);

        mat_b.second(row) = 3.0 * k * std::pow(results(row), 4);
    } else {
        mat_b.first(row, node.u_ip_j) = 1.0;
        mat_b.first(row, row) = -1.0;

        mat_b.second(row) = -0.5 * (boundary_buttom.value + boundary_top.value) * mesh.dx_;
    }
}

std::pair<MatrixXd, VectorXd> ConvertMesh2dRegularCartesian(const Mesh2DRegular& mesh, const VectorXd& results) {
    std::pair<MatrixXd, VectorXd> mat_b;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        switch (mesh.nodes_.at(i).type) {
            case Mesh2DRegular::NodeType::BUTTOM_LEFT: {
                ConvertButtomLeft(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::BUTTOM_RIGHT: {
                ConvertButtomRight(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::TOP_RIGHT: {
                ConvertTopRight(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::TOP_LEFT: {
                ConvertTopLeft(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::BUTTOM: {
                ConvertButtom(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::RIGHT: {
                ConvertRight(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::TOP: {
                ConvertTop(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::LEFT: {
                ConvertLeft(mat_b, mesh, i, results);
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

std::pair<MatrixXd, VectorXd> ConvertMesh2dRegularCylindircal(const Mesh2DRegular& mesh, const VectorXd& results) {
    std::pair<MatrixXd, VectorXd> mat_b;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    for (uint i = 0; i < mesh.nodes_.size(); i++) {
        if (mesh.nodes_.at(i).position(0) < 0.0) {
            throw Exception("r coordinate < 0.0 for node [" + std::to_string(i) + "].", __PRETTY_FUNCTION__);
        }

        switch (mesh.nodes_.at(i).type) {
            case Mesh2DRegular::NodeType::BUTTOM_LEFT: {
                ConvertButtomLeft(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::BUTTOM_RIGHT: {
                ConvertButtomRight(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::TOP_RIGHT: {
                ConvertTopRight(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::TOP_LEFT: {
                ConvertTopLeft(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::BUTTOM: {
                ConvertButtom(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::RIGHT: {
                ConvertRight(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::TOP: {
                ConvertTop(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::LEFT: {
                ConvertLeft(mat_b, mesh, i, results);
                break;
            }
            case Mesh2DRegular::NodeType::MID: {
                ConvertMidCylindrical(mat_b, mesh, i);
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

void ConvertMidCylindrical(std::pair<MatrixXd, VectorXd>& mat_b, const Mesh2DRegular& mesh, const uint& row) {
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

    const double therm_tot_y(mean_yl + mean_yr);
    const double therm_tot_x(mean_xb + mean_xt);
    const double r_dash(mesh.dy_ / (2.0 * node.position(1)));
    const double therm_cond_min(mean_xb - mean_xt);

    mat_b.first(row, node.u_im_j) = mean_yl;
    mat_b.first(row, node.u_ip_j) = mean_yr;
    mat_b.first(row, row) = r_dash * therm_cond_min - (therm_tot_x + therm_tot_y);
    mat_b.first(row, node.u_i_jm) = (1 - r_dash) * mean_xb;
    mat_b.first(row, node.u_i_jp) = (1 + r_dash) * mean_xt;
}

std::pair<MatrixXd, VectorXd> ConvertMesh2dTriangularCartesian(const Mesh2DTriangular& mesh, const VectorXd& results) {
    std::pair<MatrixXd, VectorXd> mat_b;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    for (size_t i = 0; i < mesh.nodes_.size(); i++) {
        const Mesh2DTriangular::Node& node = mesh.nodes_.at(i);

        if (node.boundaries.size()) {
            const Mesh2DTriangular::Boundary& boundary1 = mesh.boundaries_.at(node.boundaries.at(0));
            const Mesh2DTriangular::Boundary& boundary2 = mesh.boundaries_.at(node.boundaries.at(1));

            if (boundary1.type == Mesh2DTriangular::BoundaryType::DIRICHLET &&
                boundary2.type == Mesh2DTriangular::BoundaryType::DIRICHLET) {
                mat_b.second(i) = 0.5*(boundary1.value + boundary2.value);
                mat_b.first(i, i) = 1.0;
            } else if (boundary1.type == Mesh2DTriangular::BoundaryType::DIRICHLET) {
                mat_b.second(i) = boundary1.value;
                mat_b.first(i, i) = 1.0;
            } else if (boundary2.type == Mesh2DTriangular::BoundaryType::DIRICHLET) {
                mat_b.second(i) = boundary2.value;
                mat_b.first(i, i) = 1.0;
            } else if (boundary1.type == Mesh2DTriangular::BoundaryType::NEUMANN &&
                       boundary2.type == Mesh2DTriangular::BoundaryType::NEUMANN) {
                NeumannTraingularMesh(mesh, i, mat_b);
            } else {
                throw IncompleteCodeError("undefined boundary condition for triangular mesh");
            }
        } else {
            CentreTriangularMesh(mesh, i, mat_b);
        }
    }

    return mat_b;
}

void CentreTriangularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b) {
    const Mesh2DTriangular::Node& node = mesh.nodes_.at(node_id);
    double surface(0.0);

    for (size_t c = 1; c < node.adjacent_cells.size(); c++) {
        const Vector3d barycentre_dist1 = mesh.cells_.at(node.adjacent_cells.at(c - 1)).barycentre - node.position;
        const Vector3d barycentre_dist2 = mesh.cells_.at(node.adjacent_cells.at(c)).barycentre - node.position;
        const Vector3d cross = barycentre_dist1.cross(barycentre_dist2);

        surface += 0.5 * cross.norm();
    }

    for (size_t c = 1; c < node.adjacent_cells.size(); c++) {
        const size_t adjacent_node_id = node.adjacent_nodes.at(c);
        const Mesh2DTriangular::Node& adjacent_node = mesh.nodes_.at(adjacent_node_id);
        const Vector3d barycentre1 = mesh.cells_.at(node.adjacent_cells.at(c - 1)).barycentre;
        const Vector3d barycentre2 = mesh.cells_.at(node.adjacent_cells.at(c)).barycentre;
        const double factor = CalcElementFactor(node.position, adjacent_node.position, barycentre1, barycentre2);

        mat_b.first(node_id, node_id) -= factor / surface;
        mat_b.first(node_id, adjacent_node_id) += factor / surface;
    }

    const size_t adjacent_node_id = node.adjacent_nodes.at(0);
    const Mesh2DTriangular::Node& adjacent_node = mesh.nodes_.at(adjacent_node_id);
    const Vector3d barycentre1 = mesh.cells_.at(node.adjacent_cells.at(node.adjacent_cells.size() - 1)).barycentre;
    const Vector3d barycentre2 = mesh.cells_.at(node.adjacent_cells.at(0)).barycentre;
    const double factor = CalcElementFactor(node.position, adjacent_node.position, barycentre1, barycentre2);

    mat_b.first(node_id, node_id) -= factor / surface;
    mat_b.first(node_id, adjacent_node_id) += factor / surface;
}

double CalcTriangleSurface(const Vector3d& point1, const Vector3d& point2, const Vector3d& point3) {
    const Vector3d dist1 = point2 - point1;
    const Vector3d dist2 = point3 - point1;
    const Vector3d cross = dist1.cross(dist2);

    return 0.5 * cross.norm();
}

double CalcElementFactor(const Vector3d& node_pos, const Vector3d& adj_node_pos, const Vector3d& last_barycenter,
                         const Vector3d& next_barycenter) {
    const Vector3d diff = adj_node_pos - node_pos;
    const Vector3d grad_diff = CalcGradientDiff(diff);

    return (next_barycenter - last_barycenter).norm() * grad_diff.dot(diff.normalized());
}

Vector3d CalcGradientDiff(const Vector3d& pointing_vec) {
    Vector3d diff;

    for (long i = 0; i < pointing_vec.size(); i++) {
        diff(i) = (std::abs(pointing_vec(i)) < 1e-15 ? 0.0 : 1.0 / pointing_vec(i));
    }

    return diff;
}

void NeumannTraingularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b) {
    const Mesh2DTriangular::Node& node = mesh.nodes_.at(node_id);
    const Mesh2DTriangular::Boundary& boundary1 = mesh.boundaries_.at(node.boundaries.at(0));
    const Mesh2DTriangular::Boundary& boundary2 = mesh.boundaries_.at(node.boundaries.at(1));
    std::vector<Vector3d> r_i_ip1;
    std::vector<Vector3d> r_c_ip1;
    std::vector<Vector3d> n;
    Vector3d n_q;  // normal vector of the neuman boundary condition gradient
    double surface(0.0);

    // set up vectors
    for (size_t c = 0; c < node.adjacent_nodes.size(); c++) {
        if (c == 0) {
            const Vector3d p_ip1 = mesh.nodes_.at(node.adjacent_nodes.at(c)).position;

            r_i_ip1.push_back(p_ip1 - node.position);
        } else {
            const Vector3d p_i = mesh.nodes_.at(node.adjacent_nodes.at(c - 1)).position;
            const Vector3d p_ip1 = mesh.nodes_.at(node.adjacent_nodes.at(c)).position;

            r_i_ip1.push_back(p_ip1 - p_i);
            r_c_ip1.push_back(p_i - node.position);

            if (c == node.adjacent_nodes.size() - 1) {
                const Vector3d p_c = mesh.nodes_.at(node.adjacent_nodes.at(c)).position;

                r_i_ip1.push_back(node.position - p_ip1);
                r_c_ip1.push_back(p_c - node.position);
            }
        }
    }

    // set up normal vectors
    n.resize(r_i_ip1.size());

    for (size_t i = 0; i < r_i_ip1.size(); i++) {
        n.at(i)(0) = r_i_ip1.at(i)(1);
        n.at(i)(1) = -r_i_ip1.at(i)(0);
        n.at(i)(2) = r_i_ip1.at(i)(2);

        n.at(i).normalize();
    }

    // calc n_q
    n_q = 0.5 * (n.back() + n.front());

    // calculate effective cell surface
    for (size_t i = 1; i < r_c_ip1.size(); i++) {
        surface += 0.5 * (r_c_ip1.at(i).cross(r_c_ip1.at(i - 1)).norm());
    }

    /*for (size_t c = 0; c < node.adjacent_nodes.size(); c++) {
        if (c == 0) {
            const size_t adjacent_node_id2 = node.adjacent_nodes.at(c);
            const double factor = r_i_ip1.at(c).norm() * n.at(c).dot(n_q) / (2.0 * surface);

            mat_b.first(node_id, adjacent_node_id2) += factor;
        } else {
            const size_t adjacent_node_id1 = node.adjacent_nodes.at(c - 1);
            const size_t adjacent_node_id2 = node.adjacent_nodes.at(c);
            const double factor = r_i_ip1.at(c).norm() * n.at(c).dot(n_q) / (2.0 * surface);

            mat_b.first(node_id, adjacent_node_id2) += factor;
            mat_b.first(node_id, adjacent_node_id1) -= factor;
        }
    }

    const size_t adjacent_node_id1 = node.adjacent_nodes.back();
    const double factor =
        r_i_ip1.at(node.adjacent_nodes.size()).norm() * n.at(node.adjacent_nodes.size()).dot(n_q) / (2.0 * surface);

    mat_b.first(node_id, adjacent_node_id1) -= factor;

    mat_b.second(node_id) = 0.5 * (boundary1.value + boundary2.value);*/

    for (size_t c = 0; c < node.adjacent_nodes.size(); c++) {
        const double factor = r_c_ip1.at(c).dot(n_q) / (r_c_ip1.at(c).norm() * node.adjacent_nodes.size());
        const size_t adjacent_node_id = node.adjacent_nodes.at(c);

        mat_b.first(node_id, adjacent_node_id) += factor;
        mat_b.first(node_id, node_id) -= factor;
    }

    mat_b.second(node_id) = 0.5 * (boundary1.value + boundary2.value);
}

}  // namespace heat_equation_homogeneous
}  // namespace hamt
