// lexer aka(also knows as) scanner

#include "lexer.hpp"
#include <cstddef>
#include <string>
#include <cctype>
#include <unordered_map>


Lexer::Lexer(const std::string& source): source(source){}

// کاراکتر فعلی را برمی گرداند. اگر به انتهای ورودی رسیده باشد  `\0` برمی گراداند.
char Lexer::currentChar() const{
    if (position >= source.size()) {
        return '\0';
    }

    return source[position];
}


// کاراکتر بعدی را نگاه می کند بدون اینکه موقعیت فعلی تغییر کند. مثال برای تشخیص `=` از `==`.
char Lexer::peekChar() const {
    if (position +1 >= source.size()) {
        return '\0';
    }

    return source[position + 1];
}


// یک کاراکتر جاو می رود و شماره خط و ستون رو بروزرسانی میکند.
void Lexer::advance() {
    if (position >= source.size()) {
        return;
    }

    if (source[position] == '\n') {
        ++line;
        column = 1;
    
    } else {
        ++column;
    }

    ++position;
}


//فاصله ها و خط های جدید را رد کرده تا Lexer به اولین کاراکتر معنادار برسد.
void Lexer::skipWhitespace() {

    while (currentChar() == ' '  ||
           currentChar() == '\t' ||
           currentChar() == '\n' ||
           currentChar() == '\r') {
            advance();
        }
}


void Lexer::skipComments() {
    // for single-line comment: //  | برای کامنت های خطی
    if (currentChar() == '/' && peekChar() == '/') {
        while (currentChar() != '\n' &&
               currentChar() != '\0') {
                advance();
               }
               return;
    }

    // multi-line comment: /* ... */    | برای کامنت های چند خطی
    if (currentChar() == '/' && peekChar() == '*') {
        advance(); // /
        advance(); // *

        while (currentChar() != '\0') {
            if (currentChar() == '*' && peekChar() == '/') {
                advance(); // *
                advance(); // /
                return;
            }
            advance();
        }

        unterminatedComment = true;
    }
}


Token Lexer::readChar(int startLine, int startColumn) {
    advance(); // consume opening singlw quote

    if (currentChar() == '\0' ||
        currentChar() == '\n' ||
        currentChar() == '\'') {
        if (currentChar() == '\''){
            advance();
        }

        return {
            TokenType::INVALID,
            "INVALID_CHAR_LITERAL",
            startLine,
            startColumn
        };
    }

    std::size_t start = position;

    // raed one character or one escape sequence
    if (currentChar() == '\\') {
        advance();

        if (currentChar() == '\0' || currentChar() == '\n') {
            return {
                TokenType::INVALID,
                "INVALID_CHAR_LITERAL",
                startLine,
                startColumn
            };
        }
    }

    advance();

    if (currentChar() != '\'') {
        while (currentChar() != '\'' &&
               currentChar() != '\0' &&
               currentChar() != '\n') {
                advance();
            }
            if (currentChar() == '\'') {
                advance();
            }

            return {
                TokenType::INVALID,
                "INVALID_CHAR_LITERAL",
                startLine,
                startColumn
            };
    }

    std::string value = source.substr(start, position - start);
    advance(); // consume closing single quote

    return {
        TokenType::CHAR_LITERAL,
        value,
        startLine,
        startColumn
    };
}


Token Lexer::readString(int startLine, int startColumn) {
    advance(); // consume opening quete

    std::size_t start = position;

    while (currentChar() != '"' &&
           currentChar() != '\0' &&
           currentChar() != '\n') {
            if (currentChar() == '\\' && peekChar() != '\0') {
                advance();
            }
            advance();
           }

           if (currentChar() != '"') {
            return {
                TokenType::INVALID,
                "UNTERMINATED_STRING",
                startLine,
                startColumn
            };
           }

           std::string value = source.substr(start, position - start);

           advance(); // consume closing quote

           return {
            TokenType::STRING_LITERAL,
            value,
            startLine,
            startColumn
           };
}


/* چرا دو تابع جدا؟
چون `age42` معتبر است اما 
`42age` معتبر نیست.
شروع شناسه و ادامه آن قواعدی دارد.*/

static bool isIdentifierStart(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}


static bool isIdentifierPart(char c) {
    return isIdentifierStart(c) ||
        (c >= '0' && c <= '9');
}



static TokenType getKeywordType(const std::string& word) {
    static const std::unordered_map<std::string, TokenType> keywords = {
        {"int", TokenType::KW_INT},
        {"char", TokenType::KW_CHAR},
        {"float", TokenType::KW_FLOAT},
        {"double", TokenType::KW_DOUBLE},
        {"signed", TokenType::KW_SIGNED},
        {"unsigned", TokenType::KW_UNSIGNED},
        {"long", TokenType::KW_LONG},
        {"short", TokenType::KW_SHORT},
        {"void", TokenType::KW_VOID},
        {"bool", TokenType::KW_BOOL},

        {"if", TokenType::KW_IF},
        {"else", TokenType::KW_ELSE},
        {"while", TokenType::KW_WHILE},
        {"do", TokenType::KW_DO},
        {"switch", TokenType::KW_SWITCH},
        {"case", TokenType::KW_CASE},
        {"for", TokenType::KW_FOR},
        {"break", TokenType::KW_BREAK},
        {"continue", TokenType::KW_CONTINUE},
        {"return", TokenType::KW_RETURN}
    };

    auto it = keywords.find(word);

    if (it != keywords.end()) {
        return it->second;
    }

    return TokenType::IDENTIFIER;
}


Token Lexer::nextToken() {
    while (true) {
        skipWhitespace();
        if (unterminatedComment) {
            unterminatedComment = false;

            return {
                TokenType::INVALID,
                "UNTERMINATED_COMMENT",
                line,
                column
            };
        }

        if (currentChar() == '/' &&
            (peekChar() == '/' || peekChar() == '*')) {
                skipComments();
            } else {
                break;
            }
    }
    

    int startLine = line;
    int startColumn = column;

    if(currentChar() == '\0') {
        return {
            TokenType::END_OF_FILE,
            "",
            startLine,
            startColumn,
        };
    }


    if (currentChar() >= '0' && currentChar() <= '9') {
        std::size_t start = position;

        // Read the integer part
        // خواندن اعداد صحیح
        while (currentChar() >= '0' &&
               currentChar() <= '9') {
                advance();
               }

        // Check whether this is a decimal number
        // چک کنیم آیا عدد اعشاری هست 
        if (currentChar() == '.' &&
            // چرا peekChar() استفاده کردیم؟
            // تا چک شود بعد از اعشار عددی وجود دارد یا خیر
            peekChar() >= '0' &&
            peekChar() <= '9') {
            advance();  // Consume the decimal point | گرفتن بخش اعشاری عدد
            
            while (currentChar() >= '0' &&
                   currentChar() <= '9') {
                    advance();
                }
                return {
                    TokenType::FLOAT_LITERAL,
                    source.substr(start, position - start),
                    startLine,
                    startColumn
                };
        }

        return {
            TokenType::INTEGER_LITERAL,
            source.substr(start, position - start),
            startLine,
            startColumn
        };
    }


    if(isIdentifierStart(currentChar())) {
        std::size_t start = position;

        while (isIdentifierPart(currentChar())) {
            advance();
        }

        std::string word = source.substr(start, position - start);

        if(word == "true" || word == "false") {
            return {
                TokenType::BOOLEAN_LITERAL,
                word,
                startLine,
                startColumn
            };
        }

        return {
            getKeywordType(word),
            word,
            startLine,
            startColumn
        };

    }





    char c = currentChar();

    switch (c) {

        case '+':
            advance();
            if (currentChar() == '+') {
                advance();
                return {TokenType::INCREMENT, "++",
                    startLine, startColumn};
            }
            return {TokenType::PLUS, "+", startLine, startColumn};


        case '-':
            advance();
            if (currentChar() == '-') {
                advance();
                return{TokenType::DECREMENT, "--",
                startLine, startColumn};
            }
            return {TokenType::MINUS, "-", startLine, startColumn};


        case '*':
            advance();
            return {TokenType::STAR, "*", startLine, startColumn};


        case '/':
            advance();
            return {TokenType::SLASH, "/", startLine, startColumn};


        case '%':
            advance();
            return {TokenType::PERCENT, "%", startLine, startColumn};


        case '=':
            advance();
            if (currentChar() == '=') {
                advance();
                return {TokenType::EQUAL_EQUAL, "==",
                        startLine, startColumn};
            }
            return {TokenType::ASSIGN, "=", startLine, startColumn};


        case '!':
            advance();
            if (currentChar() == '=') {
                advance();
                return {TokenType::NOT_EQUAL, "!=",
                        startLine, startColumn};
            }
            return {TokenType::LOGICAL_NOT, "!", startLine, startColumn};


        case '<':
            advance();
            if (currentChar() == '='){
                advance();
                return {TokenType::LESS_EQUAL, "<=",
                    startLine, startColumn};
            }
            return {TokenType::LESS, "<", startLine, startColumn};


        case '>':
            advance();
            if (currentChar() == '=') {
                advance();
                return {TokenType::GREATER_EQUAL, ">=",
                        startLine, startColumn};
            }
            return {TokenType::GREATER, ">", startLine, startColumn};


        case '&':
            advance();
            if (currentChar() == '&') {
                advance();
                return {TokenType::LOGICAL_AND, "&&",
                        startLine, startColumn};
            }
            return {TokenType::INVALID, "&", startLine, startColumn};


        case '|':
            advance();
            if (currentChar() == '|') {
                advance();
                return {TokenType::LOGICAL_OR, "||",
                        startLine, startColumn};
            }
            return {TokenType::INVALID, "|", startLine, startColumn};


        case '(':
            advance();
            return {TokenType::LEFT_PAREN, "(", startLine, startColumn};


        case ')':
            advance();
            return {TokenType::RIGHT_PAREN, ")", startLine, startColumn};


        case '{':
            advance();
            return {TokenType::LEFT_BRACE, "{", startLine, startColumn};


        case '}':
            advance();
            return {TokenType::RIGHT_BRACE, "}", startLine, startColumn};


        case ',':
            advance();
            return {TokenType::COMMA, ",", startLine, startColumn};


        case ';':
            advance();
            return {TokenType::SEMICOLON, ";", startLine, startColumn};
    }
   
    if (currentChar() == '\'') {
        return readChar(startLine, startColumn);
    }

    if (currentChar() == '"') {
        return readString(startLine, startColumn);
    }

    advance();

    return {
        TokenType::INVALID,
        std::string(1, c),
        startLine,
        startColumn
    };

}