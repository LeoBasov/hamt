import csv
import pyhamt as ph
import os
import math

def set_up_hamt():
	hamt = ph.HAMT()
	writer_config = ph.WriterConfig()
	solver_config = ph.SolverConfig()

	solver_config.mesh_type = ph.Solver.MeshType.TRIANGULAR

	writer_config.file_name = "cylinder"
	writer_config.activated = True

	hamt.solver.config = solver_config

	hamt.writer.set_config(ph.Writer.MeshType.TRIANGULAR, ph.Writer.FileFormat.CSV, writer_config)

	hamt.reader.read_triangl_mesh("cylinder.msh")

	return hamt

def cylinder_model(T0, T1, r0, r1, r):
	return T0 + (T1 - T0)*(math.log(r/r0) / math.log(r1/r0))

def test_temp_homogene():
	hamt = set_up_hamt()

	# setting boundary types
	hamt.data.mesh2d_triangular.set_boundary_type("left", ph.Mesh2DTriangular.BoundaryType.NEUMANN)
	hamt.data.mesh2d_triangular.set_boundary_type("right", ph.Mesh2DTriangular.BoundaryType.NEUMANN)

	hamt.data.mesh2d_triangular.set_boundary_type("inner", ph.Mesh2DTriangular.BoundaryType.DIRICHLET)
	hamt.data.mesh2d_triangular.set_boundary_type("outer", ph.Mesh2DTriangular.BoundaryType.DIRICHLET)


	# setting boundary values
	hamt.data.mesh2d_triangular.set_boundary_value("inner", 100.0)
	hamt.data.mesh2d_triangular.set_boundary_value("outer", 300.0)

	hamt.data.mesh2d_triangular.set_boundary_value("left", 0.0)
	hamt.data.mesh2d_triangular.set_boundary_value("right", 0.0)


	hamt.solver.execute()
	hamt.writer.write()

	with open('cylinder.csv') as cylinder:
		spamreader = csv.reader(cylinder)
		for row in spamreader:
			T = float(row[0])
			x = float(row[1])
			y = float(row[2])
			r = math.sqrt(x*x + y*y)
			Tref = cylinder_model(100, 300, 1, 2, r)

			dt = abs(Tref - T)/Tref

			assert dt < 1e-1

	os.remove('cylinder.csv')
