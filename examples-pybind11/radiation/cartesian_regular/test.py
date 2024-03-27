import pyhamt

print('CARTESIAN BLOCKS TEST')

hamt = pyhamt.HAMT()
writer_config = pyhamt.WriterConfig()

writer_config.file_name = "cuboid"
writer_config.activated = True

hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.VTK, writer_config)
#hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.CSV, writer_config)

hamt.reader.read_reg_mesh("block.msh")

hamt.data.mesh2d_regular.set_boundary_type("buttom", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("top", pyhamt.Mesh2DRegular.BoundaryType.RADIATION)
hamt.data.mesh2d_regular.set_boundary_type("left_buttom", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("right_buttom", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("left_top", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("right_top", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)

hamt.data.mesh2d_regular.set_boundary_value("buttom", 1000.0)
hamt.data.mesh2d_regular.set_boundary_value("top", 1.0)
hamt.data.mesh2d_regular.set_boundary_value("left_buttom", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("right_buttom", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("left_top", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("right_top", 0.0)

hamt.data.mesh2d_regular.set_surface_thermal_conductivity("buttom_surf", 100)
hamt.data.mesh2d_regular.set_surface_thermal_conductivity("top_surf", 100)

for i in range(100):
	hamt.solver.execute()
	print(i + 1)

hamt.writer.write()

print('DONE')
