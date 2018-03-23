//
// Created by programajor on 3/21/18.
//

#include "DfaNode.h"
#include "DfaEdge.h"

bool DfaNode::isAcceptedState() {
    return this->acceptedState;
}

DfaNode :: DfaNode(string stateName, bool accept) {
	this->acceptedState = accept;
	this->name = stateName;
    this->start = false;
}

string DfaNode::getName() {
    return this->name;
}

void DfaNode::setName(string name) {
    this->name = name;
}

vector<DfaEdge *> DfaNode::getEdges() {
    return this->edges;
}

void DfaNode::addEdge(DfaEdge *e) {
    this->edges.push_back(e);
}

bool DfaNode::isStart() {
    return this->start;
}

void DfaNode::setStart(bool isStart) {
    this->start = isStart;
}

bool DfaNode::valid_transition(char c) {
    for (unsigned i = 0; i < edges.size(); i++) {
        DfaEdge* e = edges[i];
        if (e->valid_transition(c)) {
            return true;
        }
    }
    return false;
}

DfaNode *DfaNode::do_transition(char c) {
    for (unsigned i = 0; i < edges.size(); i++) {
        DfaEdge* e = edges[i];
        DfaNode* destination = e->do_transition(c);
        if (destination != nullptr) {
            return destination;
        }
    }
    return nullptr;
}
DfaNode::~DfaNode() {
	for (unsigned i = 0; i < this->edges.size(); i++) {
		delete this->edges[i];
	}
}

vector<DfaEdge *> *DfaNode::getRealEdges() {
	return &this->edges;
}
