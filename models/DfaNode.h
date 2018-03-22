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
    set<Node *> supportingNodes;
    bool start;
public:
    bool isAcceptedState();
    void setAcceptState(bool newState);

    bool isStart();
    void setStart(bool isStart);

    string getName();
    void setName(string name);

    vector<DfaEdge *> getEdges();
    void addEdge(DfaEdge * e);

    DfaNode(string stateName, bool accept);
//    DfaNode(string stateName, bool accept, bool start);

//    void setSupportingNfaNodes(set<Node *> nodes);
//    set<Node*> getSupportedNfaNodes();
};

#endif //COMPILERS_DFANODE_H
