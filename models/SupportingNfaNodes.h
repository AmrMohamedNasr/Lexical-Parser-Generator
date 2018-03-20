//
// Created by programajor on 3/20/18.
//

#ifndef COMPILERS_SUPPORTINGNFANODES_H
#define COMPILERS_SUPPORTINGNFANODES_H

#include <set>
#include "Node.h"

using namespace std;

class Node;
class SupportingNfaNodes {
private:
    set<Node *> nodes;

public:
    set<Node *> getSupportingNodes();
    void setSupportingNodes(set<Node *> nodes);
    SupportingNfaNodes(set<Node*> nodes);

    SupportingNfaNodes();
};


#endif //COMPILERS_SUPPORTINGNFANODES_H
