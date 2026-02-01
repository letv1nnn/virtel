#include "../include/scanner.hpp"
#include "../include/runner.hpp"

namespace Virtel {

Scanner::Scanner(std::string source)
    : source_(std::move(source)) {}

std::vector<Token> Scanner::scan_tokens() {
    while (!is_at_end()) {
        // we are at the beginning of the next lexeme
        start_ = current_;
        // scan_token();
    }

    tokens_.emplace_back(TokenType::END_OF_FILE, "", line_);
    return tokens_;
}

bool Scanner::is_at_end() const {
    return current_ >= source_.size();
}

char Scanner::advance() {
    return source_[current_++];
}

void Scanner::add_token(TokenType type) {
    tokens_.emplace_back(type, source_.substr(start_, current_ - start_), line_);
}

void Scanner::add_token(TokenType type, std::any literal) {
    tokens_.emplace_back(type, source_.substr(start_, current_ - start_), literal, line_);
}

void Scanner::scan_token() {
    char c = advance();
    switch (c) {
        case '(': add_token(LEFT_PAREN); break;
        case ')': add_token(RIGHT_PAREN); break;
        case '{': add_token(LEFT_BRACE); break;
        case '}': add_token(RIGHT_BRACE); break;
        case ',': add_token(COMMA); break;
        case '.': add_token(DOT); break;
        case '-': add_token(MINUS); break;
        case '+': add_token(PLUS); break;
        case ';': add_token(SEMICOLON); break;
        case '*': add_token(STAR); break;
        default:
            Runner::error(line_, "Unexpected character.");
            break;
    }
}

}

