#pragma once

#include "../include/common.hpp"
#include <fstream>

class Runner {
public:
    static bool had_error;
    
public: // runners
    static void run_file(const char *path);
    static void run_repl();
    static void run_source(const std::string &source);

public: // Error handling
    static void error(int line, const char *message);

private:
    static void report(int line, const char *where, const char *message);
};

