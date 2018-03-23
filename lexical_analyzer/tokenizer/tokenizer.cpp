/*
 * tokenizer.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */
#include "tokenizer.h"

bool Tokenizer::hasNext() {
	return !this->tokens.empty();
}

Token Tokenizer::nextToken() {
	Token tok = this->tokens.front();
	this->tokens.pop();
	return tok;
}

void Tokenizer::tokenize(string str) {
	string buf = "";
	string accepted_buf = "";
	unsigned last_accept_inc = 0;
	bool error_routine = false;
	string err_buf = "";
	DfaNode * lastAccepted = nullptr;
	DfaNode * cur = this->machine;
	char temp;
	for (unsigned i = 0; i < str.length(); i++) {
		temp = str.at(i);
		if (cur->valid_transition(temp)) {
			buf += temp;
			cur = cur->do_transition(temp);
			if (cur->isAcceptedState()) {
				accepted_buf = buf;
				lastAccepted = cur;
				last_accept_inc = 0;
			}
			last_accept_inc++;
		} else {
			if (lastAccepted != nullptr) {
				if (error_routine) {
					this->tokens.push(Token(ERROR_TOKEN, err_buf, ""));
					err_buf = "";
					error_routine = false;
				}
				this->tokens.push(Token(REAL_TOKEN, accepted_buf, lastAccepted->getName()));
			} else {
				error_routine = true;
				err_buf += temp;
			}
			i -= last_accept_inc;
			cur = this->machine;
			buf = "";
		}
	}
	if (error_routine) {
		this->tokens.push(Token(ERROR_TOKEN, err_buf, ""));
	}
}

void Tokenizer::reset() {
	queue<Token>().swap(this->tokens);
}

Tokenizer::Tokenizer(DfaNode * start) {
	this->machine = start;
}

