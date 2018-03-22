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
};


#endif //COMPILERS_TABLEBUILDER_H
