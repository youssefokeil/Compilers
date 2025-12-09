#include "parser.h"

Node* Parser::factor() {
    TokenType ct = current_token().token_type;

    if (ct == OPENBRACKET) {
        match(OPENBRACKET);
        Node* n = exp();
        match(CLOSEDBRACKET); 
        return n;
    }
    else if (ct == NUMBER) {
        TokenRecord t = current_token();
        match(NUMBER);
        Node* number_node = new Node{ CONST_NODE, to_string(t.num_val), {} };
        return number_node;
    }
    else if (ct == IDENTIFIER) {
        TokenRecord t = current_token();
        match(IDENTIFIER);
        Node* id_node = new Node{ ID_NODE, t.string_val, {} };
        return id_node;
    }
    else {
        if (position < (int)Tokens.size()) position++;
        return errorNode();
    }
}