
#include "lexer.hpp"
#include <cassert>
#include <iostream>


int main() {

    Lexer lexer("int x = 42;");

    Token token = lexer.nextToken();
    assert(token.type == TokenType::KW_INT);
    assert(token.lexeme == "int");

    token = lexer.nextToken();
    assert(token.type == TokenType::IDENTIFIER);
    assert(token.lexeme == "x");

    token = lexer.nextToken();
    assert(token.type == TokenType::ASSIGN);

    token = lexer.nextToken();
    assert(token.type == TokenType::INTEGER_LITERAL);
    assert(token.lexeme == "42");

    token = lexer.nextToken();
    assert(token.type == TokenType::SEMICOLON);

    token = lexer.nextToken();
    assert(token.type == TokenType::END_OF_FILE);


    Lexer operatorsLexer("= == ! != < <= > >= + ++ - -- & && | ||");

    Token expectedOperators[] = {
        
        {TokenType::ASSIGN, "=", 1, 1},
        {TokenType::EQUAL_EQUAL, "==", 1, 3},
        {TokenType::LOGICAL_NOT, "!", 1, 6},
        {TokenType::NOT_EQUAL, "!=", 1, 8},
        {TokenType::LESS, "<", 1, 11},
        {TokenType::LESS_EQUAL, "<=", 1, 13},
        {TokenType::GREATER, ">", 1, 16},
        {TokenType::GREATER_EQUAL, ">=", 1, 18},
        {TokenType::PLUS, "+", 1, 21},
        {TokenType::INCREMENT, "++", 1, 23},
        {TokenType::MINUS, "-", 1, 26},
        {TokenType::DECREMENT, "--", 1, 28},
        {TokenType::INVALID, "&", 1, 31},
        {TokenType::LOGICAL_AND, "&&", 1, 33},
        {TokenType::INVALID, "|", 1, 36},
        {TokenType::LOGICAL_OR, "||", 1, 38},
    };

    for (const Token& expected: expectedOperators) {

        Token actual = operatorsLexer.nextToken();

        assert(actual.type == expected.type);
        assert(actual.lexeme == expected.lexeme);
        assert(actual.line == expected.line);
        assert(actual.column == expected.column);

    }

    assert(operatorsLexer.nextToken().type == TokenType::END_OF_FILE);


    Lexer KeywordsLexer("int integer if ifx return returnValue true false");

    TokenType expectedTypes[] = {

        TokenType::KW_INT,
        TokenType::IDENTIFIER,
        TokenType::KW_IF,
        TokenType::IDENTIFIER,
        TokenType::KW_RETURN,
        TokenType::IDENTIFIER,
        TokenType::BOOLEAN_LITERAL,
        TokenType::BOOLEAN_LITERAL

    };

    const char* expectedLexemes[] = {

        "int", "integer", "if", "ifx","return", "returnValue", "true", "false"

    };

    for (int i = 0; i < 8; ++i) {

        Token token = KeywordsLexer.nextToken();

        assert(token.type == expectedTypes[i]);
        assert(token.lexeme == expectedLexemes[i]);

    }

    assert(KeywordsLexer.nextToken().type == TokenType::END_OF_FILE);


    Lexer numbersLexer("123 0 3.14 0.5 42.0");

    TokenType expectedNumberTypes[] = {

        TokenType::INTEGER_LITERAL,
        TokenType::INTEGER_LITERAL,
        TokenType::FLOAT_LITERAL,
        TokenType::FLOAT_LITERAL,
        TokenType::FLOAT_LITERAL

    };

    const char* expectedNumberLexemes[] = {

        "123", "0", "3.14", "0.5", "42.0"

    };
    
    for (int i = 0; i < 5; ++i) {

        Token token = numbersLexer.nextToken();

        assert(token.type == expectedNumberTypes[i]);
        assert(token.lexeme == expectedNumberLexemes[i]);

    }

    assert(numbersLexer.nextToken().type == TokenType::END_OF_FILE);


    Lexer positionLexer("int x;\n  return 42;\nfloat y;");

    Token expectedTokens[] = {

        {TokenType::KW_INT, "int", 1, 1},
        {TokenType::IDENTIFIER, "x", 1, 5},
        {TokenType::SEMICOLON, ";", 1, 6},

        {TokenType::KW_RETURN, "return", 2, 3},
        {TokenType::INTEGER_LITERAL, "42", 2, 10},
        {TokenType::SEMICOLON, ";", 2, 12},

        {TokenType::KW_FLOAT, "float", 3, 1},
        {TokenType::IDENTIFIER, "y", 3, 7},
        {TokenType::SEMICOLON, ";", 3, 8}

    };

    for (const Token& expected: expectedTokens) {

        Token actual = positionLexer.nextToken();

        assert(actual.type == expected.type);
        assert(actual.lexeme == expected.lexeme);
        assert(actual.line == expected.line);
        assert(actual.column == expected.column);

    }

    assert(positionLexer.nextToken().type == TokenType::END_OF_FILE);




    std::cout << "All lexer tests passed!\n";
    return 0;
}