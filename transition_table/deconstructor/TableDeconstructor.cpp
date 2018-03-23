//
// Created by programajor on 3/23/18.
//

#include "TableDeconstructor.h"
#include "../../models/DfaEdge.h"

vector<DfaNode *> TableDeconstructor::deconstructGraph(TransitionTable table) {
    vector<DfaNode * > nodes;
    vector<string> input;
    vector<vector<DfaNode * >> transitions;

    for (int i = 0; i < input.size(); ++i) {
        string singleInput = input[i];
        for (int j = 0; j < singleInput.length(); j += 3) {
            for (int k = 0; k < transitions.size(); ++k) {
                DfaNode* start = nodes[k];
                DfaNode* target = transitions[k][i];
                char s = singleInput[j];
                char t = singleInput[j + 2];
                DfaEdge* edge = new DfaEdge(s, t, start, target);
                start->addEdge(edge);
            }
        }
    }

    return nodes;
}
