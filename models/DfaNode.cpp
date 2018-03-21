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

DfaNode::DfaNode(string stateName, bool accept) {
    this->name = stateName;
    this->acceptedState = accept;
}

//void DfaNode::setSupportingNfaNodes(set<Node *> nodes) {
//    this->supportingNodes = nodes;
//}
//
//set<Node *> DfaNode::getSupportedNfaNodes() {
//    return this->supportingNodes;
//}
