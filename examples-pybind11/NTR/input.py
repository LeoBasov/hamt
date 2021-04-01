import pyhamt

hamt = pyhamt.HAMT()

print("BEGIN SETUP")
print(80*"-")

#Set up writer
writer_config = pyhamt.WriterConfig()

writer_config.activated = True
writer_config.file_name = "ntr"

hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.VTK, writer_config)
hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.CSV, writer_config)

#Read mesh
hamt.reader.read_reg_mesh("ntr.msh")

#Set boundary type
hamt.data.mesh2d_regular.set_boundary_type("attachment", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)

hamt.data.mesh2d_regular.set_boundary_type("housing_top", pyhamt.Mesh2DRegular.BoundaryType.RADIATION)
hamt.data.mesh2d_regular.set_boundary_type("housing_buttom", pyhamt.Mesh2DRegular.BoundaryType.RADIATION)

hamt.data.mesh2d_regular.set_boundary_type("emitter_left", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("emitter_buttom", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)

hamt.data.mesh2d_regular.set_boundary_type("keeper_top", pyhamt.Mesh2DRegular.BoundaryType.RADIATION)
hamt.data.mesh2d_regular.set_boundary_type("keeper_front", pyhamt.Mesh2DRegular.BoundaryType.RADIATION)
hamt.data.mesh2d_regular.set_boundary_type("keeper_buttom", pyhamt.Mesh2DRegular.BoundaryType.RADIATION)
hamt.data.mesh2d_regular.set_boundary_type("keeper_left", pyhamt.Mesh2DRegular.BoundaryType.RADIATION)

#Set boundary values
hamt.data.mesh2d_regular.set_boundary_value("attachment", 300.0)

hamt.data.mesh2d_regular.set_boundary_value("housing_top", 1)
hamt.data.mesh2d_regular.set_boundary_value("housing_buttom", 1)

hamt.data.mesh2d_regular.set_boundary_value("emitter_left", 1000)
hamt.data.mesh2d_regular.set_boundary_value("emitter_buttom", 1000)

hamt.data.mesh2d_regular.set_boundary_value("keeper_top", 1)
hamt.data.mesh2d_regular.set_boundary_value("keeper_front", 1)
hamt.data.mesh2d_regular.set_boundary_value("keeper_buttom", 1)
hamt.data.mesh2d_regular.set_boundary_value("keeper_left", 1)

#Set up solver
solver_config = pyhamt.SolverConfig()

solver_config.coord_type = pyhamt.Solver.CoordinatesType.CYLINDER

hamt.solver.config = solver_config

print("SETUP COMPLETE")
print("BEGIN SIMULATION")
print(80*"-")

#run
for i in range(5):
    hamt.solver.execute()
    hamt.writer.write(i)
    print("ITERATION {} COMPLETE".format(i + 1))

print(80*"-")
print("DONE")
