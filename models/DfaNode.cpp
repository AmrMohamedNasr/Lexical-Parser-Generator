//
// Created by programajor on 3/21/18.
//

#include "DfaNode.h"

bool DfaNode::isAcceptedState() {
    return this->acceptedState;
}

void DfaNode::setAcceptState(bool newState) {
    this->acceptedState = newState;
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