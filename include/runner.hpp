#pragma once

#include <fstream>
#include "common.hpp"

class Runner {
public:
    static bool had_error;
    
public: // runners
    static void run_file(const char *path);
    static void run_repl();
    static void run_source(const std::string &source);

public: // Error handling
    static void error(std::size_t line, const char *message);

private:
    static void report(std::size_t line, const char *where, const char *message);
};

