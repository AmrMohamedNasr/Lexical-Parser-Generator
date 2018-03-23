//
// Created by programajor on 3/23/18.
//

#ifndef COMPILERS_TABLEBUILDER_H
#define COMPILERS_TABLEBUILDER_H

#include "../model/TransitionTable.h"
#include "../../models/DfaNode.h"

class TableBuilder {
public:
    TransotionTable buildTransitionTable(vector<DfaNode *> nodes, vector <char> alphabets);

    void minimizeTable(vector<vector<DfaNode *>> nodes, vector <string> alphabets);

private:
    string mergeInputs(string s1, string s2);
};


#endif //COMPILERS_TABLEBUILDER_H
