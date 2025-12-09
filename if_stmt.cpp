#include "parser.h"

Node* Parser::if_stmt() {
    if (!match(IF)) return errorNode();

    Node* node = new Node{ IF_STMT, "if", {} };

    // --- parse condition (with error handling) ---
    Node* condition = exp();
    if (!condition) condition = errorNode();
    node->children.push_back(condition);

    // --- expect THEN ---
    if (!match(THEN)) {
        // recover: skip tokens until THEN or END or ELSE
        while (position < Tokens.size()) {
            TokenType t = current_token().token_type;
            if (t == THEN || t == END || t == ElSE) break;
            position++;
        }
        if (!match(THEN)) return errorNode();
    }

    // --- parse THEN-body ---
    Node* thenPart = stmt_seq();
    node->children.push_back(thenPart);

    // --- optional ELSE ---
    if (current_token().token_type == ElSE) {   // FIX: correct token spelling
        match(ElSE);
        Node* elsePart = stmt_seq();
        node->children.push_back(elsePart);
    }

    // --- END ---
    if (!match(END)) return errorNode();

    return node;
}