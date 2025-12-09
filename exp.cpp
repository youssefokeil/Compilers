#include "parser.h"


Node* Parser::exp() {
    Node* left_node = simple_exp();

    if (current_token().token_type == LESSTHAN || current_token().token_type == EQUAL) {
        TokenRecord op = current_token();
        match(op.token_type);
        Node* right = simple_exp();
        Node* op_node = new Node{ OP_NODE, op.string_val, {} };
        op_node->children.push_back(left_node);
        op_node->children.push_back(right);
        return op_node;
    }

    return left_node;
}