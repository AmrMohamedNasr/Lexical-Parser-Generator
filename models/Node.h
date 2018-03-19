//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NODE_H
#define COMPILERS_NODE_H

#include <string>
#include <vector>

using namespace std;
class Edge;
class Node {
    private:
        string name;
        vector<Edge *> edges;
        bool acceptedState;
    public:
    	bool isAcceptedState();
    	void setAcceptState(bool newState);
    	string getName();
    	vector<Edge *> getEdges();
    	void addEdge(Edge * e);
    	Node(string stateName, bool accept);
};


#endif //COMPILERS_NODE_H
