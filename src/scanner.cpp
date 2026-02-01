#include "../include/scanner.hpp"
#include "../include/runner.hpp"

namespace Virtel {

const std::unordered_map<std::string, TokenType> Scanner::keywords_ = {
    {"and",     AND},
    {"class",   CLASS},
    {"else",    ELSE},
    {"false",   FALSE},
    {"for",     FOR},
    {"fun",     FUN},
    {"if",      IF},
    {"nil",     NIL},
    {"or",      OR},
    {"print",   PRINT},
    {"return", RETURN},
    {"super",  SUPER},
    {"this",   THIS},
    {"true",   TRUE},
    {"var",    VAR},
    {"while",  WHILE},
};

Scanner::Scanner(std::string source)
    : source_(std::move(source)) {}

std::vector<Token> Scanner::scan_tokens() {
    while (!is_at_end()) {
        start_ = current_;
        scan_token();
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

bool Scanner::match(char expected) {
    if (is_at_end() || source_[current_] != expected) return 0;
    current_++;
    return 1;
}

char Scanner::peek() const {
    if (is_at_end()) return '\0';
    return source_[current_];
}

char Scanner::peek_next() const {
    if (current_ + 1 >= source_.size()) return '\0';
    return source_[current_ + 1];
}

bool Scanner::is_alpha(char c) const {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Scanner::is_alpha_numeric(char c) const {
    return is_alpha(c) || std::isdigit(c);
}

void Scanner::string() {
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') line_++;
        advance();
    }

    if (is_at_end()) {
        Runner::error(line_, "Unterminated string.");
        return;
    }

    advance();
    std::string value = source_.substr(start_ + 1, current_ - 1);
    add_token(STRING, value);
}

void Scanner::number() {
    while (std::isdigit(peek())) advance();

    if (peek() == '.' && std::isdigit(peek_next())) {
        advance();
        while (std::isdigit(peek())) advance();
    }
    
    double value = std::stod(source_.substr(start_, current_));

    add_token(NUMBER, value);
}

void Scanner::identifier() {
    while (is_alpha_numeric(peek())) advance();
    
    std::string text = source_.substr(start_, current_);
    TokenType type = IDENTIFIER;
    if (keywords_.count(text)) {
        type = keywords_.at(text);
    }

    add_token(type);
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
        case '!':
            add_token(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            add_token(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            add_token(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            add_token(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !is_at_end()) advance();
            } else if (match('*')) {
                while (!is_at_end()) {
                    if (peek() == '\n') line_++;
                    if (peek() == '*' && peek_next() == '/') {
                        advance(); advance();
                        break;
                    }
                    advance();
                }
                if (is_at_end()) {
                    Runner::error(line_, "comments are not closed");
                }
            } else {
                add_token(SLASH);
            }
            break;
        case ' ': case '\r': case '\t':
            break;
        case '\n':
            line_++;
            break;
        case '"': string(); break;
        default:
            if (std::isdigit(c)) {
                number();
            } else if (std::isalpha(c)) {
                identifier(); 
            } else {
                Runner::error(line_, "Unexpected character.");
            }
            break;
    }
}

}

