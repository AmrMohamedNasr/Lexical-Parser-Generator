//
// Created by programajor on 3/16/18.
//

#include "DfaMinimizer.h"
#include "../models/DfaNode.h"
#include <vector>
#include "../models/DfaEdge.h"
#include <utility>
#include <string.h>
#include <iostream>
#include <queue>





vector<DfaNode*> Closure:: getElements() {
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

bool Closure :: nodeExists(DfaNode *ele) {
	for (auto it = this->elements.begin(); it != this->elements.end(); it++) {
		  if ((*it) == ele) {
			  return true;
		  }
	}
	return false;
}

void Closure :: removeEle(DfaNode *ele) {
	for (int i = 0; i < this->elements.size(); i++) {
			  if (this->elements[i] == ele) {
				  this->elements.erase(this->elements.begin() +i);
				  return;
			  }
		}

}

void Closure :: addEle(DfaNode *ele) {
	this->elements.push_back(ele);
}

bool DfaMinimizer ::nodeExists(DfaNode *ele) {
	for (auto it = this->eles.begin(); it != this->eles.end(); it++) {
		  if ((*it) == ele) {
			  return true;
		  }
	}
	return false;
}


vector<DfaNode*>DfaMinimizer :: getMinimizedDFA(DfaNode *nonMinimizedDFA) {
	this->eles.clear();
	this->closures.clear();
	queue<DfaNode*> nodes;
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
				DfaNode* tempNode = this->closures[max -1]->getElements().back();
				Closure *temp = new Closure(this->closures[max -1]->getNumber());
				temp->addEle(tempNode);
				int flag = 0;
				for (int j = 0; j < this->closures[max -1]->getElements().size() - 1;j++) {
					DfaNode *tempNode2 = this->closures[max -1]->getElements()[j];
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
	vector<pair<int, DfaNode*>> qTransition;
	pair<int, DfaNode*> pStart = getNodeWithNum(nonMinimizedDFA);
	for (int i = 0; i < this->closures.size(); i++) {
		qTransition.push_back(
		pair<int, DfaNode*> (this->closures[i]->getNumber(),
				this->closures[i]->getElements()[0]));
	}
	for (int i = 0; i < qTransition.size(); i++) {
		for (int  j = 0; j < qTransition[i].second->getEdges().size(); j++) {
			if (getNumByNode(qTransition[i].second->getEdges(
					)[j]->get_target_node()) == qTransition[i].first) {
						qTransition[i].second->getEdges()[j]->set_target_node(
								qTransition[i].second);
			} else {
				int index = getNumByNode(qTransition[i].second->getEdges(
						)[j]->get_target_node()) - 1;
				qTransition[i].second->getEdges()[j]->set_target_node(
						qTransition[index].second);

			}
		}
	}
	vector<DfaNode*> lastNodes;
	lastNodes.push_back(qTransition[pStart.first - 1].second);
	for (int i = 0; i < qTransition.size(); i++) {
		if ((pStart.first - 1) != i)
			lastNodes.push_back(qTransition[i].second);
	}
	return lastNodes;

}

void DfaMinimizer :: addClosure(Closure* clo) {
	this->closures.push_back(clo);
}

bool DfaMinimizer :: removeClosure(Closure* clo) {
	for (auto it = this->closures.begin(); it != this->closures.end(); it++) {
				  if ((*it)->getNumber() == clo->getNumber()) {
					  this->closures.erase(it);
					  //delete *it;
					  return true;
				  }
			}
	return false;
}
bool DfaMinimizer :: checkSameTrans(DfaNode* ele1, DfaNode* ele2) {
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
void DfaMinimizer :: initTwoClosures(DfaNode *nonMinimizedDfa, Closure *clS, Closure *clF) {
	for (auto it = this->eles.begin(); it!= this->eles.end(); ++it) {
		if ((*it)->isAcceptedState()) {
			clF->addEle(*it);
		} else {
			clS->addEle(*it);
		}

	}
}

int  DfaMinimizer :: getNumByNode(DfaNode* node) {
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

pair<int, DfaNode*> DfaMinimizer:: getNodeWithNum(DfaNode * node) {
	int temp = getNumByNode(node);
	pair<int, DfaNode*> p(temp, node);
	return p;
}

