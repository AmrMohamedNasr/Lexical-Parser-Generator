//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NODE_H
#define COMPILERS_NODE_H

#include <string>
#include <vector>

#define ACCEPT_STATE true
#define EPS '\0'

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
    	void setName(string name);
    	vector<Edge *> getEdges();
    	void addEdge(Edge * e);
		explicit Node(bool accept);
		Node(string stateName, bool accept);
};


#endif //COMPILERS_NODE_H
