import csv
import pyhamt as ph
import os

def set_up_hamt():
	hamt = ph.HAMT()
	writer_config = ph.WriterConfig()
	solver_config = ph.SolverConfig()

	solver_config.mesh_type = ph.Solver.MeshType.TRIANGULAR

	writer_config.file_name = "block"
	writer_config.activated = True

	hamt.solver.config = solver_config

	hamt.writer.set_config(ph.Writer.MeshType.TRIANGULAR, ph.Writer.FileFormat.CSV, writer_config)

	hamt.reader.read_triangl_mesh("block.msh")

	return hamt

def linear_model(T0, T1, x0, x1, x):
	return T0*((x1 - x) / (x1 - x0)) + T1*((x - x0) / (x1 - x0))

def test_temp_homogene_vertical():
	hamt = set_up_hamt()

	# setting boundary types
	hamt.data.mesh2d_triangular.set_boundary_type("l_buttom_left", ph.Mesh2DTriangular.BoundaryType.DIRICHLET)
	hamt.data.mesh2d_triangular.set_boundary_type("l_buttom_right", ph.Mesh2DTriangular.BoundaryType.DIRICHLET)

	hamt.data.mesh2d_triangular.set_boundary_type("l_right_buttom", ph.Mesh2DTriangular.BoundaryType.NEUMANN)
	hamt.data.mesh2d_triangular.set_boundary_type("l_right_top", ph.Mesh2DTriangular.BoundaryType.NEUMANN)

	hamt.data.mesh2d_triangular.set_boundary_type("l_top_right", ph.Mesh2DTriangular.BoundaryType.DIRICHLET)
	hamt.data.mesh2d_triangular.set_boundary_type("l_top_left", ph.Mesh2DTriangular.BoundaryType.DIRICHLET)

	hamt.data.mesh2d_triangular.set_boundary_type("l_left_top", ph.Mesh2DTriangular.BoundaryType.NEUMANN)
	hamt.data.mesh2d_triangular.set_boundary_type("l_left_buttom", ph.Mesh2DTriangular.BoundaryType.NEUMANN)

	# setting boundary values
	hamt.data.mesh2d_triangular.set_boundary_value("l_buttom_left", 100.0)
	hamt.data.mesh2d_triangular.set_boundary_value("l_buttom_right", 100.0)

	hamt.data.mesh2d_triangular.set_boundary_value("l_right_buttom", 0.0)
	hamt.data.mesh2d_triangular.set_boundary_value("l_right_top", 0.0)

	hamt.data.mesh2d_triangular.set_boundary_value("l_top_right", 300.0)
	hamt.data.mesh2d_triangular.set_boundary_value("l_top_left", 300.0)

	hamt.data.mesh2d_triangular.set_boundary_value("l_left_top", 0.0)
	hamt.data.mesh2d_triangular.set_boundary_value("l_left_buttom", 0.0)

	hamt.solver.execute()
	hamt.writer.write()

	with open('block.csv') as block:
		spamreader = csv.reader(block)
		for row in spamreader:
			T = float(row[0])
			y = float(row[2])
			Tref = linear_model(100, 300, -1, 1, y)

			assert T == Tref

	os.remove('block.csv')

def test_temp_homogene_horizontal():
	hamt = set_up_hamt()

	# setting boundary types
	hamt.data.mesh2d_triangular.set_boundary_type("l_buttom_left", ph.Mesh2DTriangular.BoundaryType.NEUMANN)
	hamt.data.mesh2d_triangular.set_boundary_type("l_buttom_right", ph.Mesh2DTriangular.BoundaryType.NEUMANN)

	hamt.data.mesh2d_triangular.set_boundary_type("l_right_buttom", ph.Mesh2DTriangular.BoundaryType.DIRICHLET)
	hamt.data.mesh2d_triangular.set_boundary_type("l_right_top", ph.Mesh2DTriangular.BoundaryType.DIRICHLET)

	hamt.data.mesh2d_triangular.set_boundary_type("l_top_right", ph.Mesh2DTriangular.BoundaryType.NEUMANN)
	hamt.data.mesh2d_triangular.set_boundary_type("l_top_left", ph.Mesh2DTriangular.BoundaryType.NEUMANN)

	hamt.data.mesh2d_triangular.set_boundary_type("l_left_top", ph.Mesh2DTriangular.BoundaryType.DIRICHLET)
	hamt.data.mesh2d_triangular.set_boundary_type("l_left_buttom", ph.Mesh2DTriangular.BoundaryType.DIRICHLET)

	# setting boundary values
	hamt.data.mesh2d_triangular.set_boundary_value("l_buttom_left", 0.0)
	hamt.data.mesh2d_triangular.set_boundary_value("l_buttom_right", 0.0)

	hamt.data.mesh2d_triangular.set_boundary_value("l_right_buttom", 300.0)
	hamt.data.mesh2d_triangular.set_boundary_value("l_right_top", 300.0)

	hamt.data.mesh2d_triangular.set_boundary_value("l_top_right", 0.0)
	hamt.data.mesh2d_triangular.set_boundary_value("l_top_left", 0.0)

	hamt.data.mesh2d_triangular.set_boundary_value("l_left_top", 100.0)
	hamt.data.mesh2d_triangular.set_boundary_value("l_left_buttom", 100.0)

	hamt.solver.execute()
	hamt.writer.write()

	with open('block.csv') as block:
		spamreader = csv.reader(block)
		for row in spamreader:
			T = float(row[0])
			x = float(row[1])
			Tref = linear_model(100, 300, -1, 1, x)

			assert T == Tref

	os.remove('block.csv')
