#pragma once

#include "common.hpp"
#include <any>
#include <cstdint>

namespace Virtel {
enum TokenType {
    /* single-character tokens. */
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    /* one or two character tokens */
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    /* literals */
    IDENTIFIER, STRING, NUMBER,

    /* keywords */
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    END_OF_FILE,
};

class Token {
private:
    TokenType type_;
    std::string lexeme_;
    std::any literal_;
    std::uint64_t line_;
public:
    Token(TokenType type, std::string lexeme, std::uint64_t line);
    Token(TokenType type, std::string lexeme, std::any literal, std::uint64_t line);

    TokenType get_token() const { return type_; }
    std::string get_lexeme() const { return lexeme_; }
    std::any get_literal() const { return literal_; }
    std::uint64_t get_line() const { return line_; }

    std::string to_string() const;
    std::string literal_to_string() const;
};
}
