
#pragma once

#include <string>
#include <cstddef>


enum class TokenType {

    // Keywords | کلمات کلیدی
    KW_INT,
    KW_CHAR,
    KW_FLOAT,
    KW_DOUBLE,
    KW_SIGNED,
    KW_UNSIGNED,
    KW_LONG,
    KW_SHORT,
    KW_VOID,
    KW_BOOL,

    KW_IF,
    KW_ELSE,
    KW_WHILE,
    KW_DO,
    KW_SWITCH,
    KW_CASE,
    KW_FOR,
    KW_BREAK,
    KW_CONTINUE,
    KW_RETURN,
    


    // پیشوند `KW_` یعنی `Keyword`
    // کمک می کند کلمات قراردادی از شناسه ها متمایز شوند.

    // Identifiers and literals
    // شناسه ها و انواع ثابت
    IDENTIFIER,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    CHAR_LITERAL,
    STRING_LITERAL,
    BOOLEAN_LITERAL,


    // Arithmetic operators
    // عملگر های ریاضی
    PLUS,       // +
    MINUS,      // -
    STAR,       // *
    SLASH,      // /
    PERCENT,    // %


    // Assignment and comparison operators
    // عملگرهای جایگذاری و مقایسه ای
    ASSIGN,             // =
    EQUAL_EQUAL,        // ==
    NOT_EQUAL,          // !=
    LESS,               // <
    LESS_EQUAL,         // <=
    GREATER,            // >
    GREATER_EQUAL,      // >=


    // Logical operators
    // عملگرهای منطقی
    LOGICAL_AND,        // &&
    LOGICAL_OR,         // ||
    LOGICAL_NOT,        // !


    // Increment and decrement
    // افزایش و کاهش
    INCREMENT,
    DECREMENT,


    // Punctuation
    // علامت گذاری
    LEFT_PAREN,     // (
    RIGHT_PAREN,    // )
    LEFT_BRACE,     // {
    RIGHT_BRACE,    // }
    COMMA,          // ,
    SEMICOLON,      // ;


    // Special tokens
    END_OF_FILE,
    INVALID,

};


struct Token {

    TokenType type;
    std::string lexeme;
    int line;
    int column;

};


class Lexer {

    public:
        explicit Lexer(const std::string& source);

        Token nextToken();      // توکت بعدی را تشخیص مب دهد و برمیگرداند.

    private:
        std::string source;         // کل متن برنامه را در برمیگیرد
        std::size_t position = 0;   // موقعیت فعلی در متن
        // شماره خط و ستون برای گزارشش خطا
        int line = 1;
        int column = 1;
        bool unterminatedComment = false;

        char currentChar() const;
        char peekChar() const;
        void advance();
        void skipWhitespace();
        void skipComments();

        Token readString(int startLine, int startColumn);
        Token readChar(int startLine, int startColumn);

};