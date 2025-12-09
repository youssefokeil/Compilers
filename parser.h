#pragma once
#include <iostream>
#include <vector>
#include "tokens.h"

using namespace std;

enum NodeType {
    IF_STMT, REPEAT_STMT, ASSIGN_STMT, READ_STMT, WRITE_STMT,
    OP_NODE, CONST_NODE, ID_NODE,
    STMT_SEQ, ERROR_X
};

struct Node {
    NodeType type;
    string value;
    vector<Node*> children;
};


class Parser {
private:
    vector<TokenRecord> Tokens;
    int position = 0;

    bool at_end() {
        return position >= Tokens.size();
    }

    TokenRecord current_token() {
        if (at_end()) {
            TokenRecord t;
            t.token_type = ERROR;
            return t;
        }
        return Tokens[position];
    }

    TokenRecord next_token() {
        if (at_end()) {
            TokenRecord t;
            t.token_type = ERROR;
            return t;
        }
        return Tokens[position++];
    }

    bool match(TokenType type) {
        if (!at_end() && Tokens[position].token_type == type) {
            position++;
            return true;
        }
        return false;
    }

public:
    Parser(vector<TokenRecord> tokens) : Tokens(tokens) {}
    Node* errorNode();
    Node* program();
    Node* stmt_seq();
    Node* statement();
    Node* if_stmt();
    Node* repeat_stmt();
    Node* assign_stmt();
    Node* read_stmt();
    Node* write_stmt();
    Node* exp();
    Node* simple_exp();
    Node* term();
    Node* factor();

};