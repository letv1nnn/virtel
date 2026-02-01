#include "../include/runner.hpp"
#include <cstdlib>

bool Runner::had_error{};

void Runner::run_file(const char *path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "ERROR: Could not open file!" << std::endl;
        std::exit(1);
    }

    std::string source;
    while (file >> source)
        std::cout << source << std::endl;

    run_source(source);

    if (Runner::had_error)
        std::exit(65);

    file.close();
}

void Runner::run_repl() {
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

void Runner::error(int line, const char *message) {
    report(line, "", message);
}

void Runner::report(int line, const char *where, const char *message) {
    std::printf("[line %d] ERROR %s: %s", line, where, message); 
}

