//
// Created by programajor on 3/23/18.
//

#include <iostream>
#include "TableWriter.h"

void TableWriter::writeTransitionTable(TransitionTable table, ostream stream) {
    vector<DfaNode *> nodes = table.getNodes();
    vector<string> input = table.getInputs();
    vector<vector<DfaNode *>> transitions = table.getTransitions();
    for (int i = 0; i < nodes.size() - 1; ++i) {
        nodes[i]->sePrintingtName("n" + std::to_string(i + 1));
    }
    nodes[nodes.size() - 1]->sePrintingtName("phi");

    for (int i = 0; i < ; ++i) {
        
    }
}
