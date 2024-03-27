#include "set_writer.h"

namespace hamt {

SetWriter::SetWriter(std::string command_name) : SubOperation(command_name, "writer") {}

SetWriter::SetWriter() : SubOperation() {}

std::string SetWriter::GetHelp() const { return "Sets parameters for writer"; }

void SetWriter::Check(const std::vector<std::string>& argv) {
    ChecArgvMin(3, argv);
    ChecArgvMax(4, argv);
}

void SetWriter::Execute(const std::vector<std::string>& argv, const bool&) {
    if (hamt_->solver_.GetConfig().mesh_type == Solver::REGULAR) {
        if (argv.at(1) == "vtk") {
            Writer::Config config(hamt_->writer_.GetConfig(Writer::REGULAR, Writer::VTK));

            if (argv.at(2) == "on") {
                ChecArgvExact(3, argv);

                config.activated = true;

                std::cout << "SET WRITER FOR REG_MESH VTK: ON" << std::endl;
            } else if (argv.at(2) == "off") {
                ChecArgvExact(3, argv);

                config.activated = false;

                std::cout << "SET WRITER FOR REG_MESH VTK: OFF" << std::endl;
            } else if (argv.at(2) == "file_name") {
                ChecArgvExact(4, argv);

                config.file_name = argv.at(3);

                std::cout << "SET WRITER FOR REG_MESH VTK FILE NAME: " << config.file_name << std::endl;
            } else if (argv.at(2) == "output_freq") {
                ChecArgvExact(4, argv);

                const int frequency(std::stoi(argv.at(3)));

                if (frequency > 0) {
                    config.frequency = frequency;

                    std::cout << "SET WRITER FOR REG_MESH VTK OUTPUT FREQUENCY: " << config.frequency << std::endl;
                } else {
                    throw CommandError("Frequency must be > 0 [" + argv.at(3) + "]", __PRETTY_FUNCTION__);
                }
            } else {
                throw CommandError("unknown command 'set writer reg_mesh vtk' [" + argv.at(2) + "]",
                                   __PRETTY_FUNCTION__);
            }

            hamt_->writer_.SetConfig(Writer::REGULAR, Writer::VTK, config);
        } else if (argv.at(1) == "csv") {
            Writer::Config config(hamt_->writer_.GetConfig(Writer::REGULAR, Writer::CSV));

            if (argv.at(2) == "on") {
                ChecArgvExact(3, argv);

                config.activated = true;

                std::cout << "SET WRITER FOR REG_MESH CSV: ON" << std::endl;
            } else if (argv.at(2) == "off") {
                ChecArgvExact(3, argv);

                config.activated = false;

                std::cout << "SET WRITER FOR REG_MESH CSV: OFF" << std::endl;
            } else if (argv.at(2) == "file_name") {
                ChecArgvExact(4, argv);

                config.file_name = argv.at(3);

                std::cout << "SET WRITER FOR REG_MESH CSV FILE NAME: " << config.file_name << std::endl;
            } else if (argv.at(2) == "output_freq") {
                ChecArgvExact(4, argv);

                const int frequency(std::stoi(argv.at(3)));

                if (frequency > 0) {
                    config.frequency = frequency;

                    std::cout << "SET WRITER FOR REG_MESH CSV OUTPUT FREQUENCY: " << config.frequency << std::endl;
                } else {
                    throw CommandError("Frequency must be > 0 [" + argv.at(3) + "]", __PRETTY_FUNCTION__);
                }
            } else {
                throw CommandError("unknown command 'set writer reg_mesh csv' [" + argv.at(2) + "]",
                                   __PRETTY_FUNCTION__);
            }

            hamt_->writer_.SetConfig(Writer::REGULAR, Writer::CSV, config);
        } else {
            throw CommandError("unknown command 'set writer reg_mesh' [" + argv.at(1) + "]", __PRETTY_FUNCTION__);
        }
    } else if (hamt_->solver_.GetConfig().mesh_type == Solver::TRIANGULAR) {
        if (argv.at(1) == "vtk") {
            Writer::Config config(hamt_->writer_.GetConfig(Writer::TRIANGULAR, Writer::VTK));

            if (argv.at(2) == "on") {
                ChecArgvExact(3, argv);

                config.activated = true;

                std::cout << "SET WRITER FOR TRIANGL_MESH VTK: ON" << std::endl;
            } else if (argv.at(2) == "off") {
                ChecArgvExact(3, argv);

                config.activated = false;

                std::cout << "SET WRITER FOR TRIANGL_MESH VTK: OFF" << std::endl;
            } else if (argv.at(2) == "file_name") {
                ChecArgvExact(4, argv);

                config.file_name = argv.at(3);

                std::cout << "SET WRITER FOR TRIANGL_MESH VTK FILE NAME: " << config.file_name << std::endl;
            } else if (argv.at(2) == "output_freq") {
                ChecArgvExact(4, argv);

                const int frequency(std::stoi(argv.at(3)));

                if (frequency > 0) {
                    config.frequency = frequency;

                    std::cout << "SET WRITER FOR TRIANGL_MESH VTK OUTPUT FREQUENCY: " << config.frequency << std::endl;
                } else {
                    throw CommandError("Frequency must be > 0 [" + argv.at(3) + "]", __PRETTY_FUNCTION__);
                }
            } else {
                throw CommandError("unknown command 'set writer triangl_mesh vtk' [" + argv.at(2) + "]",
                                   __PRETTY_FUNCTION__);
            }

            hamt_->writer_.SetConfig(Writer::TRIANGULAR, Writer::VTK, config);
        } else if (argv.at(1) == "csv") {
            Writer::Config config(hamt_->writer_.GetConfig(Writer::TRIANGULAR, Writer::CSV));

            if (argv.at(2) == "on") {
                ChecArgvExact(3, argv);

                config.activated = true;

                std::cout << "SET WRITER FOR TRIANGL_MESH CSV: ON" << std::endl;
            } else if (argv.at(2) == "off") {
                ChecArgvExact(3, argv);

                config.activated = false;

                std::cout << "SET WRITER FOR TRIANGL_MESH CSV: OFF" << std::endl;
            } else if (argv.at(2) == "file_name") {
                ChecArgvExact(4, argv);

                config.file_name = argv.at(3);

                std::cout << "SET WRITER FOR TRIANGL_MESH CSV FILE NAME: " << config.file_name << std::endl;
            } else if (argv.at(2) == "output_freq") {
                ChecArgvExact(4, argv);

                const int frequency(std::stoi(argv.at(3)));

                if (frequency > 0) {
                    config.frequency = frequency;

                    std::cout << "SET WRITER FOR TRIANGL_MESH CSV OUTPUT FREQUENCY: " << config.frequency << std::endl;
                } else {
                    throw CommandError("Frequency must be > 0 [" + argv.at(3) + "]", __PRETTY_FUNCTION__);
                }
            } else {
                throw CommandError("unknown command 'set writer triangl_mesh csv' [" + argv.at(2) + "]",
                                   __PRETTY_FUNCTION__);
            }

            hamt_->writer_.SetConfig(Writer::TRIANGULAR, Writer::CSV, config);
        } else {
            throw CommandError("unknown command 'set writer triangl_mesh' [" + argv.at(1) + "]", __PRETTY_FUNCTION__);
        }
    } else {
        throw CommandError("unknown mesh type in 'set writer'", __PRETTY_FUNCTION__);
    }
}

}  // namespace hamt
