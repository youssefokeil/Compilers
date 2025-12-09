#include "parser.h"

Node* Parser::errorNode() {
    Node* n = new Node{ ERROR_X, "error", {} };
    return n;
}