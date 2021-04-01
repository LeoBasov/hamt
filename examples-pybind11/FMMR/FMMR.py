import pyhamt

hamt = pyhamt.HAMT()

# set up writer
writer_config = pyhamt.WriterConfig()

writer_config.file_name = "FMMR"
writer_config.activated = True

hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.VTK, writer_config)

# read mesh
hamt.reader.read_reg_mesh("FMMR.msh")

# set up boundary conditions
hamt.data.mesh2d_regular.set_boundary_type("top", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("buttom", pyhamt.Mesh2DRegular.BoundaryType.RADIATION)
hamt.data.mesh2d_regular.set_boundary_type("left_buttom", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("left_top", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("right_buttom", pyhamt.Mesh2DRegular.BoundaryType.RADIATION)
hamt.data.mesh2d_regular.set_boundary_type("right_top", pyhamt.Mesh2DRegular.BoundaryType.RADIATION)

# set up boundary values
hamt.data.mesh2d_regular.set_boundary_value("top", 575.0)
hamt.data.mesh2d_regular.set_boundary_value("buttom", 1)
hamt.data.mesh2d_regular.set_boundary_value("left_buttom", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("left_top", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("right_buttom", 1)
hamt.data.mesh2d_regular.set_boundary_value("right_top", 1)

print("SETUP COMPLETE")
print("BEGIN SIMULATION")
print(80*"-")

#run
for i in range(30):
    hamt.solver.execute()
    hamt.writer.write(i)
    print("ITERATION {} COMPLETE".format(i + 1))

print(80*"-")
print("DONE")
