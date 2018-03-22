//
// Created by programajor on 3/16/18.
//

#include <set>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include "NfaDfaConverter.h"
#include "../models/DfaNodeWrapper.h"

DfaNode *NfaDfaConverter::getNonMinimizedDFA(Node *combinedNfa) {
    DfaNodeWrapper* start = getDfaStartState(combinedNfa);

    set<DfaNodeWrapper*> dfaNodes;
    queue<DfaNodeWrapper*> nonMarkedNodes;

    dfaNodes.insert(start);
    nonMarkedNodes.push(start);

    while (!nonMarkedNodes.empty()) {
        DfaNodeWrapper* node = nonMarkedNodes.front();
        nonMarkedNodes.pop();

        // for every input symbol
        for (int i = 0; i < node->getNfaEdges().size(); i++) {
            set<Node*> nextStates;
            if (node->getNfaEdges()[i]->is_eps_transition()) {
                continue;
            }
            char startChar = node->getNfaEdges()[i]->get_first_allowed_char();
            char lastChar = node->getNfaEdges()[i]->get_last_allowed_char();

            nextStates.insert(node->getNfaEdges()[i]->do_transition(startChar));
            for (int j = i + 1; j < node->getNfaEdges().size(); j++) {
                Edge* e = node->getNfaEdges()[j];
                if (startChar >= e->get_first_allowed_char() && lastChar <= e->get_last_allowed_char()) {
                    nextStates.insert(node->getNfaEdges()[j]->do_transition(startChar));
                }
            }
            DfaNodeWrapper* newDfaNode = getEpslonClosureFromSet(nextStates);
            DfaNodeWrapper* dfaRepresenter = setContainsState(dfaNodes, newDfaNode);
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

DfaNodeWrapper* NfaDfaConverter::getDfaStartState(Node *combinedNfa) {
    set<Node *> nodes;
    nodes.insert(combinedNfa);
    return getEpslonClosureFromSet(nodes);
}

DfaNodeWrapper* NfaDfaConverter::getEpslonClosureFromSet(set<Node *> states) {
    set<Node*> initials;
    std::set<Node *>::iterator it;
    for (it = states.begin(); it != states.end(); it++) {
        Node* node = *it;
        set<Node*> s = getEpslonClosure(node);
        std::set<Node *>::iterator iter;
        for (iter = s.begin(); iter != s.end(); iter++) {
            initials.insert(*iter);
        }
    }

    string stateName = getStateName(initials);
    bool isAccepted = getIsAccepted(initials);
    vector<Edge *> edges = getEdges(initials);

    DfaNodeWrapper* wrapper = new DfaNodeWrapper();
    DfaNode* dfaNode = new DfaNode(stateName, isAccepted);
//    Node* node = new Node(stateName, isAccepted);
//    for (int i = 0; i < edges.size(); ++i) {
//        node->addEdge(edges[i]);
//    }
    wrapper->setDfaNode(dfaNode);
    wrapper->setNfaEdges(edges);
    wrapper->setSupportingNfaNodes(initials);
//    node->setSupportingNfaNodes(initials);
    return wrapper;
}

set<Node*> NfaDfaConverter::getEpslonClosure(Node *node) {
    set<Node*> closure;
    closure.insert(node);
    vector<Edge *> newEdges;
    stack<Node*> stack;
    stack.push(node);
    for (int i = 0; i < node->getEdges().size(); i++) {
        if (!isFound(newEdges, node->getEdges()[i])) {
            newEdges.push_back(node->getEdges()[i]);
        }
    }
    while (!stack.empty()) {
        Node* temp = stack.top();
        stack.pop();
        for (int i = 0; i < temp->getEdges().size(); i++) {
            Edge* e = temp->getEdges()[i];
            if (e->is_eps_transition()) {
                Node *newState = e->do_transition('\0');
                closure.insert(newState);
                for (int j = 0; j < newState->getEdges().size(); j++) {
                    if (!isFound(newEdges, newState->getEdges()[j])) {
                        newEdges.push_back(newState->getEdges()[j]);
                    }
                }
                stack.push(newState);
            }
        }
    }
    return closure;
}

bool NfaDfaConverter::getIsAccepted(set<Node *> states) {
    bool isAccepted = false;
    std::set<Node *>::iterator it;
    for (it = states.begin(); it != states.end(); it++) {
        Node* node = *it;
        isAccepted |= node->isAcceptedState();
    }
    return isAccepted;
}

string NfaDfaConverter::getStateName(set<Node *> states) {
    string name = "";
    std::set<Node *>::iterator it;
    for (it = states.begin(); it != states.end(); it++) {
        Node* node = *it;
        name += node->getName() + ",";
        if (node->isAcceptedState()) {
            return node->getName();
        }
    }
    return name;
}

vector<Edge *> NfaDfaConverter::getEdges(set<Node *> states) {
    vector <Edge* > edges;
    std::set<Node *>::iterator it;
    for (it = states.begin(); it != states.end(); it++) {
        Node* node = *it;
        for (int i = 0; i < node->getEdges().size(); i++) {
            edges.push_back(node->getEdges()[i]);
        }
    }
    return edges;
}

DfaNodeWrapper* NfaDfaConverter::setContainsState(set<DfaNodeWrapper *> states, DfaNodeWrapper *node) {
    std::set<DfaNodeWrapper *>::iterator it;
    for (it = states.begin(); it != states.end(); it++) {
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

bool NfaDfaConverter::isFound(vector<Edge *> vector, Edge *&edge) {
    for (int i = 0; i < vector.size(); ++i) {
        Edge* e = vector[i];
        if (e->get_target_node() == edge->get_target_node() &&
                e->get_first_allowed_char() == edge->get_first_allowed_char() &&
                e->get_last_allowed_char() == edge->get_last_allowed_char()) {
            return true;
        }
    }
    return false;
}

DfaNode *NfaDfaConverter::removeRedundantEdges(DfaNode *node) {
    for (int i = 0; i < node->getEdges().size(); i++) {
        DfaEdge* edge = node->getEdges()[i];
        for (int j = i + 1; j < node->getEdges().size(); j++) {
            DfaEdge* curr = node->getEdges()[j];
            curr->disallow_character_sequence(edge->get_first_allowed_char(),
                                              edge->get_last_allowed_char());
        }
    }
    for (int i = 0; i < node->getEdges().size(); i++) {
        DfaEdge* edge = node->getEdges()[i];
        DfaNode* next = edge->get_target_node();
        if (node != next) {
            edge->set_target_node(removeRedundantEdges(next));
        }
    }
    return node;
}

