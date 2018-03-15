//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_EDGE_H
#define COMPILERS_EDGE_H

#include <string>
#include "Node.h"

using namespace std;

class Edge {
    private:
        string transition;
        Node* start;
        Node* end;

    public:
        string getTransition() { return transition; }

        Node* getStart() { return start; }

        Node* getEnd() { return end; }
};


#endif //COMPILERS_EDGE_H
