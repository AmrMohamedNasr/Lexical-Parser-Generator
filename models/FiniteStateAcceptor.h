//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_FINITESTATEACCEPTOR_H
#define COMPILERS_FINITESTATEACCEPTOR_H


#include <map>
#include "Node.h"

class FiniteStateAcceptor {
    private:
        vector<Node> startNodes;
        map<string, Node> map;
};


#endif //COMPILERS_FINITESTATEACCEPTOR_H
