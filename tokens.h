#include <string>

typedef enum{
    SEMICOLON,      //0
    IF,             //1
    ElSE,           //2
    THEN,           //3
    END,            //4
    REPEAT,         //5
    UNTIL,          //6
    IDENTIFIER,     //7
    ASSIGN,         //8
    READ,           //9
    WRITE,          //10
    LESSTHAN,       //11
    EQUAL,          //12
    PLUS,           //13
    MINUS,          //14
    MULT,           //15
    DIV,            //16
    OPENBRACKET,    //17
    CLOSEDBRACKET,  //18
    NUMBER,         //19
    ERROR           //20
} TokenType;

struct TokenRecord
{
    /* data */
    TokenType token_type;
    std::string string_val;
    int num_val;
};
