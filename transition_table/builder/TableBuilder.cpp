//
// Created by programajor on 3/23/18.
//

#include "TableBuilder.h"

TransotionTable TableBuilder::buildTransitionTable(vector<DfaNode *> nodes, vector<char> alphabets) {
    DfaNode* phi = new DfaNode("Phi", false);
    nodes.push_back(phi);

    vector<vector<DfaNode*>> transitions;
    for (int i = 0; i < nodes.size(); ++i) {
        vector<DfaNode *> vec;
        transitions.push_back(vec);
    }

    for (int j = 0; j < alphabets.size(); ++j) {
        transitions[transitions.size() - 1].push_back(phi); // under any input phi goes to itself
    }

    for (int i = 0; i < alphabets.size(); i) {
        char input = alphabets[i];
        for (int j = 0; j < transitions.size(); j++) {
//            if (nodes[j].)
        }
    }
    return TransotionTable();
}
