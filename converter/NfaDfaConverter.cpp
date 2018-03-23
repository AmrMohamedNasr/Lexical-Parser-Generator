//
// Created by programajor on 3/16/18.
//

#include <set>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <climits>
#include "NfaDfaConverter.h"
#include <iostream>
#include "../models/DfaNodeWrapper.h"


using namespace std;

static int stateNameCounter = 1;

DfaNode *NfaDfaConverter::getNonMinimizedDFA(Node *combinedNfa, vector<string> *priorities) {
    DfaNodeWrapper* start = getDfaStartState(combinedNfa, priorities);
    start->setStart(true);

    set<DfaNodeWrapper*> dfaNodes;
    queue<DfaNodeWrapper*> nonMarkedNodes;

    dfaNodes.insert(start);
    nonMarkedNodes.push(start);

    while (!nonMarkedNodes.empty()) {
        DfaNodeWrapper* node = nonMarkedNodes.front();
        nonMarkedNodes.pop();

        // for every input symbol
        for (unsigned i = 0; i < node->getNfaEdges().size(); i++) {
            set<Node*> nextStates;
            if (node->getNfaEdges()[i]->is_eps_transition()) {
                continue;
            }
            char startChar = node->getNfaEdges()[i]->get_first_allowed_char();
            char lastChar = node->getNfaEdges()[i]->get_last_allowed_char();

            nextStates.insert(node->getNfaEdges()[i]->do_transition(startChar));
            for (unsigned j = i + 1; j < node->getNfaEdges().size(); j++) {
                Edge* e = node->getNfaEdges()[j];
                if (startChar >= e->get_first_allowed_char() && lastChar <= e->get_last_allowed_char()) {
                    nextStates.insert(node->getNfaEdges()[j]->do_transition(startChar));
                }
            }
            DfaNodeWrapper* newDfaNode = getEpslonClosureFromSet(&nextStates, priorities);
            DfaNodeWrapper* dfaRepresenter = setContainsState(&dfaNodes, newDfaNode);
            if (dfaRepresenter == NULL) {
                dfaNodes.insert(newDfaNode);
                nonMarkedNodes.push(newDfaNode);
                DfaEdge *edge = new DfaEdge(startChar, lastChar, node->getDfaNode(), newDfaNode->getDfaNode());
                node->addDfaEdge(edge);
            } else {
                DfaEdge *edge = new DfaEdge(startChar, lastChar, node->getDfaNode(), dfaRepresenter->getDfaNode());
                node->addDfaEdge(edge);
            }
        }
    }

    return removeRedundantEdges(start->getDfaNode());
}

DfaNodeWrapper* NfaDfaConverter::getDfaStartState(Node *combinedNfa, vector<string> *priorities) {
    set<Node *> nodes;
    nodes.insert(combinedNfa);
    return getEpslonClosureFromSet(&nodes, priorities);
}

DfaNodeWrapper* NfaDfaConverter::getEpslonClosureFromSet(set<Node *> *states, vector<string> *priorities) {
    set<Node*> initials;
    std::set<Node *>::iterator it;
    for (it = states->begin(); it != states->end(); it++) {
        Node* node = *it;
        set<Node*> s;
        getEpslonClosure(&s, node);
        std::set<Node *>::iterator iter;
        for (iter = s.begin(); iter != s.end(); iter++) {
            initials.insert(*iter);
        }
    }

    string stateName = getStateName(&initials, priorities);
    cout << stateName << endl;
    bool isAccepted = getIsAccepted(&initials);
    vector<Edge *> edges;
    getEdges(&edges, &initials);

    DfaNodeWrapper* wrapper = new DfaNodeWrapper();
    DfaNode* dfaNode = new DfaNode(stateName, isAccepted);
    wrapper->setDfaNode(dfaNode);
    wrapper->setNfaEdges(&edges);
    wrapper->setSupportingNfaNodes(&initials);
    return wrapper;
}

void NfaDfaConverter::getEpslonClosure(set<Node*> * closure, Node *node) {
    closure->insert(node);
    vector<Edge *> newEdges;
    stack<Node*> stack;
    stack.push(node);
    for (unsigned i = 0; i < node->getEdges().size(); i++) {
        if (!isFound(&newEdges, node->getEdges()[i])) {
            newEdges.push_back(node->getEdges()[i]);
        }
    }
    while (!stack.empty()) {
        Node* temp = stack.top();
        stack.pop();
        for (unsigned i = 0; i < temp->getEdges().size(); i++) {
            Edge* e = temp->getEdges()[i];
            if (e->is_eps_transition()) {
                Node *newState = e->do_transition('\0');
                closure->insert(newState);
                for (unsigned j = 0; j < newState->getEdges().size(); j++) {
                    if (!isFound(&newEdges, newState->getEdges()[j])) {
                        newEdges.push_back(newState->getEdges()[j]);
                    }
                }
                stack.push(newState);
            }
        }
    }
}

bool NfaDfaConverter::getIsAccepted(set<Node *> *states) {
    bool isAccepted = false;
    std::set<Node *>::iterator it;
    for (it = states->begin(); it != states->end(); it++) {
        Node* node = *it;
        isAccepted |= node->isAcceptedState();
    }
    return isAccepted;
}

string NfaDfaConverter::getStateName(set<Node *> *states, vector<string> *priorities) {
    unsigned priority = INT_MAX;
    string name = "";
    std::set<Node *>::iterator it;
    for (it = states->begin(); it != states->end(); it++) {
        Node* node = *it;
        if (node->isAcceptedState()) {
            for (unsigned i = 0; i < priorities->size(); i++) {
                if (node->getName() == (*priorities)[i] && i < priority) {
                    priority = i;
                    name = node->getName();
                }
            }
        }
    }
    if (name == "") {
        name = stateNameCounter + "";
        stateNameCounter++;
    }
    return name;
}

void NfaDfaConverter::getEdges(vector<Edge *> * edges, set<Node *> * states) {
    std::set<Node *>::iterator it;
    for (it = states->begin(); it != states->end(); it++) {
        Node* node = *it;
        for (unsigned i = 0; i < node->getEdges().size(); i++) {
            edges->push_back(node->getEdges()[i]);
        }
    }
}

DfaNodeWrapper* NfaDfaConverter::setContainsState(set<DfaNodeWrapper *> * states, DfaNodeWrapper *node) {
    std::set<DfaNodeWrapper *>::iterator it;
    for (it = states->begin(); it != states->end(); it++) {
        DfaNodeWrapper* curr = *it;
        if (representingSameNfa(node, curr)) {
            return curr;
        }
    }
    return NULL;
}

bool NfaDfaConverter::representingSameNfa(DfaNodeWrapper *n1, DfaNodeWrapper *n2) {
    set<Node*> s1 = n1->getSupportedNfaNodes();
    set<Node*> s2 = n2->getSupportedNfaNodes();

    if (s1.size() != s2.size()) {
        return false;
    }

    std::set<Node *>::iterator it;
    for (it = s1.begin(); it != s1.end(); it++) {
        Node* curr = *it;
        if (s2.find(curr) == s2.end()) {
            return false;
        }
    }
    return true;
}

bool NfaDfaConverter::isFound(vector<Edge *> *vector, Edge *&edge) {
    for (unsigned i = 0; i < vector->size(); ++i) {
        Edge* e = (*vector)[i];
        if (e->get_target_node() == edge->get_target_node() &&
                e->get_first_allowed_char() == edge->get_first_allowed_char() &&
                e->get_last_allowed_char() == edge->get_last_allowed_char()) {
            return true;
        }
    }
    return false;
}

DfaNode *NfaDfaConverter::removeRedundantEdges(DfaNode *node) {
    for (unsigned i = 0; i < node->getEdges().size(); i++) {
        DfaEdge* edge = node->getEdges()[i];
        for (unsigned j = i + 1; j < node->getEdges().size(); j++) {
            DfaEdge* curr = node->getEdges()[j];
            curr->disallow_character_sequence(edge->get_first_allowed_char(),
                                              edge->get_last_allowed_char());
        }
    }
    for (unsigned i = 0; i < node->getEdges().size(); i++) {
        DfaEdge* edge = node->getEdges()[i];
        DfaNode* next = edge->get_target_node();
        if (node != next) {
            edge->set_target_node(removeRedundantEdges(next));
        }
    }
    return node;
}

