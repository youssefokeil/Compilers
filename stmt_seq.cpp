#include "parser.h"

Node* Parser::stmt_seq() {
    Node* sequence = new Node{ STMT_SEQ, "seq", {} };

    while (position < (int)Tokens.size()) {
        TokenType ct = current_token().token_type;

        // Only these end a statement list
        if (ct == END || ct == ElSE || ct == UNTIL)
            break;

        Node* s = statement();
        sequence->children.push_back(s);

        if (current_token().token_type == SEMICOLON) {
            match(SEMICOLON);
            continue;
        }
        else {
            break;
        }
    }

    return sequence;
}