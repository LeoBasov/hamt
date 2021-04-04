######################################
#                                    #
# Regression test for cartesian mesh #
#                                    #
######################################

import pyhamt

hamt = pyhamt.HAMT()
writer_config = pyhamt.WriterConfig()

# Vertical homog surf
#=====================================
# laod mesh
hamt.reader.read_reg_mesh("block_4_segments.msh")

# set writer status
writer_config.file_name = "reg_car_hom_new"
writer_config.activated = True

hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.VTK, writer_config)
hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.CSV, writer_config)

# set boundary conditions
hamt.data.mesh2d_regular.set_boundary_type("buttom_left", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("buttom_right", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("top_left", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("top_right", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("left_buttom", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("right_buttom", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("left_top", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("right_top", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)

hamt.data.mesh2d_regular.set_boundary_value("buttom_left", 100.0)
hamt.data.mesh2d_regular.set_boundary_value("buttom_right", 100.0)
hamt.data.mesh2d_regular.set_boundary_value("top_left", 300.0)
hamt.data.mesh2d_regular.set_boundary_value("top_right", 300.0)
hamt.data.mesh2d_regular.set_boundary_value("left_buttom", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("right_buttom", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("left_top", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("right_top", 0.0)

hamt.solver.execute()
hamt.writer.write()

# Horizontal homog surf
#=====================================
# set writer status
writer_config.file_name = "reg_car_hom_1_new"
writer_config.activated = True

hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.VTK, writer_config)
hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.CSV, writer_config)

# set boundary conditions
hamt.data.mesh2d_regular.set_boundary_type("buttom_left", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("buttom_right", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("top_left", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("top_right", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("left_buttom", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("right_buttom", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("left_top", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("right_top", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)

hamt.data.mesh2d_regular.set_boundary_value("buttom_left", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("buttom_right", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("top_left", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("top_right", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("left_buttom", 100.0)
hamt.data.mesh2d_regular.set_boundary_value("right_buttom", 300.0)
hamt.data.mesh2d_regular.set_boundary_value("left_top", 100.0)
hamt.data.mesh2d_regular.set_boundary_value("right_top", 300.0)

hamt.solver.execute()
hamt.writer.write()

# Horizontal heter surf
#=====================================
# set writer status
writer_config.file_name = "reg_car_hom_2_new"
writer_config.activated = True

hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.VTK, writer_config)
hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.CSV, writer_config)

# set boundary conditions
hamt.data.mesh2d_regular.set_boundary_type("buttom_left", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("buttom_right", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("top_left", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("top_right", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("left_buttom", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("right_buttom", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("left_top", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("right_top", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)

hamt.data.mesh2d_regular.set_boundary_value("buttom_left", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("buttom_right", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("top_left", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("top_right", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("left_buttom", 100.0)
hamt.data.mesh2d_regular.set_boundary_value("right_buttom", 300.0)
hamt.data.mesh2d_regular.set_boundary_value("left_top", 100.0)
hamt.data.mesh2d_regular.set_boundary_value("right_top", 300.0)

hamt.data.mesh2d_regular.set_surface_thermal_conductivity("surf_bl", 150)
hamt.data.mesh2d_regular.set_surface_thermal_conductivity("surf_br", 100)
hamt.data.mesh2d_regular.set_surface_thermal_conductivity("surf_tl", 150)
hamt.data.mesh2d_regular.set_surface_thermal_conductivity("surf_tr", 100)

hamt.solver.execute()
hamt.writer.write()

# Vertical heter surf
#=====================================
# set writer status
writer_config.file_name = "reg_car_hom_3_new"
writer_config.activated = True

hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.VTK, writer_config)
hamt.writer.set_config(pyhamt.Writer.MeshType.REGULAR, pyhamt.Writer.FileFormat.CSV, writer_config)

# set boundary conditions
hamt.data.mesh2d_regular.set_boundary_type("buttom_left", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("buttom_right", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("top_left", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("top_right", pyhamt.Mesh2DRegular.BoundaryType.DIRICHLET)
hamt.data.mesh2d_regular.set_boundary_type("left_buttom", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("right_buttom", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("left_top", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)
hamt.data.mesh2d_regular.set_boundary_type("right_top", pyhamt.Mesh2DRegular.BoundaryType.NEUMANN)

hamt.data.mesh2d_regular.set_boundary_value("buttom_left", 100.0)
hamt.data.mesh2d_regular.set_boundary_value("buttom_right", 100.0)
hamt.data.mesh2d_regular.set_boundary_value("top_left", 300.0)
hamt.data.mesh2d_regular.set_boundary_value("top_right", 300.0)
hamt.data.mesh2d_regular.set_boundary_value("left_buttom", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("right_buttom", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("left_top", 0.0)
hamt.data.mesh2d_regular.set_boundary_value("right_top", 0.0)

hamt.data.mesh2d_regular.set_surface_thermal_conductivity("surf_bl", 150)
hamt.data.mesh2d_regular.set_surface_thermal_conductivity("surf_br", 150)
hamt.data.mesh2d_regular.set_surface_thermal_conductivity("surf_tl", 100)
hamt.data.mesh2d_regular.set_surface_thermal_conductivity("surf_tr", 100)

hamt.solver.execute()
hamt.writer.write()
