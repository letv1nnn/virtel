#include "../include/runner.hpp"

int main(int argc, char **argv) {
    if (argc > 2) {
        std::cout << "Usage: virtel [script]" << std::endl;
        return 0;
    } else if (argc == 2) {
        Virtel::Runner::run_file(argv[1]);
    } else {
        Virtel::Runner::run_repl();
    }
    return 0;
}

