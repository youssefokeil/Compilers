#include <string>

typedef enum{
    SEMICOLON,
    IF,
    THEN,
    END,
    REPEAT,
    UNTIL,
    IDENTIFIER,
    ASSIGN,
    READ,
    WRITE,
    LESSTHAN,
    EQUAL,
    PLUS,
    MINUS,
    MULT,
    DIV, 
    OPENBRACKET,
    CLOSEDBRACKET,
    NUMBER
} TokenType;

struct TokenRecord
{
    /* data */
    TokenType token_type;
    std::string string_val;
    int num_val;
};
