#include "parser.h"

Node* Parser::term() {
    Node* left_node = factor();

    while (current_token().token_type == MULT || current_token().token_type == DIV) {
        TokenRecord op = current_token();
        match(op.token_type);
        Node* right = factor();
        Node* op_node = new Node{ OP_NODE, op.string_val, {} };
        op_node->children.push_back(left_node);
        op_node->children.push_back(right);
        left_node = op_node;
    }

    return left_node;
}