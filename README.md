# HAMT - Heat and Mass Transfer simulation suit
Solver for heat and mass transfer
[![LeoBasov](https://circleci.com/gh/LeoBasov/hamt.svg?style=svg)](https://app.circleci.com/pipelines/github/LeoBasov/hamt/)

# Table of Contents
1. Introduction
2. Requirements
3. Installation

# 1. Introduction
Simulation suit to solve problems from the domain of heat and mass transfer.

# 2. Requirements
- Ubuntu 18.04.
- g++ compiler
- CMake
- Eigen C++ template library for linear algebra
- OpenMP
- gtest (for unit tests only)

# 3. Installation
The only dependencies at the moment are Eigen and OpenMP.
```
sudo apt install cmake
sudo apt install libeigen3-dev
sudo apt install libomp-dev
```
To use gtest for unit tets
```
sudo apt install libgtest-dev
cd /usr/src/gtest/
sudo cmake -DBUILD_SHARED_LIBS=ON
sudo make
sudo cp *.so /usr/lib
```
