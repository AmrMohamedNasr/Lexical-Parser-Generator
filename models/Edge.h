//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_EDGE_H
#define COMPILERS_EDGE_H

#include <string>
#include <vector>
#include "Node.h"
using namespace std;
class Node;
class Edge {
    private:
        char first_allowed_char;
        char last_allowed_char;
        Node* target_node;
        int allowing_range;
        vector<char> disallowed_chars;
    public:
        Node * do_transition(char c);
        Node * getTargetNode();
        bool is_eps_transition(void);
        bool valid_transition(char c);
        void disallow_character(char c);
        int getAllowedRange();
        char getFirstAllowedCharacter();
        char getLastAllowedCharacter();
        Edge(char start, char end, Node *target);
};


#endif //COMPILERS_EDGE_H
