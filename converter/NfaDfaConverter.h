//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NFADFACONVERTER_H
#define COMPILERS_NFADFACONVERTER_H

#include "../models/Node.h"
#include "../models/DfaNode.h"
#include "../models/DfaEdge.h"
#include "../models/DfaNodeWrapper.h"

class NfaDfaConverter {

    public:
        /**
         * takes combined NFA from the combiner and converts it to a non minimized DFA.
         * @param combinedNfa the combined NFA from the combiner
         * @return a non minimized DFA from the given NFA.
         */
        DfaNode * getNonMinimizedDFA(Node *combinedNfa);

private:
    set<Node*> getEpslonClosure(Node *node);

    string getStateName(set<Node *> states);

    bool getIsAccepted(set<Node *> states);

    vector<Edge *> getEdges(set<Node *> states);

    DfaNodeWrapper * getDfaStartState(Node *combinedNfa);

    DfaNodeWrapper * getEpslonClosureFromSet(set<Node *> states);

    DfaNodeWrapper* setContainsState(set<DfaNodeWrapper *> states, DfaNodeWrapper *node);

    bool representingSameNfa(DfaNodeWrapper *n1, DfaNodeWrapper *n2);

    bool isFound(vector<Edge *> vector, Edge *&edge);

    DfaNode *removeRedundantEdges(DfaNode *node);
};


#endif //COMPILERS_NFADFACONVERTER_H
