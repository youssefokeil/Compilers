#include "parser.h"

Node* Parser::read_stmt() {
    if (!match(READ)) return errorNode();

    if (current_token().token_type != IDENTIFIER) return errorNode();
    TokenRecord id = current_token();
    match(IDENTIFIER);

    Node* node = new Node{ READ_STMT, "read", {} };
    Node* id_node = new Node{ ID_NODE, id.string_val, {} };
    node->children.push_back(id_node);
    return node;
}