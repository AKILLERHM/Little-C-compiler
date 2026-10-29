# Little-C-compiler
a Mini C compiler implemented in `c++` for my Compiler Design course.

یک پروژه با موضوع ساخت یک کامپایلر کوچک زیرمجموعه زبان برنامه نویسی C، با زبان C++ توسعه داده میشود.

#### 1. Keywords and Identifiers | کلمات کلیدی و شناسه ها

- Recognizes supported keywords such as int, char, float, if, while, and return.
- Distinguishes keywords from identifiers.

#### 2. Literals | مقادیر ثابت

- Integer literals, such as 42.
- Floating-point literals, such as 3.14.
- Boolean literals: true and false.
- String literals.
- Character literals, including supported escape sequences.

#### 3. Operators and Punctuation | عملگرها و علائم نگارشی

- Arithmetic operators: +, -, *, /, %.
- Assignment and comparison operators: =, ==, !=, <, <=, >, >=.
- Logical operators: &&, ||, !.
- Increment and decrement operators: ++, --.
- Punctuation: parentheses, braces, commas, and semicolons.

#### 4. Comments | کامنت‌ها

- Single-line comments: //
- Multi-line comments: /* ... */

#### 5. Source Positions | موقعیت توکن‌ها در کد

Each token stores its type, lexeme, line number, and column number.

هر توکن اطلاعات زیر را نگه می‌دارد:
- نوع توکن (Token Type).
- متن توکن (Lexeme).
- شمارهٔ خط (Line).
- شمارهٔ ستون (Column).

#### 6. Error Handling | مدیریت خطاها

The lexer detects invalid characters and malformed or unterminated literals and comments. It can also continue scanning after encountering invalid characters.

Lexer کاراکترهای نامعتبر و مقادیر ثابت یا کامنت‌های ناقص و بسته‌نشده را تشخیص می‌دهد. همچنین می‌تواند پس از برخورد با کاراکتر نامعتبر، اسکن ورودی را ادامه دهد.

#### 7. Automated Tests | تست‌های خودکار

The project includes automated tests written using C++ assert.

این پروژه شامل تست‌های خودکار با استفاده از assert در زبان C++ است.

The tests cover token recognition, operators, keywords, literals, comments, source positions, invalid inputs, and end-of-file handling.

تست‌ها موارد زیر را بررسی می‌کنند:
- تشخیص توکن‌ها، کلمات کلیدی و عملگرها.
- شناسایی مقادیر ثابت.
- پردازش کامنت‌ها.
- بررسی شمارهٔ خط و ستون.
- مدیریت ورودی‌های نامعتبر و حالت‌های مرزی.
- تشخیص پایان ورودی (EOF).


### Requirements | پیش‌نیازها

- A C++ compiler.
- GCC/G++ is used for development and testing.


### Build and Run | کامپایل و اجرا

Compile the main program:

برنامهٔ اصلی را کامپایل کنید:

` g++ main.cpp src/lexer.cpp -I include -o main.exe `


Run the program in Windows PowerShell:

برنامه را در Windows PowerShell اجرا کنید:

` .\main.exe `


The program prints recognized tokens, their types, and their source positions.

برنامه توکن‌های شناسایی‌شده، نوع هر توکن و موقعیت آن در کد را نمایش می‌دهد.



### Run Tests | اجرای تست‌ها

Compile the test suite:

تست‌ها را کامپایل کنید:

` g++ tests/lexer_tests.cpp src/lexer.cpp -I include -o lexer_tests.exe `


Run the tests in Windows PowerShell:

تست‌ها را در Windows PowerShell اجرا کنید:

` .\lexer_tests.exe `


A successful test run prints:

در صورت موفقیت‌آمیز بودن تست‌ها، پیام زیر نمایش داده می‌شود:

` All lexer tests passed! `



### Example | نمونه کد

The following C-like program demonstrates several constructs recognized by the lexer.

کد شبه‌C زیر چند نمونه از ساختارهایی را نشان می‌دهد که Lexer آن‌ها را به‌عنوان توکن شناسایی می‌کند.

```

int main() {
    char c = 'A';
    float x = 3.14;

    if (x >= 2.0 && true) {
        x++;
    }

    return 0;
}

```

Lexer در این ورودی کلمات کلیدی، شناسه‌ها، مقادیر ثابت، عملگرها و علائم نگارشی را شناسایی می‌کند.
