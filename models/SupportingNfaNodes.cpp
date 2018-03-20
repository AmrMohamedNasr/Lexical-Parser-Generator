//
// Created by programajor on 3/20/18.
//

#include "SupportingNfaNodes.h"

SupportingNfaNodes::SupportingNfaNodes(set<Node *> nodes) {
    this->nodes = nodes;
}

set<Node *> SupportingNfaNodes::getSupportingNodes() {
    return this->nodes;
}

void SupportingNfaNodes::setSupportingNodes(set<Node *> nodes) {
    this->nodes = nodes;
}

SupportingNfaNodes::SupportingNfaNodes() {

}
