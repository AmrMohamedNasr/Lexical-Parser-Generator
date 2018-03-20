//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NODE_H
#define COMPILERS_NODE_H

#include <string>
#include <vector>
#include <set>
#include "SupportingNfaNodes.h"
#include "Edge.h"

#define ACCEPT_STATE true
#define EPS '\0'

using namespace std;
//class SupportingNfaNodes;
class Edge;
class Node {
    private:
        string name;
        vector<Edge *> edges;
        vector<Edge *> dfaEdges;
        bool acceptedState;
		set<Node *> supportingNodes;
//		SupportingNfaNodes nfaNodes;
    public:
    	bool isAcceptedState();
    	void setAcceptState(bool newState);
    	string getName();
    	void setName(string name);
    	vector<Edge *> getEdges();
    	void addEdge(Edge * e);
		explicit Node(bool accept);
		Node(string stateName, bool accept);
    	void addDfaEdge(Edge * e);
//    	Node(string stateName, bool accept);
		void setSupportingNfaNodes(set<Node *> nodes);
		set<Node*> getSupportedNfaNodes();

	vector<Edge *> getDfaEdges();
};


#endif //COMPILERS_NODE_H
