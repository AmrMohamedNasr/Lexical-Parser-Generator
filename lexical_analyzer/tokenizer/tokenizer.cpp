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
	DfaNode * lastAccepted = nullptr;
	DfaNode * curNode = this->machine;
	string lastAcceptedBuffer;
	string errorBuffer;
	string currentBuffer;
	unsigned lastAcceptanceEnd = 0;
	bool isFirstChar = true;
	bool trackingError = false;
	for (unsigned i = 0; i < str.length(); i++) {
		char c = str.at(i);
		if (curNode->valid_transition(c)) {
			isFirstChar = false;
			if (trackingError) {
				trackingError = false;
				this->tokens.push(Token(ERROR_TOKEN, errorBuffer, ""));
				errorBuffer = "";
			}

			curNode = curNode->do_transition(c);
			currentBuffer += c;
			if (curNode->isAcceptedState()) {
				lastAccepted = curNode;
				lastAcceptedBuffer = currentBuffer;
				lastAcceptanceEnd = i;
			}
		} else {
			if (trackingError) { // append to current detected error
				errorBuffer += c;
			} else {
				trackingError = true;
				if (isFirstChar || i == lastAcceptanceEnd + 1) { // error with first character, remove it and restart
					errorBuffer += c;
					curNode = this->machine;

					// if there is a previous acceptance
					if (!lastAcceptedBuffer.empty()) { // add last valid acceptance
						this->tokens.push(Token(REAL_TOKEN, lastAcceptedBuffer, lastAccepted->getName()));
						lastAcceptedBuffer = "";
						currentBuffer = "";
					}

				} else {
					// check if there is an acceptance state
					if (!lastAcceptedBuffer.empty()) {
						// add last accepted token
						this->tokens.push(Token(REAL_TOKEN, lastAcceptedBuffer, lastAccepted->getName()));
						lastAcceptedBuffer = "";
						currentBuffer = "";
						// backtrack to start after last valid token
						i = lastAcceptanceEnd;
						trackingError = false;
					} else { // previous input correct with no acceptance state
						errorBuffer += currentBuffer;
						errorBuffer += c;
						curNode = this->machine;
					}

				}
			}
		}
	}

	if (trackingError) {
		this->tokens.push(Token(ERROR_TOKEN, errorBuffer, ""));
	}

	if (!lastAcceptedBuffer.empty()) {
		this->tokens.push(Token(REAL_TOKEN, lastAcceptedBuffer, lastAccepted->getName()));
	}
}

void Tokenizer::reset() {
	queue<Token>().swap(this->tokens);
}

Tokenizer::Tokenizer(DfaNode * start) {
	this->machine = start;
}

Tokenizer::Tokenizer() = default;

void Tokenizer::setStart(DfaNode * newStart) {
	this->machine = newStart;
	this->reset();
}
