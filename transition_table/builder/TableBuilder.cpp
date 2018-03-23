//
// Created by programajor on 3/23/18.
//

#include <algorithm>
#include "TableBuilder.h"

TransitionTable TableBuilder::buildTransitionTable(vector<DfaNode *> nodes, vector<char> alphabets) {
    DfaNode* phi = new DfaNode("Phi", false);
    phi->sePrintingtName("Phi");
    nodes.push_back(phi);

    vector<vector<DfaNode*>> transitions;
    for (int i = 0; i < nodes.size(); ++i) {
        vector<DfaNode *> vec;
        transitions.push_back(vec);
    }

    for (int j = 0; j < alphabets.size(); ++j) {
        transitions[transitions.size() - 1].push_back(phi); // under any input phi goes to itself
    }

    for (int i = 0; i < transitions.size() - 1; i++) {
        for (int j = 0; j < alphabets.size(); j++) {
            char input = alphabets[j];
            if (nodes[i]->valid_transition(input)) {
                transitions[i].push_back(nodes[i]->do_transition(input));
            } else {
                transitions[i].push_back(phi);
            }
        }
    }
    vector<string> alphaStrings;
    for (int k = 0; k < alphabets.size(); ++k) {
        char c = alphabets[k];
        alphaStrings.push_back(string(1, c) + "-" + string(1, c));
    }

    vector<string> newInputs;
    vector<vector<DfaNode*>> newTransitions;

    minimizeTable(transitions, alphaStrings, &newInputs, &newTransitions);
    return TransitionTable(nodes, newInputs, newTransitions);
}

void TableBuilder::minimizeTable(vector<vector<DfaNode *>> transtions, vector<string> alphabets,
                                 vector<string> *newInputs, vector<vector<DfaNode *>> *newTransitions) {
    vector<int> removed;
    vector<vector<int>> depend;
    for (int i = 0; i < alphabets.size(); ++i) {
        vector<int> vec;
        depend.push_back(vec);
        if (find(removed.begin(), removed.end(), i) != removed.end()) break;
        for (int j = i + 1; j < alphabets.size(); ++j) {
            bool flag = true;
            for (int k = 0; k < transtions.size(); ++k) {
                if (transtions[k][i] != transtions[k][j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                depend[i].push_back(j);
                removed.push_back(j);
            }
        }
    }

    for (int i = 0; i < depend.size(); ++i) {
        string input = alphabets[i];
        for (int j = 0; j < depend[i].size(); ++j) {
            input = mergeInputs(input, alphabets[depend[i][j]]);
        }
        newInputs->push_back(input);
    }

    for (int i = 0; i < transtions.size() ; i++) {
        vector<DfaNode *> vec;
        newTransitions->push_back(vec);
        for (int j = 0; j < alphabets.size(); j++) {
            if (find(removed.begin(), removed.end(), j) != removed.end()) break;
            (*newTransitions)[i].push_back(transtions[i][j]);
        }
    }
}

string TableBuilder::mergeInputs(string s1, string s2) {
    char c2 = s2[0];
    if (c2 == (s1[s1.length() - 1] + 1)) {
        s1[s1.length() - 1] = c2;
    } else {
        s1 += s2;
    }
    return s1;
}
