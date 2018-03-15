//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NODE_H
#define COMPILERS_NODE_H

#include <string>
#include <vector>
#include "Edge.h"

using namespace std;

class Node {
    private:
        string name;
        vector<Edge> edges;
        bool isAcceptedState;
};


#endif //COMPILERS_NODE_H
