#include "parser.h"


Node* Parser::write_stmt() {
    if (!match(WRITE)) return errorNode();

    Node* node = new Node{ WRITE_STMT, "write", {} };
    node->children.push_back(exp());
    return node;
}