#include "parser.h"

Node* Parser::statement() {
    TokenType t = current_token().token_type;
    switch (t) {
    case IF:        return if_stmt();
    case REPEAT:    return repeat_stmt();
    case IDENTIFIER: return assign_stmt();
    case READ:      return read_stmt();
    case WRITE:     return write_stmt();
    default:
        if (position < (int)Tokens.size()) position++;
        return errorNode();
    }
}