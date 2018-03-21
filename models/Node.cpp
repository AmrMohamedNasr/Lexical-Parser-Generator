//
// Created by programajor on 3/16/18.
//

#include "Node.h"

bool Node::isAcceptedState() {
	return this->acceptedState;
}

string Node::getName() {
	return this->name;
}

void Node::setName(string name) {
	this->name = name;
}

vector<Edge *> Node::getEdges() {
	return this->edges;
}

vector<Edge *> Node::getDfaEdges() {
	return this->dfaEdges;
}

void Node::addEdge(Edge * e) {
	this->edges.push_back(e);
}

void Node::addDfaEdge(Edge * e) {
	this->dfaEdges.push_back(e);
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

void Node::setSupportingNfaNodes(set<Node *> nodes) {
	this->supportingNodes = nodes;
}

set<Node *> Node::getSupportedNfaNodes() {
	return this->supportingNodes;
}

