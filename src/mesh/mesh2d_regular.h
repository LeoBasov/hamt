#pragma once

#include <Eigen/Dense>
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
        BUTTOM_LEFT,
        BUTTOM_RIGHT,
    };

    enum BoundaryType { NEUMANN, DIRICHLET };

    struct Node {
        // stencil ids
        int u_im_j = -1, u_ip_j = -1, u_i_jm = -1, u_i_jp = -1;
        int cell_bl = -1, cell_br = -1, cell_tr = -1, cell_tl = -1;
        NodeType type = MID;
        Eigen::Vector3d position;
    };

    struct Cell {
        int bounary_left = -1, bounary_buttom = -1, bounary_right = -1, bounary_top = -1;
        uint surface_id;
        uint node1, node2, node3, node4;

        bool IsButtom(uint node_1, uint node_2) const;
        bool IsRight(uint node_1, uint node_2) const;
        bool IsTop(uint node1, uint node2) const;
        bool IsLeft(uint node1, uint node2) const;
    };

    struct Surface {
        double thermal_conductivity;

        inline bool operator==(const Surface& rhs) { return this->thermal_conductivity == rhs.thermal_conductivity; }
        inline bool operator!=(const Surface& rhs) { return !(*this == rhs); }
    };

    struct Boundary {
        BoundaryType type;
        double value;
    };

   public:
    Mesh2DRegular();
    ~Mesh2DRegular() = default;

    void SetBoundaryType(const std::string& name, BoundaryType type);
    void SetBoundaryValue(const std::string& name, const double& value);

    void Clear();

    double dx_, dy_;
    std::vector<Node> nodes_;
    std::vector<Cell> cells_;
    std::vector<Surface> surfaces_;
    std::vector<Boundary> boundaries_;

    std::map<uint, uint> surface_tags_;
    std::map<std::string, uint> surface_names_;

    std::map<uint, uint> boundary_tags_;
    std::map<std::string, uint> boundary_names_;
};
}  // namespace hamt
