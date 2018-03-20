//
// Created by programajor on 3/16/18.
//

#include "Node.h"
#include <string>

bool Node::isAcceptedState() {
	return this->acceptedState;
}

string Node::getName() {
	return this->name;
}

vector<Edge *> Node::getEdges() {
	return this->edges;
}

void Node::addEdge(Edge * e) {
	this->edges.push_back(e);
}

Node::Node(string stateName, bool accept) {
	this->acceptedState = accept;
	this->name = stateName;
}

Node::Node(bool accept) {
	this->acceptedState = accept;
}

void Node::setAcceptState(bool newState) {
	this->acceptedState = newState;
}
