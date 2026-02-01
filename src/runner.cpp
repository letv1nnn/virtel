#include "../include/runner.hpp"

namespace Virtel {

bool Runner::had_error{};

void Runner::run_file(const char *path) {
    std::ifstream file{path};
    if (!file) {
        std::cerr << "ERROR: Could not open file!" << std::endl;
        return;
    }

    std::string source, line;
    while (std::getline(file, line)) {
        source += line + '\n';
    }

    run_source(source);

    if (Runner::had_error)
        std::exit(2);

    file.close();
}

void Runner::run_repl() {
    std::cout << "virtel version: " << VIRTEL_VERSION << std::endl;

    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
#ifdef DEBUG
        std::cout << line << '\n';
#endif
        run_source(line);
        Runner::had_error = 0;
    }
}

void Runner::run_source(const std::string &source) {

}

void Runner::error(std::uint64_t line, const char *message) {
    report(line, "", message);
}

void Runner::report(std::uint64_t line, const char *where, const char *message) {
    std::printf("[line %ld] ERROR %s: %s", line, where, message); 
}

}
