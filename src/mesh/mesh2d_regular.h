#pragma once

#include <map>
#include <vector>

using uint = unsigned int;

namespace hamt {
class Mesh2DRegular {
   public:
    enum NodeType {
        MID,
        LEFT,
        BUTTOM,
        RIGHT,
        TOP,
        TOP_LEFT,
        TOP_RIGHT,
        BUTTOM_LEFTL,
        BUTTON_RIGHT,
        CROSS_H,
        CROSS_V,
        CROSS_HV
    };

    enum BoundaryType { NEUMANN, DIRICHLET };

    struct Node {
        // stencil ids
        uint u_im_j, u_ip_j, u_i_jm, u_i_jp;
        uint cell_bl, cell_br, cell_tr, cell_tl;
        NodeType type = MID;
    };

    struct Cell {
        uint bounary_left, bounary_buttom, bounary_right, bounary_top;
        uint surface_id;
    };

    struct Surface {
        double thermal_conductivity;
    };

    struct Boundary {
        BoundaryType type;
        double value;
    };

   public:
    Mesh2DRegular();
    ~Mesh2DRegular() = default;

    void Clear();

   private:
    double dx_, dy_;
    std::vector<Node> nodes_;
    std::vector<Cell> cells_;
    std::vector<Surface> surfaces_;
    std::vector<Boundary> boundaries_;
};
}  // namespace hamt
