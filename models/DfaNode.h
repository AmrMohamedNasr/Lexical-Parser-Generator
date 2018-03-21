//
// Created by programajor on 3/21/18.
//

#ifndef COMPILERS_DFANODE_H
#define COMPILERS_DFANODE_H

using namespace std;
#include "Node.h"

class DfaEdge;
class DfaNode {
private:
    string name;
    vector<DfaEdge *> edges;
    bool acceptedState;
public:
    bool isAcceptedState();
    void setAcceptState(bool newState);
    string getName();
    void setName(string name);
    vector<DfaEdge *> getEdges();
    void addEdge(DfaEdge * e);
    DfaNode(string stateName, bool accept);
//    void setSupportingNfaNodes(set<Node *> nodes);
//    set<Node *> getSupportedNfaNodes();
};

#endif //COMPILERS_DFANODE_H
