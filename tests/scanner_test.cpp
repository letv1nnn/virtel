#include "gtest/gtest.h"
#include "../include/scanner.hpp"

namespace Virtel {

std::vector<Token> get_tokens_from_source(const std::string &source) {
    Scanner scanner(source);
    return scanner.scan_tokens();
}

TEST(Scanner, scan_single_character_tokens) {
    std::string source = "()  {}\t,\r.    -\n+ ;*/";
    std::vector<Token> tokens = get_tokens_from_source(source);

    std::vector<Virtel::TokenType> actual_tokens = {
        LEFT_PAREN, RIGHT_PAREN,
        LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT,
        MINUS, PLUS,
        SEMICOLON, STAR,
        SLASH, END_OF_FILE
    };

    EXPECT_EQ(tokens.size(), actual_tokens.size());
    
    for (std::size_t i{}; i < tokens.size(); ++i)
        EXPECT_EQ(tokens[i].get_token(), actual_tokens[i]);
}

TEST(Scanner, scan_two_characters_tokens) {
    std::string source = "!\n  !=\r\r=  == \t> >= < \t\t\n\n<=";
    std::vector<Token> tokens = get_tokens_from_source(source);

    std::vector<TokenType> actual_tokens = {
        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,
        END_OF_FILE
    };    

    EXPECT_EQ(tokens.size(), actual_tokens.size());
    
    for (std::size_t i{}; i < tokens.size(); ++i)
        EXPECT_EQ(tokens[i].get_token(), actual_tokens[i]);
}

TEST(Scanner, scan_literal_tokens) {
    std::string source = "identifier\t\n    \"some string\" 12345.67890";
    std::vector<Token> tokens = get_tokens_from_source(source);

    std::vector<TokenType> actual_tokens = {
        IDENTIFIER, STRING, NUMBER,
        END_OF_FILE
    };    
    
    EXPECT_EQ(tokens.size(), actual_tokens.size());
    
    for (std::size_t i{}; i < tokens.size(); ++i)
        EXPECT_EQ(tokens[i].get_token(), actual_tokens[i]);
}

TEST(Scanner, scan_keywords_tokens) {
    std::string source = "and\n  class else \t\tfalse for fun if\t\t nil or\n\n print\t\t\n\r\t return super this true var while\r\r";
    std::vector<Token> tokens = get_tokens_from_source(source);

    std::vector<TokenType> actual_tokens = {
        AND, CLASS, ELSE, FALSE, FOR, FUN,
        IF, NIL, OR, PRINT, RETURN, SUPER,
        THIS, TRUE, VAR, WHILE,
        END_OF_FILE
    };
    
    EXPECT_EQ(tokens.size(), actual_tokens.size());
    
    for (std::size_t i{}; i < tokens.size(); ++i)
        EXPECT_EQ(tokens[i].get_token(), actual_tokens[i]);
}

TEST(Scanner, scan_single_line_comments) {
    std::string source = "123 // + - ;";
    std::vector<Token> tokens = get_tokens_from_source(source);
    
    std::vector<TokenType> actual_tokens = {
        NUMBER, END_OF_FILE
    };

    EXPECT_EQ(tokens.size(), actual_tokens.size());
    
    for (std::size_t i{}; i < tokens.size(); ++i)
        EXPECT_EQ(tokens[i].get_token(), actual_tokens[i]);
}

TEST(Scanner, scan_multiple_lines_comments) {
    std::string source = "\"hello\" /* + - ; \n*/";
    std::vector<Token> tokens = get_tokens_from_source(source);
    
    std::vector<TokenType> actual_tokens = {
        STRING, END_OF_FILE
    };

    EXPECT_EQ(tokens.size(), actual_tokens.size());
    
    for (std::size_t i{}; i < tokens.size(); ++i)
        EXPECT_EQ(tokens[i].get_token(), actual_tokens[i]);
}

}
