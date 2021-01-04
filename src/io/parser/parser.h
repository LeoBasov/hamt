#pragma once

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

namespace hamt {
struct Command {
    std::string name;
    std::vector<std::string> argv;

    void Clear() {
        name = "";
        argv.clear();
    }
};

class Parser {
   public:
    Parser();
    ~Parser() = default;

    void ParseShell();
    void ParseFile(const std::string& file_name);
    void GetRelDirectory(const std::string& file_name);

    Command command_;
    std::vector<Command> commads_;
    std::string relative_directory_;
};
}  // namespace hamt
