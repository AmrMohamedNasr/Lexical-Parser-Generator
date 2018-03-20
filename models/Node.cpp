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

void Node::setAcceptState(bool newState) {
	this->acceptedState = newState;
}

void Node::setSupportingNfaNodes(set<Node *> nodes) {
//	this->nfaNodes = SupportingNfaNodes(nodes);
	this->supportingNodes = nodes;
}

set<Node *> Node::getSupportedNfaNodes() {
//	return this->nfaNodes.getSupportingNodes();
	return this->supportingNodes;
}

