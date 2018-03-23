//
// Created by programajor on 3/23/18.
//

#include <algorithm>
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

    for (int i = 0; i < transitions.size(); i++) {
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
        alphaStrings.push_back(alphabets[k] + "-" + alphabets[k]);
    }
    minimizeTable(transitions, alphaStrings);
    return TransotionTable();
}

void TableBuilder::minimizeTable(vector<vector<DfaNode *>> transtions, vector<string> alphabets) {
    vector<int> removed;
    vector<vector<int>> depend;
    vector<string> newInputs;
    for (int i = 0; i < alphabets.size(); ++i) {
        vector<int> vec;
        depend.push_back(vec);
        if (find(removed.begin(), removed.end(), i) != removed.end()) break;
        for (int j = i + 1; j < alphabets.size(); ++j) {
            bool flag = true;
            for (int k = 0; k < transtions.size() - 1; ++k) {
                if (transtions[k][i] != transtions[k][j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                depend[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < depend.size(); ++i) {
        string input = alphabets[i];
        for (int j = 0; j < depend[i].size(); ++j) {
//            input = mergeInputs(input, alphabets[depend[i][j]]);
        }
        newInputs.push_back(input);
    }
}

string mergeInputs(string s1, string s2) {

}
