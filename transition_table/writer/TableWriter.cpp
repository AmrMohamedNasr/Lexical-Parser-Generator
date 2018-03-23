//
// Created by programajor on 3/23/18.
//

#include <iostream>
#include "TableWriter.h"

void TableWriter::writeTransitionTableInHumanReadableFormat(TransitionTable table, ostream* stream) {
    vector<DfaNode *> nodes = table.getNodes();
    vector<string> input = table.getInputs();
    vector<vector<DfaNode *>> transitions = table.getTransitions();
    for (int i = 0; i < nodes.size() - 1; ++i) {
        nodes[i]->sePrintingtName("n" + std::to_string(i + 1));
    }
    nodes[nodes.size() - 1]->sePrintingtName("phi");

    *stream << "states\\input\t\t";
    for (int i = 0; i < input.size(); ++i) {
        *stream << (input[i] + "\t");
    }
    *stream << "isAccepted\tAcceptanceName\tisStart\n";
    for (int i = 0; i < transitions.size(); ++i) {
        *stream << nodes[i]->getPrintingName() + "\t\t";
        for (int j = 0; j < input.size(); ++j) {
            *stream << transitions[i][j]->getPrintingName() + "\t";
        }
        if (nodes[i]->isAcceptedState() ) {
            *stream << "YES\t" + nodes[i]->getName() + "\t";
        } else {
            *stream << "NO\tNONE\t";
        }
        if (nodes[i]->isStart() ) {
            *stream << "YES";
        } else {
            *stream << "NO";
        }
        *stream << '\n';
    }
}

void TableWriter::writeTransitionTableInReadableForamt(TransitionTable table, ostream* stream) {
    vector<DfaNode *> nodes = table.getNodes();
    vector<string> input = table.getInputs();
    vector<vector<DfaNode *>> transitions = table.getTransitions();
    for (int i = 0; i < nodes.size() - 1; ++i) {
        nodes[i]->sePrintingtName("n" + std::to_string(i + 1));
    }
    nodes[nodes.size() - 1]->sePrintingtName("phi");

    *stream << std::to_string(nodes.size()) + "\n";
    for (int i = 0; i < nodes.size(); ++i) {
        *stream << nodes[i]->isAcceptedState() ? "1 " : "0 ";
    }
    *stream << "\n";

    for (int i = 0; i < nodes.size(); ++i) {
        *stream << nodes[i]->isStart() ? "1 " : "0 ";
    }
    *stream << "\n";

    for (int i = 0; i < nodes.size(); ++i) {
        *stream << nodes[i]->getName() + "\n";
    }

    *stream << std::to_string(input.size()) + "\n";
    for (int i = 0; i < input.size(); ++i) {
        *stream << input[i] + "\n";
    }

    for (int i = 0; i < transitions.size(); ++i) {
        for (int j = 0; j < transitions[i].size(); ++j) {
            *stream << transitions[i][j]->getPrintingName() + "\n";
        }
    }
}
