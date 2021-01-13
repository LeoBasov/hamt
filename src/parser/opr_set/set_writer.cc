#include "set_writer.h"

namespace hamt {

SetWriter::SetWriter(std::string command_name) : SubOperation(command_name, "writer") {}

SetWriter::SetWriter() : SubOperation() {}

std::string SetWriter::GetHelp() const { return "Sets parameters for writer"; }

void SetWriter::Check(const std::vector<std::string>& argv) { ChecArgvMin(4, argv); }

void SetWriter::Execute(const std::vector<std::string>& argv, const bool&) {
    if (argv.at(1) == "reg_mesh") {
        if (argv.at(2) == "vtk") {
            Writer::Config config(hamt_->writer_.GetConfig(Writer::REGULAR, Writer::VTK));

            if (argv.at(3) == "on") {
                ChecArgvExact(4, argv);

                config.activated = true;

                std::cout << "SET WRITER FOR REG_MESH VTK: ON" << std::endl;
            } else if (argv.at(3) == "off") {
                ChecArgvExact(4, argv);

                config.activated = false;

                std::cout << "SET WRITER FOR REG_MESH VTK: OFF" << std::endl;
            } else if (argv.at(3) == "file_name") {
                ChecArgvExact(5, argv);

                config.file_name = argv.at(4);

                std::cout << "SET WRITER FOR REG_MESH VTK FILE NAME: " << config.file_name << std::endl;
            } else if (argv.at(3) == "output_freq") {
                ChecArgvExact(5, argv);

                const int frequency(std::stoi(argv.at(4)));

                if (frequency > 0) {
                    config.frequency = frequency;

                    std::cout << "SET WRITER FOR REG_MESH VTK OUTPUT FREQUENCY: " << config.frequency << std::endl;
                } else {
                    throw CommandError("Frequency must be > 0 [" + argv.at(4) + "]", __PRETTY_FUNCTION__);
                }
            } else {
                throw CommandError("unknown command 'set writer reg_mesh vtk' [" + argv.at(3) + "]",
                                   __PRETTY_FUNCTION__);
            }

            hamt_->writer_.SetConfig(Writer::REGULAR, Writer::VTK, config);
        } else {
            throw CommandError("unknown command 'set writer reg_mesh' [" + argv.at(2) + "]", __PRETTY_FUNCTION__);
        }
    } else {
        throw CommandError("unknown command 'set writer' [" + argv.at(1) + "]", __PRETTY_FUNCTION__);
    }
}

}  // namespace hamt
