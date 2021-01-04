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
        int u_im_j = -1, u_ip_j = -1, u_i_jm = -1, u_i_jp = -1;
        int cell_bl = -1, cell_br = -1, cell_tr = -1, cell_tl = -1;
        NodeType type = MID;
    };

    struct Cell {
        int bounary_left = -1, bounary_buttom = -1, bounary_right = -1, bounary_top = -1;
        uint surface_id;
        uint node1, node2, node3, node4;
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

    double dx_, dy_;
    std::vector<Node> nodes_;
    std::vector<Cell> cells_;
    std::vector<Surface> surfaces_;
    std::vector<Boundary> boundaries_;
};
}  // namespace hamt
