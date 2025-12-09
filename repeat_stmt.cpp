#include "parser.h"


Node* Parser::repeat_stmt() {
    if (!match(REPEAT)) return errorNode();

    Node* node = new Node{ REPEAT_STMT, "repeat", {} };
    // body: parse statements until UNTIL
    node->children.push_back(stmt_seq());

    if (!match(UNTIL)) return errorNode();
    node->children.push_back(exp());
    return node;
}