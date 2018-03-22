//
// Created by programajor on 3/22/18.
//

#ifndef COMPILERS_TRANSTABLEPRINTER_H
#define COMPILERS_TRANSTABLEPRINTER_H


#include "../models/DfaNode.h"

class TransTablePrinter {
public:
    void printTransitionTable(vector <DfaNode*> nodes);

    void breakDownEdgesInOtherNodes(DfaNode *pNode, vector<DfaNode *> vector);

    void minimizeEdges(DfaEdge *e1, DfaEdge *e2);
};


#endif //COMPILERS_TRANSTABLEPRINTER_H
