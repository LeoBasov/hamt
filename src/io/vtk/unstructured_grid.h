#pragma once

#include <fstream>
#include <tuple>
#include <vector>

#include "../../exception/exception.h"
#include "../../mesh/mesh2d_regular.h"

namespace hamt {
namespace vtk {
namespace unstructured_grid {

void WriteMesh2DRegular(const Mesh2DRegular& mesh, const std::string& file_name,
                        const std::vector<std::pair<std::string, std::vector<double>>>& point_data);

void WriteHeader(std::ofstream& stream);
void WriteFooter(std::ofstream& stream);

void WriteBody(std::ofstream& stream, const Mesh2DRegular& mesh,
               const std::vector<std::pair<std::string, std::vector<double>>>& point_data);
void WritePoints(std::ofstream& stream, const Mesh2DRegular& mesh);
void WriteCells(std::ofstream& stream, const Mesh2DRegular& mesh);

void WritePointData(std::ofstream& stream, const std::vector<std::pair<std::string, std::vector<double>>>& point_data);

}  // namespace unstructured_grid
}  // namespace vtk
}  // namespace hamt
