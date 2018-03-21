//
// Created by programajor on 3/16/18.
//

#include "DfaMinimizer.h"
#include "../models/Node.h"
#include <vector>
#include "../models/Edge.h"
#include <utility>
#include <string.h>
#include <iostream>
#include <queue>





vector<Node*> Closure:: getElements() {
	return this->elements;
}

int Closure:: getNumber() {
	return this->number;
}

void Closure :: setNumber(int number) {

}
Closure ::Closure(int number) {
	this->number = number;
	this->finished = false;
}

bool Closure :: nodeExists(Node *ele) {
	for (auto it = this->elements.begin(); it != this->elements.end(); it++) {
		  if ((*it)->getName().compare(ele->getName()) == 0) {
			  return true;
		  }
	}
	return false;
}

void Closure :: removeEle(Node *ele) {
	for (auto it = this->elements.begin(); it != this->elements.end(); it++) {
			  if ((*it)->getName().compare(ele->getName()) == 0) {
				  this->elements.erase(it);
				  return;
			  }
		}

}

void Closure :: addEle(Node *ele) {
	this->elements.push_back(ele);
}

bool DfaMinimizer ::nodeExists(Node *ele) {
	for (auto it = this->eles.begin(); it != this->eles.end(); it++) {
		  if ((*it)->getName().compare(ele->getName()) == 0) {
			  return true;
		  }
	}
	return false;
}


Node *DfaMinimizer :: getMinimizedDFA(Node *nonMinimizedDFA) {
	queue<Node*> nodes;
	nodes.push(nonMinimizedDFA);
	this->eles.push_back(nonMinimizedDFA);
	while (!nodes.empty()) {
		for (int j = 0; j < nodes.front()->getEdges().size(); ++j) {
			if (!nodeExists(nodes.front()->getEdges()[j]->get_target_node())) {
				nodes.push(nodes.front()->getEdges()[j]->get_target_node());
				//cout << "get out" << endl;
				this->eles.push_back(nodes.front()->getEdges()[j]->get_target_node());
			}
		}
		nodes.pop();
	}
	cout << "get out";
	int count = 1;
	Closure clS(count++);
	Closure clF(count++);
	this->getClosures().push_back(&clS);
	this->getClosures().push_back(&clF);
	initTwoClosures(nonMinimizedDFA, &clS, &clF);
	while (getNumOfUnfinishedClos() > 0) {
		vector<Closure*> nextClosures;
		for (auto it = this->getClosures().begin();
				it != this->getClosures().end(); ) {
			for (auto i = (*it)->getElements().begin();
					i != (*it)->getElements().end(); ) {
				(*it)->removeEle((*i));
				Closure temp(count++);
				temp.addEle((*i));
				int flag = 0;
				for (auto j = (*it)->getElements().begin();
						j != (*it)->getElements().end(); ) {
					if (checkSameTrans((*i), (*j))) {
						temp.addEle((*j));
						(*it)->removeEle((*j));
					} else {
						j++;
						flag = 1;
					}
				}
				if (flag == 1) {
					nextClosures.push_back(&temp);
				} else {
					temp.setFinished(true);
					this->addClosure(&temp);
				}
			}
			this->removeClosure((*it));
		}
		while (!nextClosures.empty()) {
			this->getClosures().push_back(nextClosures.back());
			nextClosures.pop_back();
		}
	}
	queue<pair<int, Node*>> qTransition;
	pair<int, Node*> pStart = getNodeWithNum(nonMinimizedDFA);
	vector<int> substituter;
	qTransition.push(pStart);
	while (!qTransition.empty()) {
		for (auto it = qTransition.front().second->getEdges().begin();
				it != qTransition.front().second->getEdges().end(); ++it) {
			if (getNumByNode((*it)->get_target_node()) == qTransition.front().first) {
				(*it)->set_target_node(qTransition.front().second);
			} else {
				pair<int, Node*> temp = getNodeWithNum((*it)->get_target_node());
				bool flag = true;
				for (int j : substituter) {
					if (j == temp.first) {
						flag = false;
					}
				}
				if (flag) {
					substituter.push_back(temp.first);
					qTransition.push(temp);
				}
			}
		}
		qTransition.pop();
	}
	return nonMinimizedDFA;

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
bool DfaMinimizer :: checkSameTrans(Node* ele1, Node* ele2) {
	for (auto i = ele1->getEdges().begin();
			i != ele1->getEdges().end(); ++i) {
		int flag = 0;
		for (auto j = ele2->getEdges().begin();
					j != ele2->getEdges().end(); ++j) {
				if ((*i)->equals((*j))) {
					if (getNumByNode(ele1) != getNumByNode(ele2)) {
						return false;
					}
					flag = 1;
				}
			}
		if (flag == 0) {
			return false;
		}
	}
	return true;
}
void DfaMinimizer :: initTwoClosures(Node *nonMinimizedDfa, Closure *clS, Closure *clF) {
	for (auto it = this->eles.begin(); it!= this->eles.end(); ++it) {
		if ((*it)->isAcceptedState()) {
			clF->addEle(*it);
		} else {
			clS->addEle(*it);
		}

	}
}

int  DfaMinimizer :: getNumByNode(Node* node) {
	for (auto i = this->closures.begin(); i != this->closures.end(); i++) {
		for (auto j = (*i)->getElements().begin(); j != (*i)->getElements().end(); j++) {
			if ((*j)->getName().compare(node->getName())) {
				return (*i)->getNumber();
			}
		}

	}
	// error TODO to be handled
	return 0;
}
vector<Closure*> DfaMinimizer ::  getClosures(){
	return this->closures;
}

int DfaMinimizer::getNumOfUnfinishedClos() {
	int count = 0;
	for (auto it = this->getClosures().begin(); it != this->getClosures().end(); it++) {
		if (!(*it)->isFinished()) {
			count++;
		}
	}
	return count;
}


bool Closure:: isFinished() {
	return this->finished;
}
void Closure::setFinished(bool finish) {
  this->finished = finish;
}

pair<int, Node*> DfaMinimizer:: getNodeWithNum(Node * node) {
	int temp = getNumByNode(node);
	pair<int, Node*> p(temp, node);
	return p;
}

