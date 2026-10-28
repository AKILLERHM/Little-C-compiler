
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



    Lexer keywordsLexer("int integer if ifx return returnValue true false");

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

        Token token = keywordsLexer.nextToken();

        assert(token.type == expectedTypes[i]);
        assert(token.lexeme == expectedLexemes[i]);

    }

    assert(keywordsLexer.nextToken().type == TokenType::END_OF_FILE);



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



    Lexer commentLexer("int x; // this is a comment\n"
                       "/* multi-line\n"
                       "   comment */ return 42;");

    Token expectedComments[] = {

        {TokenType::KW_INT, "int", 1, 1},
        {TokenType::IDENTIFIER, "x", 1, 5},
        {TokenType::SEMICOLON, ";", 1, 6},

        {TokenType::KW_RETURN, "return", 3, 15},
        {TokenType::INTEGER_LITERAL, "42", 3, 22},
        {TokenType::SEMICOLON, ";", 3, 24},

    };

    for (const Token& expected: expectedComments) {

        Token actual = commentLexer.nextToken();

        assert(actual.type == expected.type);
        assert(actual.lexeme == expected.lexeme);
        assert(actual.line == expected.line);
        assert(actual.column == expected.column);

    }

    assert(commentLexer.nextToken().type == TokenType::END_OF_FILE);



    Lexer tabsLexer("\tint\tx;");

    Token tabInt = tabsLexer.nextToken();
    assert(tabInt.type == TokenType::KW_INT);
    assert(tabInt.lexeme == "int");
    assert(tabInt.column == 2);

    Token tabX = tabsLexer.nextToken();
    assert(tabX.type == TokenType::IDENTIFIER);
    assert(tabX.lexeme == "x");
    assert(tabX.column == 6);

    Token tabSemicolon = tabsLexer.nextToken();
    assert(tabSemicolon.type == TokenType::SEMICOLON);
    assert(tabSemicolon.column == 7);

    assert(tabsLexer.nextToken().type == TokenType::END_OF_FILE);


    Lexer unterminatedCommentLexer("int x; /* never closed");

    Token first = unterminatedCommentLexer.nextToken();
    assert(first.type == TokenType::KW_INT);

    Token second = unterminatedCommentLexer.nextToken();
    assert(second.type == TokenType::IDENTIFIER);

    Token third = unterminatedCommentLexer.nextToken();
    assert(third.type == TokenType::SEMICOLON);

    Token error = unterminatedCommentLexer.nextToken();
    assert(error.type == TokenType::INVALID);
    assert(error.lexeme == "UNTERMINATED_COMMENT");



    Lexer invalidStringLexer("\"hello");
    Token stringError = invalidStringLexer.nextToken();

    assert(stringError.type == TokenType::INVALID);
    assert(stringError.lexeme == "UNTERMINATED_STRING");



    Lexer invalidCharLexer("'A");
    Token charError = invalidCharLexer.nextToken();

    assert(charError.type == TokenType::INVALID);
    assert(charError.lexeme == "INVALID_CHAR_LITERAL");



    Lexer boundaryLexer("123abc");

    Token first1 = boundaryLexer.nextToken();
    Token second2 = boundaryLexer.nextToken();

    assert(first1.type == TokenType::INTEGER_LITERAL);
    assert(first1.lexeme == "123");

    assert(second2.type == TokenType::IDENTIFIER);
    assert(second2.lexeme == "abc");

    assert(boundaryLexer.nextToken().type == TokenType::END_OF_FILE);



    Lexer boundaryNumbersLexer("42. 1.2.3");

    Token n1 = boundaryNumbersLexer.nextToken();
    assert(n1.type == TokenType::INTEGER_LITERAL);
    assert(n1.lexeme == "42");

    Token n2 = boundaryNumbersLexer.nextToken();
    assert(n2.type == TokenType::INVALID);
    assert(n2.lexeme ==".");

    Token n3 = boundaryNumbersLexer.nextToken();
    assert(n3.type == TokenType::FLOAT_LITERAL);
    assert(n3.lexeme == "1.2");

    Token n4 = boundaryNumbersLexer.nextToken();
    assert(n4.type == TokenType::INVALID);
    assert(n4.lexeme == ".");

    Token n5 = boundaryNumbersLexer.nextToken();
    assert(n5.type == TokenType::INTEGER_LITERAL);
    assert(n5.lexeme == "3");

    assert(boundaryNumbersLexer.nextToken().type == TokenType::END_OF_FILE);



    Lexer invalidOperatorsLexer("& | @");

    Token op1 = invalidOperatorsLexer.nextToken();
    assert(op1.type == TokenType::INVALID);
    assert(op1.lexeme == "&");

    Token op2 = invalidOperatorsLexer.nextToken();
    assert(op2.type == TokenType::INVALID);
    assert(op2.lexeme =="|");

    Token op3 = invalidOperatorsLexer.nextToken();
    assert(op3.type == TokenType::INVALID);
    assert(op3.lexeme == "@");

    assert(invalidOperatorsLexer.nextToken().type == TokenType::END_OF_FILE);



    Lexer recoverLexer("@ int x;");

    Token r1 = recoverLexer.nextToken();
    assert(r1.type == TokenType::INVALID);
    assert(r1.lexeme == "@");

    Token r2 = recoverLexer.nextToken();
    assert(r2.type == TokenType::KW_INT);
    assert(r2.lexeme == "int");

    Token r3 = recoverLexer.nextToken();
    assert(r3.type == TokenType::IDENTIFIER);
    assert(r3.lexeme == "x");

    Token r4 = recoverLexer.nextToken();
    assert(r4.type == TokenType::SEMICOLON);
    assert(r4.lexeme == ";");

    assert(recoverLexer.nextToken().type == TokenType::END_OF_FILE);



    // empty input |  ورودی خالی
    Lexer emptyLexer("");

    Token emptyToken = emptyLexer.nextToken();
    assert(emptyToken.type == TokenType::END_OF_FILE);

    //whitespace-only input |  ورودی با تنها اسپییس ها
    Lexer whitespaceLexer("   \t\n  \r");

    Token whitespaceToken = whitespaceLexer.nextToken();
    assert(whitespaceToken.type == TokenType::END_OF_FILE);

    // comment-only input | ورودی تنها کامنت
    Lexer commentOnlyLexer("// just a comment\n"
                           "/* another comment */");

    Token commenttoken = commentOnlyLexer.nextToken();
    assert(commenttoken.type == TokenType::END_OF_FILE);

    



    std::cout << "All lexer tests passed!\n" << std::endl;
    return 0;
}