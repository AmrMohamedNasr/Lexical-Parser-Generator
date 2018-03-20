//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NFADFACONVERTER_H
#define COMPILERS_NFADFACONVERTER_H

#include "../models/Node.h"

class NfaDfaConverter {

    public:
        /**
         * takes combined NFA from the combiner and converts it to a non minimized DFA.
         * @param combinedNfa the combined NFA from the combiner
         * @return a non minimized DFA from the given NFA.
         */
        Node *getNonMinimizedDFA(Node *combinedNfa);

private:
    set<Node*> getEpslonClosure(Node *node);

    string getStateName(set<Node *> states);

    bool getIsAccepted(set<Node *> states);

    vector<Edge *> getEdges(set<Node *> states);

    Node * getDfaStartState(Node *combinedNfa);

    Node * getEpslonClosureFromSet(set<Node *> states);

    bool setContainsState(set<Node *> states, Node *node);

    bool representingSameNfa(Node *n1, Node *n2);

    bool isFound(vector<Edge *> vector, Edge *&edge);
};


#endif //COMPILERS_NFADFACONVERTER_H
