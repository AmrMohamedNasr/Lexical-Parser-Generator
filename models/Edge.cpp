//
// Created by programajor on 3/16/18.
//

#include "Edge.h"
#include <algorithm>

Edge::Edge(char start, char end, Node * target) {
	this->first_allowed_char = start;
	this->last_allowed_char = end;
	this->allowing_range = end - start + 1;
	this->target_node = target;
}

void Edge::disallow_character(char c) {
	this->disallowed_chars.push_back(c);
	if (c >= this->first_allowed_char && c <= this->last_allowed_char) {
		this->allowing_range--;
	}
}

Node * Edge::do_transition(char c) {
	if (this->valid_transition(c)) {
		return this->target_node;
	} else {
		return nullptr;
	}
}

bool Edge::is_eps_transition() {
	return this->first_allowed_char == '\0' && this->last_allowed_char == '\0';
}

int Edge::getAllowedRange() {
	return this->allowing_range;
}

bool Edge::valid_transition(char c) {
	if (find(this->disallowed_chars.begin(), this->disallowed_chars.end(), c) != this->disallowed_chars.end()) {
		return false;
	} else {
		return c <= this->last_allowed_char && c >= this->first_allowed_char;
	}
}

char Edge::getFirstAllowedCharacter() {
	return this->first_allowed_char;
}

char Edge::getLastAllowedCharacter() {
	return this->last_allowed_char;
}

Node *Edge::getTargetNode() {
    return this->target_node;
}
