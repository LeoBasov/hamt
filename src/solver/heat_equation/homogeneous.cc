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

std::pair<MatrixXd, VectorXd> ConvertMesh2dTriangular(const Mesh2DTriangular& mesh, const VectorXd& results,
                                                      bool cartesian, bool true_radiation) {
    std::pair<MatrixXd, VectorXd> mat_b;

    mat_b.first = MatrixXd::Zero(mesh.nodes_.size(), mesh.nodes_.size());
    mat_b.second = VectorXd::Zero(mesh.nodes_.size());

    for (size_t i = 0; i < mesh.nodes_.size(); i++) {
        const Mesh2DTriangular::Node& node = mesh.nodes_.at(i);

        if (node.boundaries.size()) {
            ConvertBoundariesTriangularMesh(mesh, results, i, mat_b, true_radiation);
        } else if (cartesian) {
            FEMCentreTriangularMesh(mesh, i, mat_b);
        } else {
            FEMCentreCylindricalMesh(mesh, i, mat_b);
        }
    }

    return mat_b;
}

void CentreTriangularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b) {
    const Mesh2DTriangular::Node& node = mesh.nodes_.at(node_id);
    double total_cell_area = 0.0;
    Matrix3d rot_mat = Matrix3d::Zero();

    rot_mat(0, 1) = 1.0;
    rot_mat(1, 0) = -1.0;
    rot_mat(2, 2) = 1.0;

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        total_cell_area += mesh.GetCellArea(node.adjacent_cells.at(c));
    }

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        const size_t pos_i = c;
        const size_t pos_ip = c == node.adjacent_cells.size() - 1 ? 0 : c + 1;
        const size_t cell_id_i = node.adjacent_cells.at(pos_i);
        const size_t cell_id_ip = node.adjacent_cells.at(pos_ip);
        const Mesh2DTriangular::Cell& cell_i = mesh.cells_.at(cell_id_i);
        const Mesh2DTriangular::Cell& cell_ip = mesh.cells_.at(cell_id_ip);
        const double surface = mesh.GetCellArea(cell_id_i) + mesh.GetCellArea(cell_id_ip);
        const Vector3d bary_vec = rot_mat * (mesh.GetBarycentre(node_id, pos_ip) - mesh.GetBarycentre(node_id, pos_i));
        const Mesh2DTriangular::Surface& surface_i = mesh.surfaces_.at(cell_i.surface_id);
        const Mesh2DTriangular::Surface& surface_ip = mesh.surfaces_.at(cell_ip.surface_id);
        const double factor_i = surface_i.thermal_conductivity * (1.0 / (2.0 * surface * total_cell_area));
        const double factor_ip = surface_ip.thermal_conductivity * (1.0 / (2.0 * surface * total_cell_area));

        for (size_t i = 0; i < 3; i++) {
            const size_t pos_im = i == 0 ? 2 : i - 1;
            const size_t pos_ip = i == 2 ? 0 : i + 1;
            const size_t node_id_b_im = cell_i.nodes.at(pos_im);
            const size_t node_id_b_ip = cell_i.nodes.at(pos_ip);
            const size_t node_id_bp_im = cell_ip.nodes.at(pos_im);
            const size_t node_id_bp_ip = cell_ip.nodes.at(pos_ip);
            const size_t node_id_b_i = cell_i.nodes.at(i);
            const size_t node_id_bp_i = cell_ip.nodes.at(i);
            const Vector3d node_pos_b_im = mesh.GetNodePos(node_id_b_im);
            const Vector3d node_pos_b_ip = mesh.GetNodePos(node_id_b_ip);
            const Vector3d node_pos_bp_im = mesh.GetNodePos(node_id_bp_im);
            const Vector3d node_pos_bp_ip = mesh.GetNodePos(node_id_bp_ip);

            mat_b.first(node_id, node_id_b_i) += factor_i * (rot_mat * (node_pos_b_ip - node_pos_b_im)).dot(bary_vec);
            mat_b.first(node_id, node_id_bp_i) +=
                factor_ip * (rot_mat * (node_pos_bp_ip - node_pos_bp_im)).dot(bary_vec);
        }
    }
}

void FEMCentreTriangularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b) {
    const Mesh2DTriangular::Node& node = mesh.nodes_.at(node_id);

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        const size_t cell_id = node.adjacent_cells.at(c);
        const Mesh2DTriangular::Cell& cell = mesh.cells_.at(cell_id);
        int pos_im = -1, pos_ip = -1;

        for (size_t i = 0; i < 3; i++) {
            if (cell.nodes.at(i) == node_id) {
                pos_im = i == 0 ? 2 : i - 1;
                pos_ip = i == 2 ? 0 : i + 1;
                break;
            }
        }

        const size_t node_id_im = cell.nodes.at(pos_im);
        const size_t node_id_ip = cell.nodes.at(pos_ip);
        const Vector3d node_pos_i = mesh.GetNodePos(node_id);
        const Vector3d node_pos_im = mesh.GetNodePos(node_id_im);
        const Vector3d node_pos_ip = mesh.GetNodePos(node_id_ip);

        const double dx10 = node_pos_ip(0) - node_pos_i(0);
        const double dx20 = node_pos_im(0) - node_pos_i(0);
        const double dy10 = node_pos_ip(1) - node_pos_i(1);
        const double dy20 = node_pos_im(1) - node_pos_i(1);

        const double det_J = dx10 * dy20 - dx20 * dy10;

        const double phi_ii_x = 0.5 * std::pow(-dy20 + dy10, 2) / det_J;
        const double phi_ii_y = 0.5 * std::pow(dx20 - dx10, 2) / det_J;

        const double phi_ip_x = 0.5 * (-dy20 + dy10) * dy20 / det_J;
        const double phi_ip_y = -0.5 * (dx20 - dx10) * dx20 / det_J;

        const double phi_im_x = -0.5 * (-dy20 + dy10) * dy10 / det_J;
        const double phi_im_y = 0.5 * (dx20 - dx10) * dx10 / det_J;

        const Mesh2DTriangular::Surface surface_br(mesh.surfaces_.at(mesh.cells_.at(cell_id).surface_id));

        mat_b.first(node_id, node_id) += (phi_ii_x + phi_ii_y) * surface_br.thermal_conductivity;
        mat_b.first(node_id, node_id_im) += (phi_im_x + phi_im_y) * surface_br.thermal_conductivity;
        mat_b.first(node_id, node_id_ip) += (phi_ip_x + phi_ip_y) * surface_br.thermal_conductivity;

        mat_b.second(node_id) += (1.0 / 6.0) * surface_br.volumetric_heat_source * det_J;
    }
}

void NeumannTriangularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b) {
    const Mesh2DTriangular::Node& node = mesh.nodes_.at(node_id);
    const Mesh2DTriangular::Boundary& boundary1 = mesh.boundaries_.at(node.boundaries.at(0));
    const Mesh2DTriangular::Boundary& boundary2 = mesh.boundaries_.at(node.boundaries.at(1));
    const Vector3d node_pos_left = mesh.GetNodePos(node_id, 0);
    const Vector3d node_pos_right = mesh.GetNodePos(node_id, node.adjacent_nodes.size() - 1);
    Matrix3d rot_mat = Matrix3d::Zero();
    double total_cell_area = 0.0;

    rot_mat(0, 1) = 1.0;
    rot_mat(1, 0) = -1.0;
    rot_mat(2, 2) = 1.0;

    Vector3d normal =
        (0.5 * rot_mat * (node_pos_left - node.position) + 0.5 * rot_mat * (node.position - node_pos_right))
            .normalized();

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        const size_t cell_id = node.adjacent_cells.at(c);
        total_cell_area += mesh.GetCellArea(cell_id);
    }

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        const size_t cell_id = node.adjacent_cells.at(c);
        const Mesh2DTriangular::Cell& cell = mesh.cells_.at(cell_id);
        const double factor = (1.0 / (2.0 * total_cell_area));

        for (size_t i = 0; i < 3; i++) {
            const size_t pos_im = i == 0 ? 2 : i - 1;
            const size_t pos_ip = i == 2 ? 0 : i + 1;
            const size_t node_id_im = cell.nodes.at(pos_im);
            const size_t node_id_ip = cell.nodes.at(pos_ip);
            const size_t node_id_i = cell.nodes.at(i);
            const Vector3d node_pos_im = mesh.GetNodePos(node_id_im);
            const Vector3d node_pos_ip = mesh.GetNodePos(node_id_ip);

            mat_b.first(node_id, node_id_i) += factor * (rot_mat * (node_pos_ip - node_pos_im)).dot(normal);
        }
    }

    // TODO (LB): implement correct area dependant average
    mat_b.second(node_id) = (boundary1.value + boundary2.value) / 2.0;
}

void HeatFluxTriangularMesh(const Mesh2DTriangular& mesh, const size_t node_id, std::pair<MatrixXd, VectorXd>& mat_b) {
    const Mesh2DTriangular::Node& node = mesh.nodes_.at(node_id);
    const Mesh2DTriangular::Boundary& boundary1 = mesh.boundaries_.at(node.boundaries.at(0));
    const Mesh2DTriangular::Boundary& boundary2 = mesh.boundaries_.at(node.boundaries.at(1));
    const Vector3d node_pos_left = mesh.GetNodePos(node_id, 0);
    const Vector3d node_pos_right = mesh.GetNodePos(node_id, node.adjacent_nodes.size() - 1);
    const double L_left = (node_pos_left - node.position).norm();
    const double L_right = (node.position - node_pos_right).norm();
    const double L = L_left + L_right;
    Vector3d nomal, nomal_left, nomal_right;
    Matrix3d rot_mat = Matrix3d::Zero();
    double total_cell_area = 0.0;

    rot_mat(0, 1) = 1.0;
    rot_mat(1, 0) = -1.0;
    rot_mat(2, 2) = 1.0;

    nomal_left = (rot_mat * (node_pos_left - node.position)).normalized();
    nomal_right = (rot_mat * (node.position - node_pos_right)).normalized();
    nomal = ((L_left * nomal_left + L_right * nomal_right) / L).normalized();

    mat_b.second(node_id) = ((L_left * boundary1.value + L_right * boundary2.value) / L);

    if (boundary1.type == Mesh2DTriangular::BoundaryType::HEAT_FLUX &&
        boundary2.type == Mesh2DTriangular::BoundaryType::HEAT_FLUX) {
        nomal_left = (rot_mat * (node_pos_left - node.position)).normalized();
        nomal_right = (rot_mat * (node.position - node_pos_right)).normalized();
        nomal = ((L_left * nomal_left + L_right * nomal_right) / L).normalized();
        mat_b.second(node_id) = ((L_left * boundary1.value + L_right * boundary2.value) / L);
    } else if (boundary1.type == Mesh2DTriangular::BoundaryType::HEAT_FLUX) {
        nomal = (rot_mat * (node_pos_left - node.position)).normalized();
        mat_b.second(node_id) = boundary1.value;
    } else {
        nomal = (rot_mat * (node.position - node_pos_right)).normalized();
        mat_b.second(node_id) = boundary2.value;
    }

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        const size_t cell_id = node.adjacent_cells.at(c);
        total_cell_area += mesh.GetCellArea(cell_id);
    }

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        const size_t cell_id = node.adjacent_cells.at(c);
        const Mesh2DTriangular::Cell& cell = mesh.cells_.at(cell_id);
        const int pos_i = cell.GetNodePos(node_id);
        const int pos_im = pos_i == 0 ? 2 : pos_i - 1;
        const int pos_ip = pos_i == 2 ? 0 : pos_i + 1;
        const size_t node_id_im = cell.nodes.at(pos_im);
        const size_t node_id_ip = cell.nodes.at(pos_ip);
        const Mesh2DTriangular::Surface& surface = mesh.surfaces_.at(cell.surface_id);
        const double frac = mesh.GetCellArea(cell_id) / total_cell_area;
        const Vector3d coeffs =
            -frac * surface.thermal_conductivity * CalcNormalDerevativeCoefficients(mesh, nomal, cell_id, node_id);

        mat_b.first(node_id, node_id) += coeffs(0);

        mat_b.first(node_id, node_id_ip) += coeffs(1);
        mat_b.first(node_id, node_id_im) += coeffs(2);
    }
}

void RadiationTrueTriangularMesh(const Mesh2DTriangular& mesh, const VectorXd& results, const size_t node_id,
                                 std::pair<MatrixXd, VectorXd>& mat_b) {
    const Mesh2DTriangular::Node& node = mesh.nodes_.at(node_id);
    const Mesh2DTriangular::Boundary& boundary1 = mesh.boundaries_.at(node.boundaries.at(0));
    const Mesh2DTriangular::Boundary& boundary2 = mesh.boundaries_.at(node.boundaries.at(1));
    const Vector3d node_pos_left = mesh.GetNodePos(node_id, 0);
    const Vector3d node_pos_right = mesh.GetNodePos(node_id, node.adjacent_nodes.size() - 1);
    const double L_left = (node_pos_left - node.position).norm();
    const double L_right = (node.position - node_pos_right).norm();
    const double L = L_left + L_right;
    Vector3d nomal, nomal_left, nomal_right;
    Matrix3d rot_mat = Matrix3d::Zero();
    double total_cell_area = 0.0, epsilon;

    rot_mat(0, 1) = 1.0;
    rot_mat(1, 0) = -1.0;
    rot_mat(2, 2) = 1.0;

    if (boundary1.type == Mesh2DTriangular::BoundaryType::RADIATION &&
        boundary2.type == Mesh2DTriangular::BoundaryType::RADIATION) {
        epsilon = (L_left * boundary1.value + L_right * boundary2.value) / L;
        nomal_left = (rot_mat * (node_pos_left - node.position)).normalized();
        nomal_right = (rot_mat * (node.position - node_pos_right)).normalized();
        nomal = ((L_left * nomal_left + L_right * nomal_right) / L).normalized();
    } else if (boundary1.type == Mesh2DTriangular::BoundaryType::RADIATION) {
        nomal = (rot_mat * (node_pos_left - node.position)).normalized();
        epsilon = boundary1.value;
    } else {
        nomal = (rot_mat * (node.position - node_pos_right)).normalized();
        epsilon = boundary2.value;
    }

    mat_b.second(node_id) += epsilon * constants::kStefanBoltzmann * std::pow(results(node_id), 4);

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        const size_t cell_id = node.adjacent_cells.at(c);
        total_cell_area += mesh.GetCellArea(cell_id);
    }

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        const size_t cell_id = node.adjacent_cells.at(c);
        const Mesh2DTriangular::Cell& cell = mesh.cells_.at(cell_id);
        const int pos_i = cell.GetNodePos(node_id);
        const int pos_im = pos_i == 0 ? 2 : pos_i - 1;
        const int pos_ip = pos_i == 2 ? 0 : pos_i + 1;
        const size_t node_id_im = cell.nodes.at(pos_im);
        const size_t node_id_ip = cell.nodes.at(pos_ip);
        const Mesh2DTriangular::Surface& surface = mesh.surfaces_.at(cell.surface_id);
        const double frac = mesh.GetCellArea(cell_id) / total_cell_area;
        const Vector3d coeffs =
            -frac * surface.thermal_conductivity * CalcNormalDerevativeCoefficients(mesh, nomal, cell_id, node_id);

        mat_b.first(node_id, node_id) += coeffs(0);

        mat_b.first(node_id, node_id_ip) += coeffs(1);
        mat_b.first(node_id, node_id_im) += coeffs(2);
    }
}

void RadiationTriangularMesh(const Mesh2DTriangular& mesh, const VectorXd& results, const size_t node_id,
                             std::pair<MatrixXd, VectorXd>& mat_b) {
    const Mesh2DTriangular::Node& node = mesh.nodes_.at(node_id);
    const Mesh2DTriangular::Boundary& boundary1 = mesh.boundaries_.at(node.boundaries.at(0));
    const Mesh2DTriangular::Boundary& boundary2 = mesh.boundaries_.at(node.boundaries.at(1));
    const Vector3d node_pos_left = mesh.GetNodePos(node_id, 0);
    const Vector3d node_pos_right = mesh.GetNodePos(node_id, node.adjacent_nodes.size() - 1);
    const double L_left = (node_pos_left - node.position).norm();
    const double L_right = (node.position - node_pos_right).norm();
    const double L = L_left + L_right;
    Vector3d nomal, nomal_left, nomal_right;
    Matrix3d rot_mat = Matrix3d::Zero();
    double total_cell_area = 0.0, epsilon, a;

    rot_mat(0, 1) = 1.0;
    rot_mat(1, 0) = -1.0;
    rot_mat(2, 2) = 1.0;

    if (boundary1.type == Mesh2DTriangular::BoundaryType::RADIATION &&
        boundary2.type == Mesh2DTriangular::BoundaryType::RADIATION) {
        epsilon = (L_left * boundary1.value + L_right * boundary2.value) / L;
        nomal_left = (rot_mat * (node_pos_left - node.position)).normalized();
        nomal_right = (rot_mat * (node.position - node_pos_right)).normalized();
        nomal = ((L_left * nomal_left + L_right * nomal_right) / L).normalized();
    } else if (boundary1.type == Mesh2DTriangular::BoundaryType::RADIATION) {
        nomal = (rot_mat * (node_pos_left - node.position)).normalized();
        epsilon = boundary1.value;
    } else {
        nomal = (rot_mat * (node.position - node_pos_right)).normalized();
        epsilon = boundary2.value;
    }

    a = 4.0 * epsilon * constants::kStefanBoltzmann * std::pow(results(node_id), 3);

    mat_b.first(node_id, node_id) -= a;
    mat_b.second(node_id) = -3.0 * epsilon * constants::kStefanBoltzmann * std::pow(results(node_id), 4);

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        const size_t cell_id = node.adjacent_cells.at(c);
        total_cell_area += mesh.GetCellArea(cell_id);
    }

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        const size_t cell_id = node.adjacent_cells.at(c);
        const Mesh2DTriangular::Cell& cell = mesh.cells_.at(cell_id);
        const int pos_i = cell.GetNodePos(node_id);
        const int pos_im = pos_i == 0 ? 2 : pos_i - 1;
        const int pos_ip = pos_i == 2 ? 0 : pos_i + 1;
        const size_t node_id_im = cell.nodes.at(pos_im);
        const size_t node_id_ip = cell.nodes.at(pos_ip);
        const Mesh2DTriangular::Surface& surface = mesh.surfaces_.at(cell.surface_id);
        const double frac = mesh.GetCellArea(cell_id) / total_cell_area;
        const Vector3d coeffs =
            -frac * surface.thermal_conductivity * CalcNormalDerevativeCoefficients(mesh, nomal, cell_id, node_id);

        mat_b.first(node_id, node_id) += coeffs(0);

        mat_b.first(node_id, node_id_ip) += coeffs(1);
        mat_b.first(node_id, node_id_im) += coeffs(2);
    }
}

Vector3d CalcNormalDerevativeCoefficients(const Mesh2DTriangular& mesh, const Vector3d& normal_vec,
                                          const size_t cell_id, const size_t node_id) {
    const Mesh2DTriangular::Cell& cell = mesh.cells_.at(cell_id);
    const size_t pos_i = cell.GetNodePos(node_id);
    const size_t pos_im = pos_i == 0 ? 2 : pos_i - 1;
    const size_t pos_ip = pos_i == 2 ? 0 : pos_i + 1;
    const size_t node_id_im = cell.nodes.at(pos_im);
    const size_t node_id_ip = cell.nodes.at(pos_ip);
    const Vector3d node_pos_i = mesh.GetNodePos(node_id);
    const Vector3d node_pos_im = mesh.GetNodePos(node_id_im);
    const Vector3d node_pos_ip = mesh.GetNodePos(node_id_ip);
    const double dx10 = node_pos_ip(0) - node_pos_i(0);
    const double dx20 = node_pos_im(0) - node_pos_i(0);
    const double dy10 = node_pos_ip(1) - node_pos_i(1);
    const double dy20 = node_pos_im(1) - node_pos_i(1);
    const double det_J = dx10 * dy20 - dx20 * dy10;
    Vector3d coeffs = Vector3d::Zero();

    coeffs(0) = (normal_vec(0) * (dy10 - dy20) + normal_vec(1) * (dx20 - dx10)) / det_J;
    coeffs(1) = (normal_vec(0) * dy20 - normal_vec(1) * dx20) / det_J;
    coeffs(2) = (-normal_vec(0) * dy10 + normal_vec(1) * dx10) / det_J;

    return coeffs;
}

void FEMCentreCylindricalMesh(const Mesh2DTriangular& mesh, const size_t node_id,
                              std::pair<MatrixXd, VectorXd>& mat_b) {
    const Mesh2DTriangular::Node& node = mesh.nodes_.at(node_id);

    for (size_t c = 0; c < node.adjacent_cells.size(); c++) {
        const size_t cell_id = node.adjacent_cells.at(c);
        const Mesh2DTriangular::Cell& cell = mesh.cells_.at(cell_id);
        int pos_im = -1, pos_ip = -1;

        for (size_t i = 0; i < 3; i++) {
            if (cell.nodes.at(i) == node_id) {
                pos_im = i == 0 ? 2 : i - 1;
                pos_ip = i == 2 ? 0 : i + 1;
                break;
            }
        }

        const size_t node_id_im = cell.nodes.at(pos_im);
        const size_t node_id_ip = cell.nodes.at(pos_ip);
        const Vector3d node_pos_i = mesh.GetNodePos(node_id);
        const Vector3d node_pos_im = mesh.GetNodePos(node_id_im);
        const Vector3d node_pos_ip = mesh.GetNodePos(node_id_ip);

        const double dx10 = node_pos_ip(0) - node_pos_i(0);
        const double dx20 = node_pos_im(0) - node_pos_i(0);
        const double dy10 = node_pos_ip(1) - node_pos_i(1);
        const double dy20 = node_pos_im(1) - node_pos_i(1);

        const double det_J = dx10 * dy20 - dx20 * dy10;

        const double phi_ii_x = 0.5 * std::pow(-dy20 + dy10, 2) / det_J;
        const double phi_ii_y = 0.5 * std::pow(dx20 - dx10, 2) / det_J;

        const double phi_ip_x = 0.5 * (-dy20 + dy10) * dy20 / det_J;
        const double phi_ip_y = -0.5 * (dx20 - dx10) * dx20 / det_J;

        const double phi_im_x = -0.5 * (-dy20 + dy10) * dy10 / det_J;
        const double phi_im_y = 0.5 * (dx20 - dx10) * dx10 / det_J;

        const double int_r = (dy10 / 3.0) + (dy20 / 3.0) + node_pos_i(1);
        const double int_rb = (dy10 / 24.0) + (dy20 / 24.0) + (node_pos_i(1) / 6.0);

        const Mesh2DTriangular::Surface surface_br(mesh.surfaces_.at(mesh.cells_.at(cell_id).surface_id));

        mat_b.first(node_id, node_id) += int_r * (phi_ii_x + phi_ii_y) * surface_br.thermal_conductivity;
        mat_b.first(node_id, node_id_im) += int_r * (phi_im_x + phi_im_y) * surface_br.thermal_conductivity;
        mat_b.first(node_id, node_id_ip) += int_r * (phi_ip_x + phi_ip_y) * surface_br.thermal_conductivity;

        mat_b.second(node_id) += int_rb * surface_br.volumetric_heat_source * det_J;
    }
}

void ConvertBoundariesTriangularMesh(const Mesh2DTriangular& mesh, const VectorXd& results, const size_t node_id,
                                     std::pair<MatrixXd, VectorXd>& mat_b, const bool true_radiation) {
    const Mesh2DTriangular::Node& node = mesh.nodes_.at(node_id);
    const Mesh2DTriangular::Boundary& boundary1 = mesh.boundaries_.at(node.boundaries.at(0));
    const Mesh2DTriangular::Boundary& boundary2 = mesh.boundaries_.at(node.boundaries.at(1));

    if (boundary1.type == Mesh2DTriangular::BoundaryType::DIRICHLET &&
        boundary2.type == Mesh2DTriangular::BoundaryType::DIRICHLET) {
        mat_b.second(node_id) = 0.5 * (boundary1.value + boundary2.value);
        mat_b.first(node_id, node_id) = 1.0;
    } else if (boundary1.type == Mesh2DTriangular::BoundaryType::DIRICHLET) {
        mat_b.second(node_id) = boundary1.value;
        mat_b.first(node_id, node_id) = 1.0;
    } else if (boundary2.type == Mesh2DTriangular::BoundaryType::DIRICHLET) {
        mat_b.second(node_id) = boundary2.value;
        mat_b.first(node_id, node_id) = 1.0;
    } else if (true_radiation && (boundary1.type == Mesh2DTriangular::BoundaryType::RADIATION ||
                                  boundary2.type == Mesh2DTriangular::BoundaryType::RADIATION)) {
        RadiationTrueTriangularMesh(mesh, results, node_id, mat_b);
    } else if (boundary1.type == Mesh2DTriangular::BoundaryType::RADIATION ||
               boundary2.type == Mesh2DTriangular::BoundaryType::RADIATION) {
        RadiationTriangularMesh(mesh, results, node_id, mat_b);
    } else if (boundary1.type == Mesh2DTriangular::BoundaryType::HEAT_FLUX ||
               boundary2.type == Mesh2DTriangular::BoundaryType::HEAT_FLUX) {
        HeatFluxTriangularMesh(mesh, node_id, mat_b);
    } else if (boundary1.type == Mesh2DTriangular::BoundaryType::NEUMANN &&
               boundary2.type == Mesh2DTriangular::BoundaryType::NEUMANN) {
        NeumannTriangularMesh(mesh, node_id, mat_b);
    } else {
        throw IncompleteCodeError("undefined boundary condition for triangular mesh");
    }
}

}  // namespace heat_equation_homogeneous
}  // namespace hamt
