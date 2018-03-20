//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_DFAMINIMIZER_H
#define COMPILERS_DFAMINIMIZER_H

#include <vector>
#include <string.h>
#include "../models/Node.h"

class Element {
	private:
		Node *node;
		bool start;
	public:
		Node *getNode();
		bool isStart();
		Element(Node *node, bool start);
};

class Closure {
	private:
		vector<Element*> elements;
		int number;

	public:
		vector<Element*> getElements();
		int getNumber();
		void setNumber(int number);
		Closure(int number);
		bool nodeExists(Element *ele);
		void removeEle(Element *ele);
		void addEle(Element *ele);
};

class DfaMinimizer {

	private:
	    vector<Element*> eles;
		vector<Closure*> closures;
		vector<Closure*>  getClosures();
		void addClosure(Closure* clo);
		bool removeClosure(Closure* clo);
		bool checkSameTrans(Element* ele1, Element* ele2);
		void initTwoClosures(Node *nonMinimizedDfa, Closure *clS, Closure *clF);
		int getNumByEle(Element* ele);
    public:
        /**
         * takes non minimized DFA from the converter and return it minimized.
         * @param nonMinimizedDFA the non minimized DFA from the converter
         * @return a minimized DFA from the given non minimized one.
         */
        Node *getMinimizedDFA(Node *nonMinimizedDFA);

};



#endif //COMPILERS_DFAMINIMIZER_H
