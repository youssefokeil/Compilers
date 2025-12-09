#include "parser.h"

Node* Parser::program() {
	return stmt_seq();
}

