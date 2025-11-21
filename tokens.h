#include <string>

typedef enum{
    SEMICOLON,      //0
    IF,             //1
    THEN,           //2
    END,            //3
    REPEAT,         //4
    UNTIL,          //5
    IDENTIFIER,     //6
    ASSIGN,         //7
    READ,           //8
    WRITE,          //9
    LESSTHAN,       //10
    EQUAL,          //11
    PLUS,           //12
    MINUS,          //13
    MULT,           //14
    DIV,            //15
    OPENBRACKET,    //16
    CLOSEDBRACKET,  //17
    NUMBER,         //18
    ERROR           //19
} TokenType;

struct TokenRecord
{
    /* data */
    TokenType token_type;
    std::string string_val;
    int num_val;
};
