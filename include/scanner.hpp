#pragma once

#include "token.hpp"
#include <vector>

namespace Virtel {

class Scanner {
private:
    std::string source_;
    std::vector<Token> tokens_;
    // start (first char of lexem), current (current char)
    std::uint64_t start_{}, current_{}, line_{1};
public:
    Scanner(std::string source);

    std::vector<Token> scan_tokens();

private:
    /* helper functions */
    bool is_at_end() const;
    
    char advance();
    void add_token(TokenType type);
    void add_token(TokenType type, std::any literal);
    void scan_token();
};

}
