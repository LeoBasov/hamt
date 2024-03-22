import pyhamt

hamt = pyhamt.HAMT()

print("BEGIN SETUP")
print(80*"-")

#Set up writer
writer_config = pyhamt.WriterConfig()

writer_config.activated = True
writer_config.file_name = "ntr"

hamt.writer.set_config(pyhamt.Writer.MeshType.TRIANGULAR, pyhamt.Writer.FileFormat.VTK, writer_config)
#hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.CSV, writer_config)

#Read mesh
hamt.reader.read_triangl_mesh("ntr.msh")

#Set boundary type
hamt.data.mesh2d_triangular.set_boundary_type("attachment", pyhamt.Mesh2DTriangular.BoundaryType.DIRICHLET)

hamt.data.mesh2d_triangular.set_boundary_type("housing_top", pyhamt.Mesh2DTriangular.BoundaryType.RADIATION)
hamt.data.mesh2d_triangular.set_boundary_type("housing_buttom", pyhamt.Mesh2DTriangular.BoundaryType.RADIATION)

hamt.data.mesh2d_triangular.set_boundary_type("emitter_left", pyhamt.Mesh2DTriangular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_triangular.set_boundary_type("emitter_buttom", pyhamt.Mesh2DTriangular.BoundaryType.DIRICHLET)

hamt.data.mesh2d_triangular.set_boundary_type("keeper_top", pyhamt.Mesh2DTriangular.BoundaryType.RADIATION)
hamt.data.mesh2d_triangular.set_boundary_type("keeper_front", pyhamt.Mesh2DTriangular.BoundaryType.RADIATION)
hamt.data.mesh2d_triangular.set_boundary_type("keeper_buttom", pyhamt.Mesh2DTriangular.BoundaryType.RADIATION)
hamt.data.mesh2d_triangular.set_boundary_type("keeper_left", pyhamt.Mesh2DTriangular.BoundaryType.RADIATION)

#Set boundary values
hamt.data.mesh2d_triangular.set_boundary_value("attachment", 300.0)

hamt.data.mesh2d_triangular.set_boundary_value("housing_top", 1)
hamt.data.mesh2d_triangular.set_boundary_value("housing_buttom", 1)

hamt.data.mesh2d_triangular.set_boundary_value("emitter_left", 1000)
hamt.data.mesh2d_triangular.set_boundary_value("emitter_buttom", 1000)

hamt.data.mesh2d_triangular.set_boundary_value("keeper_top", 1)
hamt.data.mesh2d_triangular.set_boundary_value("keeper_front", 1)
hamt.data.mesh2d_triangular.set_boundary_value("keeper_buttom", 1)
hamt.data.mesh2d_triangular.set_boundary_value("keeper_left", 1)

#Set up solver
solver_config = pyhamt.SolverConfig()

solver_config.mesh_type = pyhamt.Solver.MeshType.TRIANGULAR
solver_config.coord_type = pyhamt.Solver.CoordinatesType.CYLINDER

hamt.solver.config = solver_config

print("SETUP COMPLETE")
print("BEGIN SIMULATION")
print(80*"-")

#run
hamt.solver.execute()
hamt.writer.write()

print(80*"-")
print("DONE")
