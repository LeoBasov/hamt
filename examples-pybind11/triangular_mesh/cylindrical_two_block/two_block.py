import pyhamt

print('CARTESIAN BLOCKS TEST')

hamt = pyhamt.HAMT()
writer_config = pyhamt.WriterConfig()
solver_config = pyhamt.SolverConfig()

solver_config.mesh_type = pyhamt.Solver.MeshType.TRIANGULAR
solver_config.coord_type = pyhamt.Solver.CoordinatesType.CYLINDER

hamt.solver.config = solver_config

writer_config.file_name = "two_blocks"
writer_config.activated = True

hamt.writer.set_config(pyhamt.Writer.MeshType.TRIANGULAR, pyhamt.Writer.FileFormat.VTK, writer_config)
hamt.writer.set_config(pyhamt.Writer.MeshType.TRIANGULAR, pyhamt.Writer.FileFormat.CSV, writer_config)

hamt.reader.read_triangl_mesh("two_blocks.msh")

hamt.data.mesh2d_triangular.set_boundary_type("l_buttom", pyhamt.Mesh2DTriangular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_triangular.set_boundary_type("l_top", pyhamt.Mesh2DTriangular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_triangular.set_boundary_type("l_buttom_left", pyhamt.Mesh2DTriangular.BoundaryType.NEUMANN)
hamt.data.mesh2d_triangular.set_boundary_type("l_buttom_right", pyhamt.Mesh2DTriangular.BoundaryType.NEUMANN)
hamt.data.mesh2d_triangular.set_boundary_type("l_top_left", pyhamt.Mesh2DTriangular.BoundaryType.NEUMANN)
hamt.data.mesh2d_triangular.set_boundary_type("l_top_right", pyhamt.Mesh2DTriangular.BoundaryType.NEUMANN)

hamt.data.mesh2d_triangular.set_boundary_value("l_buttom", 300.0)
hamt.data.mesh2d_triangular.set_boundary_value("l_top", 100.0)
hamt.data.mesh2d_triangular.set_boundary_value("l_buttom_left", 0.0)
hamt.data.mesh2d_triangular.set_boundary_value("l_buttom_right", 0.0)
hamt.data.mesh2d_triangular.set_boundary_value("l_top_left", 0.0)
hamt.data.mesh2d_triangular.set_boundary_value("l_top_right", 0.0)

hamt.data.mesh2d_triangular.set_surface_thermal_conductivity("buttom", 50)
hamt.data.mesh2d_triangular.set_surface_thermal_conductivity("top", 20)

hamt.solver.execute()

hamt.writer.write()

print('DONE')
