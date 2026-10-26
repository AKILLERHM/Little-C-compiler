#include <iostream>
#include "lexer.hpp"



const char* tokenTypeName(TokenType type) {

    switch (type) {
        case TokenType::KW_INT: return "KW_INT";
        case TokenType::KW_CHAR: return "KW_CHAR";
        case TokenType::KW_FLOAT: return "KW_FLOAT";
        case TokenType::KW_DOUBLE: return "KW_DOUBLE";
        case TokenType::KW_BOOL: return "KW_BOOL";
        case TokenType::KW_VOID: return "KW_VOID";
        case TokenType::KW_IF: return "KW_IF";
        case TokenType::KW_RETURN: return "KW_RETURN";

        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::INTEGER_LITERAL: return "INTEGER_LITERAL";
        case TokenType::BOOLEAN_LITERAL: return "BOOLEAN_LITERAL";
        case TokenType::FLOAT_LITERAL: return "FLOAT_LITERAL";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case TokenType::CHAR_LITERAL: return "CHAR_LITERAL";

        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::STAR: return "STAR";
        case TokenType::SLASH: return "SLASH";
        case TokenType::PERCENT: return "PERCENT";

        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::NOT_EQUAL: return "NOT_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";

        case TokenType::LOGICAL_AND: return "LOGICAL_AND";
        case TokenType::LOGICAL_OR: return "LOGICAL_OR";
        case TokenType::LOGICAL_NOT: return "LOGICAL_NOT";
        case TokenType::INCREMENT: return "INCREMENT";
        case TokenType::DECREMENT: return "DECREMENT";

        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::COMMA: return "COMMA";
        case TokenType::SEMICOLON: return "SEMICOLON";

        case TokenType::END_OF_FILE: return "END_OF_FILE";
        case TokenType::INVALID: return "INVALID";

        default: return "OTHER_TOKEN";
    }
}



int main() {
    
    Lexer lexer("= == ! != < <= > >= + ++ - -- & && | ||");

    while(true) {
        Token token = lexer.nextToken();

        std::cout << token.lexeme
                  << " | type: " << tokenTypeName(token.type)
                  << " | line: " << token.line
                  << " | column: " << token.column
                  << '\n';


        if (token.type == TokenType::END_OF_FILE) {
            break;
        }
    }
    return 0;
}