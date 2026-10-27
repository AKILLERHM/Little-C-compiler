
#pragma once

#include <string>       // برای std::string
#include <cstddef>      // برای std::size_t (نوع اندازه و اندیس)


enum class TokenType {

    // Keywords | کلمات کلیدی
    // کلمات کلیدی مربوط به نوع داده
    KW_INT,
    KW_CHAR,
    KW_FLOAT,
    KW_DOUBLE,
    KW_SIGNED,
    KW_UNSIGNED,
    KW_LONG,
    KW_SHORT,
    KW_VOID,
    KW_BOOL,        // در استاندراد های جدید زبان C وجود دارد

    // کلمات کلیدی مربوط به کنترل جریان
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
    IDENTIFIER,             // نام متغیر / تابع
    INTEGER_LITERAL,        // عدد صحیح
    FLOAT_LITERAL,          // عدد اعشاری
    CHAR_LITERAL,           // کاراکتر بصورت: 'A'
    STRING_LITERAL,         // رشته بصورت: "ABCDEF"
    BOOLEAN_LITERAL,        // true / false


    // Arithmetic operators
    // عملگر های ریاضی
    PLUS,       // +
    MINUS,      // -
    STAR,       // *
    SLASH,      // /
    PERCENT,    // %


    // Assignment and comparison operators
    // عملگرهای جایگذاری و مقایسه ای
    ASSIGN,             // =    (برای جایگذاری مقادیر)
    EQUAL_EQUAL,        // ==   (برای سنجش مقادیر)
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
    INCREMENT,      // ++
    DECREMENT,      // --


    // Punctuation
    // علامت گذاری
    LEFT_PAREN,     // (
    RIGHT_PAREN,    // )
    LEFT_BRACE,     // {
    RIGHT_BRACE,    // }
    COMMA,          // ,
    SEMICOLON,      // ;


    // Special tokens
    // توکن های ویژه
    END_OF_FILE,
    INVALID,

};


/*  یک بخش لغوی چهار بخش دارد:
    type: نوع آن
    lexeme: متن اصلی همان توکن
    line: شماره خطی که توکن از آن شروع شده
    column: شماره ستونی که توکن از آن شروع شده */

struct Token {

    TokenType type;
    std::string lexeme;
    int line;
    int column;

};


class Lexer {

    public:
        explicit Lexer(const std::string& source);

        Token nextToken();      // توکن بعدی را تشخیص می دهد و برمیگرداند.

    private:
        std::string source;         // کل متن برنامه را در برمیگیرد
        std::size_t position = 0;   // موقعیت فعلی در متن

        // شماره خط و ستون برای گزارشش خطا
        int line = 1;
        int column = 1;
        // پرچم: آیا کامنت /* ... */ بدون بسته شدن به انتهای فایل رسید؟
        // skipComments فقط پرچم را روشن می‌کند و nextToken خطا را برمی‌گرداند.
        bool unterminatedComment = false;

        // توابع شناسایی
        char currentChar() const;
        char peekChar() const;
        void advance();
        void skipWhitespace();
        void skipComments();

        // خواندن «کاراکتر» 'a' و «رشته» "abc"
        Token readString(int startLine, int startColumn);
        Token readChar(int startLine, int startColumn);

};