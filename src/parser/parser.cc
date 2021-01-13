#include "parser.h"

namespace hamt {

Parser::Parser() {}

void Parser::ParseShell() {
    std::string str;
    std::getline(std::cin, str);
    std::istringstream iss(str);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    command_.Clear();

    for (uint i = 0; i < results.size(); i++) {
        if (i == 0) {
            if (results.at(i).front() == std::string("#").front()) {
                command_.Clear();
                break;
            }

            command_.name = results.at(i);
        } else {
            if (results.at(i).front() == std::string("#").front()) {
                break;
            }

            command_.argv.push_back(results.at(i));
        }
    }
}

void Parser::ParseFile(const std::string& file_name) {
    std::ifstream infile(file_name);
    std::string line;

    commads_.clear();

    if (!infile.is_open()) {
        throw std::exception();
    }

    while (std::getline(infile, line)) {
        Command command;
        std::istringstream iss(line);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                         std::istream_iterator<std::string>());

        for (uint i = 0; i < results.size(); i++) {
            if (i == 0) {
                if (results.at(i).front() == std::string("#").front()) {
                    command_.Clear();
                    break;
                }

                command.name = results.at(i);
            } else {
                if (results.at(i).front() == std::string("#").front()) {
                    break;
                }

                command.argv.push_back(results.at(i));
            }
        }

        if (!command.name.empty()) {
            commads_.push_back(command);
        }
    }

    GetRelDirectory(file_name);
}

void Parser::GetRelDirectory(const std::string& file_name) {
    std::stringstream outstream;
    std::string::size_type pos_old = 0;
    std::string::size_type pos = file_name.find('/');

    while (pos != std::string::npos) {
        std::string substr;

        substr = file_name.substr(pos_old, (pos - pos_old));
        substr += "/";
        outstream << substr;

        pos_old = pos + 1;
        pos = file_name.find('/', pos + 1);
    }

    relative_directory_ = outstream.str();
}

}  // namespace hamt
