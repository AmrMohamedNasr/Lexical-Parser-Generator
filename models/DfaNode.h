////
//// Created by programajor on 3/21/18.
////
//
//#ifndef COMPILERS_DFANODE_H
//#define COMPILERS_DFANODE_H
//
//#include "Node.h"
//
//class DfaEdge;
//class DfaNode {
//private:
//    string name;
//    vector<Edge *> edges;
//    vector<Edge *> dfaEdges;
//    bool acceptedState;
//    set<Node *> supportingNodes;
//public:
//    bool isAcceptedState();
//    void setAcceptState(bool newState);
//    string getName();
//    void setName(string name);
//    vector<Edge *> getEdges();
//    void addEdge(Edge * e);
//    explicit Node(bool accept);
//    Node(string stateName, bool accept);
//    void addDfaEdge(Edge * e);
//    void setSupportingNfaNodes(set<Node *> nodes);
//    set<Node*> getSupportedNfaNodes();
//    vector<Edge *> getDfaEdges();
//};
//
//#endif //COMPILERS_DFANODE_H
