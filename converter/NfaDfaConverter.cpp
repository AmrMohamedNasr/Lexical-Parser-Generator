//
// Created by programajor on 3/16/18.
//

#include <set>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include "NfaDfaConverter.h"

struct smallerRangeKey {
    inline bool operator() (Edge* e1, Edge* e2) {
        if(e1 != NULL && e2 != NULL) {
            int a = e1->getAllowedRange();
            int b = e2->getAllowedRange();
            return (a < b);
        } else {
            return 0;
        }
    }
};

Node *NfaDfaConverter::getNonMinimizedDFA(Node *combinedNfa) {
    Node *start = getDfaStartState(combinedNfa);

    set<Node*> dfaNodes;
    queue<Node*> nonMarkedNodes;
    dfaNodes.insert(start);
    nonMarkedNodes.push(start);

    while (!nonMarkedNodes.empty()) {
        Node* node = nonMarkedNodes.front();
        nonMarkedNodes.pop();
//        sort(node->getEdges().begin(), node->getEdges().end(), smallerRangeKey());

        // for every input symbol
        for (int i = 0; i < node->getEdges().size(); i++) {
            set<Node*> nextStates;
            if (node->getEdges()[i]->is_eps_transition()) {
                continue;
            }
            char startChar = node->getEdges()[i]->getFirstAllowedCharacter();
            char lastChar = node->getEdges()[i]->getLastAllowedCharacter();
            nextStates.insert(node->getEdges()[i]->do_transition(startChar));
            for (int j = i + 1; j < node->getEdges().size(); j++) {
                Edge* e = node->getEdges()[j];
                if (startChar >= e->getFirstAllowedCharacter() &&
                        lastChar <= e->getLastAllowedCharacter()) {
                    nextStates.insert(node->getEdges()[j]->do_transition(startChar));
                }
            }
            Node* newDfaNode = getEpslonClosureFromSet(nextStates);
            if (!setContainsState(dfaNodes, newDfaNode)) {
                dfaNodes.insert(newDfaNode);
                nonMarkedNodes.push(newDfaNode);
            }
            Edge *edge = (Edge*) malloc(sizeof (Edge));
            new (edge) Edge(startChar, lastChar, newDfaNode);
            node->addDfaEdge(edge);
        }
    }
    return start;
}

Node* NfaDfaConverter::getDfaStartState(Node *combinedNfa) {
    set<Node *> nodes;
    nodes.insert(combinedNfa);
    return getEpslonClosureFromSet(nodes);
}

Node * NfaDfaConverter::getEpslonClosureFromSet(set<Node *> states) {
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
    Node* node = (Node*) malloc(sizeof (Node));
    new (node) Node(stateName, isAccepted);
    vector<Edge *> edges = getEdges(initials);
    for (int i = 0; i < edges.size(); ++i) {
        node->addEdge(edges[i]);
    }
    node->setSupportingNfaNodes(initials);
    return node;
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
            break;
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

bool NfaDfaConverter::setContainsState(set<Node *> states, Node *node) {
    std::set<Node *>::iterator it;
    for (it = states.begin(); it != states.end(); it++) {
        Node* curr = *it;
        if (representingSameNfa(node, curr)) {
            return true;
        }
    }
    return false;
}

bool NfaDfaConverter::representingSameNfa(Node *n1, Node *n2) {
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
        if (e->getTargetNode() == edge->getTargetNode() &&
                e->getFirstAllowedCharacter() == edge->getFirstAllowedCharacter() &&
                e->getLastAllowedCharacter() == edge->getLastAllowedCharacter()) {
            return true;
        }
    }
    return false;
}

