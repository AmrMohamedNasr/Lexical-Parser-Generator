//
// Created by programajor on 3/22/18.
//

#include "TransTablePrinter.h"
#include "../models/DfaEdge.h"

void TransTablePrinter::printTransitionTable(vector<DfaNode *> nodes) {
    for (int i = 0; i < nodes.size(); i++) {
        DfaNode* node = nodes[i];
        breakDownEdgesInOtherNodes(node, nodes);
    }
}

void TransTablePrinter::breakDownEdgesInOtherNodes(DfaNode *node, vector<DfaNode *> otherNodes) {
    for (int i = 0; i < node->getEdges().size(); i++) {
        DfaEdge* edge = node->getEdges()[i];
        for (int j = 0; j < otherNodes.size(); j++) {
            DfaNode* otherNode = otherNodes[j];
            if (node != otherNode) {
                for (int k = 0; k < otherNode->getEdges().size(); k++) {
                    DfaEdge* otherEdge = otherNode->getEdges()[k];
                    minimizeEdges(edge, otherEdge);
                }
            }
        }
    }
}

void TransTablePrinter::minimizeEdges(DfaEdge *e1, DfaEdge *e2) {
//    char s1 = e1->get_first_allowed_char();
//    char t1 = e1->get_last_allowed_char();
//    char s2 = e2->get_first_allowed_char();
//    char t2 = e2->get_last_allowed_char();
//
//    if (s1 > s2 && t1 < t2) {
//
//    } else if (s1 < s2 && t1 > t2) {
//
//    } else if () {
//
//    } else if () {
//
//    } else if () {
//
//    } else if () {
//
//    } else if () {
//
//    } else if () {
//
//    }
}
