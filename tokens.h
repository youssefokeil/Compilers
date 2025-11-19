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

typedef struct TokenRecord
{
    /* data */
    TokenType token_type;
    char* string_val;
    int num_val;
};
