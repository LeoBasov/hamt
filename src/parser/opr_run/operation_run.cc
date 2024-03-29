#include "operation_run.h"

namespace hamt {

OperationRun::OperationRun() : Operation("run") {}

void OperationRun::Execute(const std::vector<std::string>& argv, const bool&) {
    ChecArgvMax(1, argv);
    uint number_iterations(1);
    Timer writer_timer, total_timer, solver_timer;
    double rel_error;

    if (argv.size()) {
        number_iterations = std::stoi(argv.at(0));
    }

    std::cout << "RUN STARTED" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    for (uint i = 0; i < number_iterations; i++) {
        total_timer.Start();

        solver_timer.Start();
        rel_error = hamt_->solver_.Execute();
        solver_timer.Stop();

        writer_timer.Start();
        hamt_->writer_.Write(i);
        writer_timer.Stop();

        total_timer.Stop();

        std::cout << "Relative error: " << rel_error << std::endl;
        std::cout << "Solver time: " << solver_timer.GetCurrentDuration() << " s" << std::endl;
        std::cout << "Writer time: " << writer_timer.GetCurrentDuration() << " s" << std::endl;
        std::cout << "Total time: " << total_timer.GetCurrentDuration() << " s" << std::endl;
        std::cout << "Iteration " << i + 1 << "/" << number_iterations << " complete." << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
    }

    std::cout << "RUN COMPLETE" << std::endl;
    std::cout << "Total Solver time: " << solver_timer.GetTotalDuration() << " s" << std::endl;
    std::cout << "Total Writer time: " << writer_timer.GetTotalDuration() << " s" << std::endl;
    std::cout << "Total time: " << total_timer.GetTotalDuration() << " s" << std::endl;
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
