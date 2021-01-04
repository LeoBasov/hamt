#pragma once

#include <Eigen/Dense>
#include <map>
#include <string>
#include <vector>

namespace hamt {
namespace gmsh {
using namespace Eigen;
class MSH2 {
   public:
    struct PhysicalName {
        // physical-dimension physical-tag "physical-name"
        uint physical_dimension, physical_tag;
        std::string physical_name;
    };

    struct Node {
        // node-number x-coord y-coord z-coord
        uint node_number = 0;
        Vector3d coord;
    };

    struct Element {
        // elm-number elm-type number-of-tags < tag > … node-number-list
        int elm_number, elm_type;
        std::vector<int> tags;
        std::vector<int> node_number_list;
    };

    MSH2();
    ~MSH2() = default;

    void Clear();

    std::map<uint, Node> nodes_;
    std::map<uint, PhysicalName> physical_names_;
    std::vector<Element> elements_;
};
}  // namespace gmsh
}  // namespace hamt
