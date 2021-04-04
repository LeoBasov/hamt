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

## 2.1 Base
- Ubuntu 18.04.
- g++ compiler
- CMake
- Eigen C++ template library for linear algebra
- OpenMP

## 2.2 Unit tests
- gtest

## 2.3 pybind11
- python3
- pybind11

# 3. Installation

## 3.1 Manual

### 3.1.1 Pure c++
The only dependencies at the moment are Eigen and OpenMP.
```
sudo apt install cmake
sudo apt install libeigen3-dev
sudo apt install libomp-dev
```

### 3.1.2 gtest
To use gtest for unit tets
```
sudo apt install libgtest-dev
cd /usr/src/gtest/
sudo cmake -DBUILD_SHARED_LIBS=ON
sudo make
sudo cp *.so /usr/lib
```

### 3.1.3 pybind11
```
sudo apt install cmake
sudo apt install libeigen3-dev
sudo apt install libomp-dev
sudo apt install python3
sudo apt install python3-pip
pip3 install "pybind11[global]"
```

## 3.2 Automatic


### 3.2.1 Pure c++
```
./setup.sh
```

or
```
bash setup.sh
```

### 3.2.2 gtest
```
./setup.sh -gtest
```

### 3.2.3 pybind11
```
./setup.sh -pybind11
```

# 3. Building

## 3.1 pybind11
```
cd hamt/pyhamt/
cmake -DCMAKE_BUILD_TYPE=Release ../pybind11
pip3 install ..
```
