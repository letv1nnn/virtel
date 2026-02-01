#pragma once

#include "token.hpp"
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdlib>

namespace Virtel {

class Scanner {
private:
    std::string source_;
    std::vector<Token> tokens_;
    std::uint64_t start_{}, current_{}, line_{1};
    
public:
    static const std::unordered_map<std::string, TokenType> keywords_;

public:
    Scanner(std::string source);

    std::vector<Token> scan_tokens();

private:
    /* helper functions */
    bool is_at_end() const;
    char peek() const;
    char peek_next() const;
    bool is_alpha(char c) const;
    bool is_alpha_numeric(char c) const;

    char advance();
    void add_token(TokenType type);
    void add_token(TokenType type, std::any literal);
    bool match(char expected);
    
    void string();
    void number();
    void identifier();

    void scan_token();
};

}
