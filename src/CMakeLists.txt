cmake_minimum_required(VERSION 3.10)

project(hamt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(OpenMP REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIRS})
file(GLOB_RECURSE sources *.cc *.h)
add_executable(hamt ${sources})
target_link_libraries(hamt ${EIGEN3_LIBRARIES} OpenMP::OpenMP_CXX)
