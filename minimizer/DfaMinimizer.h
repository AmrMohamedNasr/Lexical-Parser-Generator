//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_DFAMINIMIZER_H
#define COMPILERS_DFAMINIMIZER_H

#include <vector>
#include <string.h>
#include <utility>
#include "../models/Node.h"



class Closure {
	private:
		vector<Node*> elements;
		int number;
		bool finished;
	public:
		vector<Node*> getElements();
		int getNumber();
		bool isFinished();
		void setFinished(bool finish);
		void setNumber(int number);
		Closure(int number);
		bool nodeExists(Node *ele);
		void removeEle(Node *ele);
		void addEle(Node *ele);
};

class DfaMinimizer {

	private:
	    vector<Node*> eles;
		vector<Closure*> closures;
		vector<Closure*>  getClosures();
		void addClosure(Closure* clo);
		bool removeClosure(Closure* clo);
		bool checkSameTrans(Node* ele1, Node* ele2);
		void initTwoClosures(Node *nonMinimizedDfa, Closure *clS, Closure *clF);
		int getNumOfUnfinishedClos();
		int getNumByNode(Node* node);
		pair<int, Node*> getNodeWithNum(Node *);
		bool nodeExists(Node *node);
    public:
        /**
         * takes non minimized DFA from the converter and return it minimized.
         * @param nonMinimizedDFA the non minimized DFA from the converter
         * @return a minimized DFA from the given non minimized one.
         */
        Node *getMinimizedDFA(Node *nonMinimizedDFA);

};



#endif //COMPILERS_DFAMINIMIZER_H
