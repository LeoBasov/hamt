#pragma once

#include <fstream>
#include <iterator>
#include <string>

#include "../../exception/exception.h"
#include "msh2.h"

namespace hamt {
namespace gmsh {

double GetFileFormat(const std::string& file_name);

MSH2 ReadMSH2(const std::string& file_name);
void CheckFileFormatMSH2(const std::string& file_name);
void ReadPhysicalNamesMSH2(const std::string& file_name, MSH2& mesh);
void ReadNodesMSH2(const std::string& file_name, MSH2& mesh);
void ReadElementsMSH2(const std::string& file_name, MSH2& mesh);
void CheckMeshMSH2(MSH2& mesh);

}  // namespace gmsh
}  // namespace hamt
