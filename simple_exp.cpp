#include "parser.h"


Node* Parser::simple_exp() {
    Node* left_node = term();

    while (current_token().token_type == PLUS || current_token().token_type == MINUS) {
        TokenRecord op = current_token();
        match(op.token_type); 
        Node* right = term();
        Node* op_node = new Node{ OP_NODE, op.string_val, {} };
        op_node->children.push_back(left_node);
        op_node->children.push_back(right);
        left_node = op_node;
    }

    return left_node;
}