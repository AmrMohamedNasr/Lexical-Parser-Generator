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
    string printingName;
    vector<DfaEdge *> edges;
    bool acceptedState;
//    set<Node *> supportingNodes;
    bool start;
public:
    bool isAcceptedState();
    void setAcceptState(bool newState);

    bool isStart();
    void setStart(bool isStart);

    string getName();
    void setName(string name);

    string getPrintingName();
    void sePrintingtName(string printingName);

    vector<DfaEdge *> getEdges();
    void addEdge(DfaEdge * e);

    DfaNode(string stateName, bool accept);

    bool valid_transition(char c);
    DfaNode* do_transition(char c);
};

#endif //COMPILERS_DFANODE_H
