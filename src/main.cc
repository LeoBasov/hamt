/*
HAMT Simulation Tool
Copyright (C) 2020  Leo Basov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>

#include "exception/incomplete_code_error.h"
#include "exception/load_pass.h"
#include "parser/controller.h"
#include "parser/parser.h"

using namespace hamt;

void WriteHeader(), WriteCopyright(), WriteLicense(), WriteLicenceWarranty(), WriteLicenceRedistribution(),
    WriteCredits();

void WriteHelp(const Controller &controller);

int ProcessFile(Controller &controller, const std::string &file_name, const std::string &relative_dir,
                const bool &test_mode);

void ChecArgvExact(const uint &size, const std::vector<std::string> &argv);

int main(int argc, char *argv[]) {
    bool run(true);
    Parser parser;
    Controller controller;

    WriteHeader();

    if (argc == 1) {
        while (run) {
            std::cout << ">>> ";
            parser.ParseShell();

            if (parser.command_.name == "quit") {
                run = false;
            } else if (parser.command_.name == "help") {
                WriteHelp(controller);
            } else if (parser.command_.name == "copyright") {
                WriteCopyright();
            } else if (parser.command_.name == "credits") {
                WriteCredits();
            } else if (parser.command_.name == "license") {
                WriteLicense();
            } else if (parser.command_.name == "show") {
                if (parser.command_.argv.size() && parser.command_.argv.front() == "w") {
                    WriteLicenceWarranty();
                } else if (parser.command_.argv.size() && parser.command_.argv.front() == "c") {
                    WriteLicenceRedistribution();
                }
            } else if (parser.command_.name == "load") {
                try {
                    ChecArgvExact(1, parser.command_.argv);
                    ProcessFile(controller, parser.command_.argv.front(), parser.relative_directory_, false);
                } catch (CommandError &e) {
                    std::cout << "CommandError: " << e.what() << std::endl;
                } catch (IncompleteCodeError &e) {
                    std::cout << "IncompleteCodeError: " << e.what() << std::endl;
                }
            } else {
                try {
                    controller.ProcessCommand(parser.command_, false);
                } catch (CommandError &e) {
                    std::cout << "CommandError: " << e.what() << std::endl;
                } catch (IncompleteCodeError &e) {
                    std::cout << "IncompleteCodeError: " << e.what() << std::endl;
                }
            }
        }
    } else if (argc == 2) {
        if (ProcessFile(controller, argv[1], "", false) == 0) {
            std::cout << "================================================================" << std::endl;
            std::cout << "EXECUTION FINISHED SUCCESSFULLY" << std::endl;
            std::cout << "================================================================" << std::endl;

            return 0;
        } else {
            std::cout << "================================================================" << std::endl;
            std::cout << "EXECUTION FINISHED WITH ERROR" << std::endl;
            std::cout << "================================================================" << std::endl;

            return 1;
        }
    } else if (argc == 3) {
        if (std::string(argv[1]) == "-t") {
            if (ProcessFile(controller, argv[2], "", true) == 0) {
                std::cout << "================================================================" << std::endl;
                std::cout << "EXECUTION FINISHED SUCCESSFULLY" << std::endl;
                std::cout << "================================================================" << std::endl;

                return 0;
            } else {
                std::cout << "================================================================" << std::endl;
                std::cout << "EXECUTION FINISHED WITH ERROR" << std::endl;
                std::cout << "================================================================" << std::endl;

                return 1;
            }
        } else {
            std::cout << "ParseError: Unknown argument [" << argv[1] << "]." << std::endl;
            return 1;
        }
    } else {
        std::cout << "ParseError: Too many arguments." << std::endl;
        return 1;
    }

    return 0;
}

void WriteHeader() {
    std::cout << "HAMT Simulation Tool VERSION (default, COMPILE_DATE, COMPILE_TIME)" << std::endl;
    std::cout << "[COMPILER] on SYSTEM" << std::endl;
    std::cout << "Type \"help\", \"copyright\", \"credits\" or \"license\" for more information." << std::endl;
}

void WriteCopyright() {
    std::cout << "Copyright (c) 2020 Leo Basov." << std::endl;
    std::cout << "All Rights Reserved." << std::endl;
}

void WriteLicense() {
    std::cout << "HAMT Simulation Tool  Copyright (C) 2020  Leo Basov" << std::endl;
    std::cout << "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'." << std::endl;
    std::cout << "This is free software, and you are welcome to redistribute it" << std::endl;
    std::cout << "under certain conditions; type `show c' for details." << std::endl;
}

void WriteLicenceWarranty() {
    std::cout << "THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY" << std::endl;
    std::cout << "APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT" << std::endl;
    std::cout << "HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY" << std::endl;
    std::cout << "OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO," << std::endl;
    std::cout << "THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR" << std::endl;
    std::cout << "PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM" << std::endl;
    std::cout << "IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF" << std::endl;
    std::cout << "ALL NECESSARY SERVICING, REPAIR OR CORRECTION." << std::endl;
}

void WriteLicenceRedistribution() { std::cout << "TODO" << std::endl; }

void WriteHelp(const Controller &controller) {
    std::cout << "The following operations are currently implemented:" << std::endl;

    for (auto op : controller.GetOperations()) {
        std::cout << op.second->GetHelp() << std::endl;
    }
}

void WriteCredits() { std::cout << "TODO" << std::endl; }

int ProcessFile(Controller &controller, const std::string &file_name, const std::string &relative_dir,
                const bool &test_mode) {
    Parser parser;

    try {
        parser.ParseFile(relative_dir + file_name);
        controller.SetRelDir(parser.relative_directory_);
    } catch (std::exception &e) {
        std::cout << "ParseError: File [" << relative_dir + file_name << "] could not be opened." << std::endl;
        return 1;
    }

    for (auto command : parser.commads_) {
        try {
            controller.ProcessCommand(command, test_mode);
        } catch (CommandError &e) {
            std::cout << "CommandError: " << e.what() << std::endl;
            return 1;
        } catch (IncompleteCodeError &e) {
            std::cout << "IncompleteCodeError: " << e.what() << std::endl;
            return 1;
        } catch (LoadPass &e) {
            if (ProcessFile(controller, e.what(), parser.relative_directory_, test_mode)) {
                return 1;
            }
        } catch (Exception &e) {
            std::cout << "Exception trhown: " << e.what() << " In: " << e.where() << std::endl;
            return 1;
        }
    }

    return 0;
}

void ChecArgvExact(const uint &size, const std::vector<std::string> &argv) {
    if (argv.size() != size) {
        throw CommandError("command 'load' must have '" + std::to_string(size) + "' argument(s)");
    }
}
