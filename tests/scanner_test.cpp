#include "gtest/gtest.h"
#include "../include/scanner.hpp"

using namespace Virtel;

namespace {

std::vector<Token> get_tokens_from_source(const std::string &source) {
    Scanner scanner(source);
    return scanner.scan_tokens();
}

void same_tokens(const std::vector<Token> &actual, const std::vector<Token> &expected) {
    std::size_t acc_size{actual.size()}, exp_size{expected.size()};
    EXPECT_EQ(acc_size, exp_size)
        << "The size of actual array of tokens differs from the size of expected (" << acc_size << " != " << exp_size << ")";

    for (std::size_t i{}; i < acc_size; ++i) {
        EXPECT_EQ(actual[i].get_type(), expected[i].get_type())
            << "Different token types (" << actual[i].get_type() << ", " << expected[i].get_type() << ", iteration " << i << ")";
        EXPECT_EQ(actual[i].get_lexeme(), expected[i].get_lexeme())
            << "Different token lexeme (" << actual[i].get_lexeme() << ", " << expected[i].get_lexeme() << ", iteration " << i << ")";
        EXPECT_EQ(actual[i].get_line(), expected[i].get_line())
            << "Different token lines (" << actual[i].get_line() << ", " << expected[i].get_line() << ", iteration " << i << ")";
        EXPECT_TRUE(actual[i].same_literals(expected[i].get_type(), expected[i].get_literal()))
            << "Different token literals (iteration " << i << ")";
    }
}

TEST(Scanner, scan_single_character_tokens) {
    std::string source = "()  {}\t,\r.    -\n+ ;*/";
    
    std::vector<Token> actual = ::get_tokens_from_source(source);
    std::vector<Token> expected = {
        Token{TokenType::LEFT_PAREN, "(", 1},
        Token{TokenType::RIGHT_PAREN, ")", 1},
        Token{TokenType::LEFT_BRACE, "{", 1},
        Token{TokenType::RIGHT_BRACE, "}", 1},
        Token{TokenType::COMMA, ",", 1},
        Token{TokenType::DOT, ".", 1},
        Token{TokenType::MINUS, "-", 1},
        Token{TokenType::PLUS, "+", 2},
        Token{TokenType::SEMICOLON, ";", 2},
        Token{TokenType::STAR, "*", 2},
        Token{TokenType::SLASH, "/", 2},
        Token{TokenType::END_OF_FILE, "", 2},
    };
    
    ::same_tokens(actual, expected);
}

TEST(Scanner, scan_two_characters_tokens) {
    std::string source = "!\n  !=\r\r=  == \t> >= < \t\t\n\n<=";

    std::vector<Token> actual = ::get_tokens_from_source(source);
    std::vector<Token> expected = {
        Token{TokenType::BANG, "!", 1},
        Token{TokenType::BANG_EQUAL, "!=", 2},
        Token{TokenType::EQUAL, "=", 2},
        Token{TokenType::EQUAL_EQUAL, "==", 2},
        Token{TokenType::GREATER, ">", 2},
        Token{TokenType::GREATER_EQUAL, ">=", 2},
        Token{TokenType::LESS, "<", 2},
        Token{TokenType::LESS_EQUAL, "<=", 4},
        Token{TokenType::END_OF_FILE, "", 4},
    };    

    ::same_tokens(actual, expected);
}

TEST(Scanner, scan_literal_tokens) {
    std::string source = "identifier\t\n    \"some string\" 12.34";

    std::vector<Token> actual = ::get_tokens_from_source(source);
    std::vector<Token> expected = {
        Token{TokenType::IDENTIFIER, "identifier", 1},
        Token{TokenType::STRING, "\"some string\"", std::string{"some string"}, 2},
        Token{TokenType::NUMBER, "12.34", 12.34, 2},
        Token{TokenType::END_OF_FILE, "", 2},
    };

    ::same_tokens(actual, expected);
}

TEST(Scanner, scan_keywords_tokens) {
    std::string source = "and\n  class else \t\tfalse for fun if\t\t nil or\n\n print\t\t\n\r\t return super this true var while\r\r";
    
    std::vector<Token> actual = ::get_tokens_from_source(source);
    std::vector<Token> expected = {
        Token{TokenType::AND, "and", 1},
        Token{TokenType::CLASS, "class", 2},
        Token{TokenType::ELSE, "else", 2},
        Token{TokenType::FALSE, "false", 2},
        Token{TokenType::FOR, "for", 2},
        Token{TokenType::FUN, "fun", 2},
        Token{TokenType::IF, "if", 2},
        Token{TokenType::NIL, "nil", 2},
        Token{TokenType::OR, "or", 2},
        Token{TokenType::PRINT, "print", 4},
        Token{TokenType::RETURN, "return", 5},
        Token{TokenType::SUPER, "super", 5},
        Token{TokenType::THIS, "this", 5},
        Token{TokenType::TRUE, "true", 5},
        Token{TokenType::VAR, "var", 5},
        Token{TokenType::WHILE, "while", 5},
        Token{TokenType::END_OF_FILE, "", 5},
    };
    
    ::same_tokens(actual, expected);
}

TEST(Scanner, scan_single_line_comments) {
    std::string source = "123 // + - ;";

    std::vector<Token> actual = ::get_tokens_from_source(source);
    std::vector<Token> expected = {
        Token{TokenType::NUMBER, "123", 123.0, 1},
        Token{TokenType::END_OF_FILE, "", 1},
    };    

    ::same_tokens(actual, expected);
}

TEST(Scanner, scan_multiple_lines_comments) {
    std::string source = "\"hello\" /* + - ; \n*/";

    std::vector<Token> actual = ::get_tokens_from_source(source);
    std::vector<Token> expected = {
        Token{TokenType::STRING, "\"hello\"", std::string{"hello"}, 1},
        Token{TokenType::END_OF_FILE, "", 2},
    };

    ::same_tokens(actual, expected);
}

TEST(Scanner, scan_expression) {
    std::string source = "var num = 123;\n";

    std::vector<Token> actual = ::get_tokens_from_source(source);
    std::vector<Token> expected = {
        Token{TokenType::VAR, "var", 1},
        Token{TokenType::IDENTIFIER, "num", 1},
        Token{TokenType::EQUAL, "=", 1},
        Token{TokenType::NUMBER, "123", 123.0, 1},
        Token{TokenType::SEMICOLON, ";", 1},
        Token{TokenType::END_OF_FILE, "", 2},
    };

    ::same_tokens(actual, expected);
}

}
