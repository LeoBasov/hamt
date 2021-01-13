#include "operation_run.h"

namespace hamt {

OperationRun::OperationRun() : Operation("run") {}

void OperationRun::Execute(const std::vector<std::string>& argv, const bool&) {
    ChecArgvMax(1, argv);
    uint number_iterations(1);
    Timer writer_timer_, total_;

    if (argv.size()) {
        if (std::stoi(argv.at(0)) > 0) {
            throw IncompleteCodeError(__PRETTY_FUNCTION__);
        } else {
            number_iterations = std::stoi(argv.at(0));
            throw CommandError("command 'run' Nr iter must be > 0", __PRETTY_FUNCTION__);
        }
    }

    std::cout << "RUN STARTED" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    for (uint i = 0; i < number_iterations; i++) {
        total_.Start();

        writer_timer_.Start();
        hamt_->writer_.Write(i);
        writer_timer_.Stop();

        total_.Stop();

        std::cout << "Writer time: " << writer_timer_.GetCurrentDuration() << " s" << std::endl;
        std::cout << "Total time: " << total_.GetCurrentDuration() << " s" << std::endl;
        std::cout << "Iteration " << i + 1 << "/" << number_iterations << " complete." << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
    }

    std::cout << "RUN COMPLETE" << std::endl;
    std::cout << "Total Writer time: " << writer_timer_.GetTotalDuration() << " s" << std::endl;
    std::cout << "Total time: " << total_.GetTotalDuration() << " s" << std::endl;
    std::cout << "================================================================" << std::endl;
}

void OperationRun::Check(const std::vector<std::string>& argv) { ChecArgvMax(1, argv); }

std::string OperationRun::GetHelp() const {
    const std::string tab("    ");
    std::stringstream ss;

    ss << tab << name_ << " <object> <id> <value, ...> :" << tab;
    ss << "Executes simulaton." << std::endl;

    for (auto bin : sub_operations_) {
        ss << tab << tab << tab << tab << "- " << bin.first << std::endl;
    }

    return ss.str();
}

}  // namespace hamt
