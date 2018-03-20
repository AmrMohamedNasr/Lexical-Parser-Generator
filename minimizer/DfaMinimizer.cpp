//
// Created by programajor on 3/16/18.
//

#include "DfaMinimizer.h"
#include "../models/Node.h"
#include <vector>
#include "../models/Edge.h"
#include <string.h>
#include <queue>

bool Element::isStart() {
	return this->start;
}

Node * Element::getNode() {
	return this->node;
}



Element::Element(Node *node, bool start) {
	this->node = node;
	this->start = start;
}

vector<Element*> Closure:: getElements() {
	return this->elements;
}

int Closure:: getNumber() {
	return this->number;
}

void Closure :: setNumber(int number) {

}
Closure ::Closure(int number) {
	this->number = number;
}

bool Closure :: nodeExists(Element *ele) {
	for (auto it = this->elements.begin(); it != this->elements.end(); it++) {
		  if ((*it)->getNode()->getName().compare(ele->getNode()->getName()) == 0) {
			  return true;
		  }
	}
	return false;
}

void Closure :: removeEle(Element *ele) {
	for (auto it = this->elements.begin(); it != this->elements.end(); it++) {
			  if ((*it)->getNode()->getName().compare(ele->getNode()->getName()) == 0) {
				  this->elements.erase(it);
				  return;
			  }
		}

}
void Closure :: addEle(Element *ele) {
	this->elements.push_back(ele);
}



Node *DfaMinimizer :: getMinimizedDFA(Node *nonMinimizedDFA) {
	queue<Node*> nodes;
	nodes.push(nonMinimizedDFA);
	int flag = 0;
	Element ele(&nodes.front(), true);
	this->eles.push_back(&ele);
	while (!nodes.empty()) {
		if (flag != 0) {
			Element ele(&nodes.front(), false);
			this->eles.push_back(&ele);
		}
		flag = 1;
		for (auto j = nodes.front()->getEdges().begin();
				j != nodes.front()->getEdges().end(); ++j) {
			nodes.push((*j)->target_node);
		}
		nodes.pop();
	}
}

void DfaMinimizer :: addClosure(Closure* clo) {
	this->getClosures().push_back(clo);
}

bool DfaMinimizer :: removeClosure(Closure* clo) {
	for (auto it = this->closures.begin(); it != this->closures.end(); it++) {
				  if ((*it)->getNumber() == clo->getNumber()) {
					  this->closures.erase(it);
					  return true;
				  }
			}
	return false;
}
bool DfaMinimizer :: checkSameTrans(Element* ele1, Element* ele2) {
	for (auto i = ele1->getNode()->getEdges().begin();
			i != ele1->getNode()->getEdges().end(); ++i) {
		for (auto j = ele2->getNode()->getEdges().begin();
					j != ele2->getNode()->getEdges().end(); ++j) {

			}
	}
}
void DfaMinimizer :: initTwoClosures(Node *nonMinimizedDfa, Closure *clS, Closure *clF) {
	for (auto it = this->eles.begin(); it!= this->eles.end(); ++it) {
		if ((*it)->getNode()->isAcceptedState()) {
			clF->addEle(*it);
		} else {
			clS->addEle(*it);
		}

	}
}
int  DfaMinimizer :: getNumByEle(Element* ele) {
	for (auto i = this->closures.begin(); i != this->closures.end(); i++) {
		for (auto j = (*i)->getElements().begin(); j != (*i)->getElements().end(); j++) {
			if ((*j)->getNode()->getName().compare(ele->getNode()->getName())) {
				return (*i)->getNumber();
			}
		}

	}
	return 0;
}

