# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
- Full heat equation on a 2d regular mesh in cartesian coordinates
- Full heat equation on a 2d regular mesh in cylinder coordinates
- Writer for hdf5 files

## 2.1.1 - 2024-04-01
### Fixed
- bug in volumetric heat source term

## 2.1.0 - 2024-03-30
### Added
- Algorithms to solve the 2d homogeneous heat equation on a triangular mesh in cartesian coordinates with a volumetric heat source
- Algorithms to solve the 2d homogeneous heat equation on a triangular mesh in cylinder coordinates with a volumetric heat source
- Relative error calculation for black body radiation boundary condition

## 2.0.1 - 2024-03-30
### Added
- Relative error calculation for solver

### Changed
- refactored solver

## 2.0.0 - 2024-03-27
### Changed
- simplified input format
- grid type is not set for all modules when reading grid

## 1.6.0 - 2024-03-27
### Added
- Possibility to compile hampt as a python module
- Black body radiation boundary condition with adjustable emission coefficient for unstructured triangular mesh
- Heat flux boundary condition for unstructured triangular mesh

## 1.5.0 - 2024-02-19
### Added
- Algorithms to solve the 2d homogeneous heat equation on a triangular mesh in cylinder coordinates

## 1.4.1 - 2022-05-27
### Fixed
- Bug where material heat conductivity would be considered in the Neumann boundary condition

## 1.4.0 - 2022-05-27
### Added
- Capability to used heat transfer in cartesian coordinates on triangular mesh in pyhamt

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
