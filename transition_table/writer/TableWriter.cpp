//
// Created by programajor on 3/23/18.
//

#include <iostream>
#include "TableWriter.h"

void TableWriter::writeTransitionTableInHumanReadableFormat(TransitionTable table, ostream stream) {
    string toBeWritten = "";

    vector<DfaNode *> nodes = table.getNodes();
    vector<string> input = table.getInputs();
    vector<vector<DfaNode *>> transitions = table.getTransitions();
    for (int i = 0; i < nodes.size() - 1; ++i) {
        nodes[i]->sePrintingtName("n" + std::to_string(i + 1));
    }
    nodes[nodes.size() - 1]->sePrintingtName("phi");

    toBeWritten += "states\\input\t\t";
    for (int i = 0; i < input.size(); ++i) {
        toBeWritten += (input[i] + "\t");
    }
    toBeWritten += "isAccepted\tAcceptanceName\tisStart";
    for (int i = 0; i < transitions.size(); ++i) {
        toBeWritten += nodes[i]->getPrintingName() + "\t\t";
        for (int j = 0; j < input.size(); ++j) {
            toBeWritten += transitions[i][j]->getPrintingName() + "\t";
        }
        toBeWritten += nodes[i]->isAcceptedState() ? "YES\t" + nodes[i]->getName() + "\t" : "NO\tNONE\t";
        toBeWritten += nodes[i]->isStart() ? "YES" : "NO";
        toBeWritten += '\n';
    }

    stream << toBeWritten;
}

void TableWriter::writeTransitionTableInReadableForamt(TransitionTable table, ostream stream) {
    string toBeWritten = "";

    vector<DfaNode *> nodes = table.getNodes();
    vector<string> input = table.getInputs();
    vector<vector<DfaNode *>> transitions = table.getTransitions();
    for (int i = 0; i < nodes.size() - 1; ++i) {
        nodes[i]->sePrintingtName("n" + std::to_string(i + 1));
    }
    nodes[nodes.size() - 1]->sePrintingtName("phi");

    toBeWritten += std::to_string(nodes.size()) + "\n";
    for (int i = 0; i < nodes.size(); ++i) {
        toBeWritten += nodes[i]->isAcceptedState() ? "1 " : "0 ";
    }
    toBeWritten += "\n";

    for (int i = 0; i < nodes.size(); ++i) {
        toBeWritten += nodes[i]->isStart() ? "1 " : "0 ";
    }
    toBeWritten += "\n";

    for (int i = 0; i < nodes.size(); ++i) {
        toBeWritten += nodes[i]->getName() + "\n";
    }
    toBeWritten += "\n";

    toBeWritten += std::to_string(input.size()) + "\n";
    for (int i = 0; i < input.size(); ++i) {
        toBeWritten += input[i] + "\n";
    }
    toBeWritten += "\n";
    for (int i = 0; i < transitions.size(); ++i) {
        for (int j = 0; j < transitions[i].size(); ++j) {
            toBeWritten += transitions[i][j]->getPrintingName() + "\n";
        }
    }

}
