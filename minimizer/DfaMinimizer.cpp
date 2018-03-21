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
	this->number = number;
}
Closure ::Closure(int number) {
	this->number = number;
	this->finished = false;
}

bool Closure :: nodeExists(Node *ele) {
	for (auto it = this->elements.begin(); it != this->elements.end(); it++) {
		  if ((*it) == ele) {
			  return true;
		  }
	}
	return false;
}

void Closure :: removeEle(Node *ele) {
	for (int i = 0; i < this->elements.size(); i++) {
			  if (this->elements[i] == ele) {
				  this->elements.erase(this->elements.begin() +i);
				  return;
			  }
		}

}

void Closure :: addEle(Node *ele) {
	this->elements.push_back(ele);
}

bool DfaMinimizer ::nodeExists(Node *ele) {
	for (auto it = this->eles.begin(); it != this->eles.end(); it++) {
		  if ((*it) == ele) {
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
	int count = 1;
	Closure clS(count++);
	Closure clF(count++);
	this->closures.push_back(&clS);
	this->closures.push_back(&clF);
	initTwoClosures(nonMinimizedDFA, &clS, &clF);
	int counter = getNumOfUnfinishedClos();
	int max = 2;
	while ( counter > 0) {
		while (max > 0) {
			while (!this->closures[max -1]->getElements().empty()) {
				Node* tempNode = this->closures[max -1]->getElements().back();
				Closure *temp = new Closure(this->closures[max -1]->getNumber());
				temp->addEle(tempNode);
				int flag = 0;
				for (int j = 0; j < this->closures[max -1]->getElements().size() - 1;j++) {
					Node *tempNode2 = this->closures[max -1]->getElements()[j];
					if (checkSameTrans(tempNode, tempNode2)) {
						temp->addEle(tempNode2);
					} else {
						flag = 1;
					}
				}
				for (int i = 0; i < temp->getElements().size(); i++) {
					this->closures[max - 1]->removeEle(temp->getElements()[i]);
				}
				if (flag == 0) {
					temp->setFinished(true);
				}
				this->closures.push_back(temp);
			}
			this->removeClosure(this->closures[max -1]);
			max--;
		}
		for (int i = 0; i < this->closures.size(); i++) {
			this->closures[i]->setNumber(i+1);
		}
		counter = getNumOfUnfinishedClos();
		max = this->closures.size();

	}
	queue<pair<int, Node*>> qTransition;
	pair<int, Node*> pStart = getNodeWithNum(nonMinimizedDFA);
	vector<int> substituter;
	qTransition.push(pStart);
	substituter.push_back(pStart.first);
	while (!qTransition.empty()) {
		for (int  i = 0; i < qTransition.front().second->getEdges().size(); ++i) {
			if (getNumByNode(qTransition.front().second->getEdges(
					)[i]->get_target_node()) == qTransition.front().first) {
				qTransition.front().second->getEdges()[i]->set_target_node(qTransition.front().second);
			} else {
				pair<int, Node*> temp = getNodeWithNum(qTransition.front(
						).second->getEdges()[i]->get_target_node());
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
	this->closures.push_back(clo);
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
	if (ele1->getEdges().size() != ele2->getEdges().size()) {
		return false;
	}
	for (int i = 0; i < ele1->getEdges().size(); ++i) {
		int flag = 0;
		for (int j = 0; j < ele2->getEdges().size(); ++j) {
				if (ele1->getEdges()[i]->equals(ele2->getEdges()[j])) {
					if (getNumByNode(ele1->getEdges()[i]->get_target_node()) ==
							getNumByNode(ele2->getEdges()[j]->get_target_node())) {
						flag = 1;
					}

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
	for (int i = 0; i != this->closures.size(); i++) {
		for (int j = 0 ; j < this->closures[i]->getElements().size(); j++) {
			if (this->closures[i]->getElements()[j] == node ) {
				return this->closures[i]->getNumber();
			}
		}

	}
	cout << "error"<< endl;
	// error TODO to be handled
	return 0;
}
vector<Closure*> DfaMinimizer ::  getClosures(){
	return this->closures;
}

int DfaMinimizer::getNumOfUnfinishedClos() {
	int count = 0;
	for (int i = 0; i < this->closures.size(); i++) {
		if (!this->closures[i]->isFinished()) {
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

