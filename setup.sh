#!/bin/bash

sudo apt update

sudo apt install -y gcc g++
sudo apt install -y cmake
sudo apt install -y libeigen3-dev
sudo apt install -y libomp-dev

if [ "$1" == "-gtest" ]; then
    sudo apt install -y libgtest-dev
    cd /usr/src/gtest
    sudo cmake CMakeLists.txt
    sudo make
    sudo cp *.a /usr/lib
    echo "INSTALLATION COMPLETE"
elif [ "$1" == "-pybind11" ]; then
    sudo apt install -y python3
    sudo apt install -y python3-pip
    pip3 install "pybind11[global]"
    pip3 install pytest
    echo "INSTALLATION COMPLETE"
else
    echo "INSTALLATION COMPLETE"
fi
