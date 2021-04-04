cmake_minimum_required(VERSION 3.10)

project(pyhamt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(OpenMP REQUIRED)
#find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

include_directories(${EIGEN3_INCLUDE_DIRS}  OpenMP::OpenMP_CXX)
file(GLOB_RECURSE sources ../src/*.cc *.cc)
list(FILTER sources EXCLUDE REGEX "../src/main.cc")

pybind11_add_module(pyhamt ${sources})

target_link_libraries(pyhamt PUBLIC OpenMP::OpenMP_CXX)
