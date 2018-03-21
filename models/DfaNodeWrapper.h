//
// Created by programajor on 3/21/18.
//

#ifndef COMPILERS_NODEWRAPPER_H
#define COMPILERS_NODEWRAPPER_H


#include "Edge.h"

class DfaNodeWrapper {
private:
    vector<Edge*> nfaEdges;
    Node* dfaNode;

public:
    Node* getDfaNode();
    void setNfaEdges(vector <Edge*> edges);
    vector <Edge*> getNfaEdges();
    void addDfaEdge(Edge* edge);
};


#endif //COMPILERS_NODEWRAPPER_H
