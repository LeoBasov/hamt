# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
- Algorithms  to solve the 2d homogeneous heat equation on a regular mesh in cartesian coordinates with a volumetric heat source
- Algorithms  to solve the 2d homogeneous heat equation on a regular mesh in cylinder coordinates with a volumetric heat source
- Relative error calculation for black body radiation boundary condition
- Full heat equation on a 2d regular mesh in cartesian coordinates
- Full heat equation on a 2d regular mesh in cylinder coordinates
- Possibility to compile hampt as a python module

## 1.3.0 - 2022-03-25
### Added
- Rading of triangular mesh from gmsh 2 format
- VTK writer for triangular mesh
- CSV writer for triangular mesh
- Heat transfer in cartesian coordinates on triangular mesh

## 1.2.0 - 2021-07-23
### Added
- Added cmake project using pybind11
- Exposed HAMT to python
- Exposed Reader to python
- Exposed Writer to python
- Exposed Writer::Config to python
- Added examples as python scripts
### Changed
- Extended setup file to install pybind11 related libraries
- Updated requirements section in README.md file
### Fixed
- Fixed typos

## 1.1.1 - 2021-04-01
### Added
- Added new features to unreleased stack in changelog
### Fixed
- Fixed keyword usage in changelog

## [1.1.0](https://github.com/LeoBasov/hamt/tree/v1.1.0) - 2021-03-08
### Added
- Black body radiation boundary condition with adjustable emission coefficient
### Fixed
- Fixed typos in changelog

## [1.0.0](https://github.com/LeoBasov/hamt/tree/v1.0.0) - 2021-01-21
### Added
- Functionality to read GMSH files of type msh2
- Functionality to write to vtk file format readable by ParaView
- Algorithms  to solve the 2d homogeneous heat equation on a regular mesh in cartesian coordinates
- Algorithms  to solve the 2d homogeneous heat equation on a regular mesh in cylinder coordinates
- Neumann boundary conditions
- Dirichlet boundary conditions
- Parser to process input files
- First draft of Latex based documentation
