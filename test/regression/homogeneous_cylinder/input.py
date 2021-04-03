import pyhamt

hamt = pyhamt.HAMT()
writer_config = pyhamt.WriterConfig()

writer_config.file_name = "cylinder_test"
writer_config.activated = True

hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.VTK, writer_config)
hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.CSV, writer_config)

hamt.reader.read_reg_mesh("block.msh")

hamt.data.mesh2d_regular.set_boundary_type("buttom", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("top", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("left_buttom", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("right_buttom", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("left_top", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("right_top", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)

hamt.data.mesh2d_regular.set_boundary_value("buttom", 100.0)
hamt.data.mesh2d_regular.set_boundary_value("top", 300.0)
hamt.data.mesh2d_regular.set_boundary_value("left_buttom", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("right_buttom", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("left_top", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("right_top", 0.0)

hamt.data.mesh2d_regular.set_surface_thermal_conductivity("buttom_surf", 10)
hamt.data.mesh2d_regular.set_surface_thermal_conductivity("top_surf", 50)

solver_config = pyhamt.SolverConfig()

solver_config.coord_type = pyhamt.Solver.CoordinatesType.CYLINDER

hamt.solver.config = solver_config

hamt.solver.execute()
hamt.writer.write()
