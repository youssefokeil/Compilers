#include "parser.h"


Node* Parser::assign_stmt() {
    // assignment should start with IDENTIFIER
    if (current_token().token_type != IDENTIFIER) return errorNode();
    TokenRecord id = current_token();
    match(IDENTIFIER);

    if (!match(ASSIGN)) return errorNode(); 

    Node* node = new Node{ ASSIGN_STMT, ":=", {} };
    Node* id_node = new Node{ ID_NODE, id.string_val, {} };
    node->children.push_back(id_node);
    node->children.push_back(exp());
    return node;
}