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
#include "io/parser/parser.h"

using namespace hamt;

void WriteHeader(), WriteCopyright(), WriteLicense(), WriteLicenceWarranty(), WriteLicenceRedistribution(),
    WriteCredits();

int main(int argc, char **) {
    bool run(true);
    Parser parser;

    WriteHeader();

    if (argc == 1) {
        while (run) {
            std::cout << ">>> ";
            parser.ParseShell();

            if (parser.command_.name == "quit") {
                run = false;
            } else if (parser.command_.name == "help") {
                std::cout << "IncompleteCodeError: WriteHelp(controller);" << std::endl;
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
                } else {
                    std::cout << "Unknown command: show";

                    for (auto command : parser.command_.argv) {
                        std::cout << " " << command;
                    }

                    std::cout << std::endl;
                }
            } else if (parser.command_.name == "load") {
                std::cout << "IncompleteCodeError: load" << std::endl;
            } else {
                std::cout << "IncompleteCodeError: else" << std::endl;
            }
        }
    } else if (argc == 2) {
        throw IncompleteCodeError("simulation run");
    } else if (argc == 3) {
        throw IncompleteCodeError("simulation run -t");
    } else {
        std::cout << "ParseError: Too many arguments." << std::endl;
        return 1;
    }
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

void WriteCredits() { std::cout << "TODO" << std::endl; }
