#include "../include/token.hpp"
#include <any>
#include <string>

namespace Virtel {

Token::Token(TokenType type, std::string lexeme, std::any literal, std::uint64_t line)
    : type_(type), lexeme_(lexeme), literal_(literal), line_(line) {}

Token::Token(TokenType type, std::string lexeme, std::uint64_t line)
    : Token::Token(type, lexeme, std::any{}, line) {}

std::string Token::to_string() const {
    return std::to_string(static_cast<int>(type_)) + ", lexeme: '" + lexeme_ + "', literal: '" + literal_to_string() + "'";
}

std::string Token::literal_to_string() const {
    switch (type_) {
        case TokenType::STRING:
            return std::any_cast<std::string>(literal_);
        case TokenType::NUMBER:
            return std::to_string(std::any_cast<double>(literal_));
        default:
            return "";
    }
}

}

