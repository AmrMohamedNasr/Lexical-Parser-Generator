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
#include <algorithm>
#include <queue>

vector<DfaNode*> PartitionSet:: getElements() {
	return this->elements;
}

int PartitionSet:: getNumber() {
	return this->number;
}

void PartitionSet :: setNumber(int number) {
	this->number = number;
}
PartitionSet ::PartitionSet(int number) {
	this->number = number;
	this->finished = false;
}

bool PartitionSet :: nodeExists(DfaNode *ele) {
	for (auto it = this->elements.begin(); it != this->elements.end(); it++) {
		  if ((*it) == ele) {
			  return true;
		  }
	}
	return false;
}

void PartitionSet :: removeEle(DfaNode *ele) {
	for (unsigned i = 0; i < this->elements.size(); i++) {
			  if (this->elements[i] == ele) {
				  this->elements.erase(this->elements.begin() +i);
				  return;
			  }
		}

}

void PartitionSet :: addEle(DfaNode *ele) {
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


//bool compareEdges (const DfaEdge * lhs, const DfaEdge * rhs) {
//	if (lhs->allowing_range != rhs->allowing_range) {
//		return lhs->allowing_range < rhs->allowing_range;
//	}
//	for (unsigned i = 0; i < lhs->disallowed_chars.size(); i++) {
//			if (lhs->disallowed_chars[i] != rhs->disallowed_chars[i]) {
//				return lhs->disallowed_chars[i] > rhs->disallowed_chars[i];
//			}
//	}
//	if (lhs->first_allowed_char != rhs->first_allowed_char) {
//		return lhs->first_allowed_char < rhs->first_allowed_char;
//	}
//	if (lhs->last_allowed_char != rhs->last_allowed_char) {
//		return lhs->last_allowed_char > rhs->last_allowed_char;
//	}
//	return true;
//}

void DfaMinimizer :: getMinimizedDFA(vector<DfaNode*> * finalMachine, DfaNode *nonMinimizedDFA) {
	this->eles.clear();
	this->partitionSets.clear();
	queue<DfaNode*> nodes;
	nodes.push(nonMinimizedDFA);
	this->eles.push_back(nonMinimizedDFA);
	while (!nodes.empty()) {
		for (unsigned j = 0; j < nodes.front()->getEdges().size(); ++j) {
			if (!nodeExists(nodes.front()->getEdges()[j]->get_target_node())) {
				nodes.push(nodes.front()->getEdges()[j]->get_target_node());
				this->eles.push_back(nodes.front()->getEdges()[j]->get_target_node());
			}
		}
		nodes.pop();
	}
//	for(unsigned i = 0; i < this->eles.size(); i++) {
//		sort(this->eles[i]->getEdges().begin(),
//				this->eles[i]->getEdges().end(), compareEdges);
//	}
	int count = 1;
	PartitionSet *setS = new PartitionSet(count++);
	PartitionSet *setF = new PartitionSet(count++);
	this->partitionSets.push_back(setS);
	this->partitionSets.push_back(setF);
	initTwoSets(nonMinimizedDFA, setS, setF);
	int counter = getNumOfUnfinishedSet();
	int max = 2;
	while ( counter > 0) {
		while (max > 0) {
			while (!this->partitionSets[max -1]->getElements().empty()) {
				DfaNode* tempNode = this->partitionSets[max -1]->getElements().back();
				PartitionSet *temp = new PartitionSet(this->partitionSets[max -1]->getNumber());
				temp->addEle(tempNode);
				int flag = 0;
				for (unsigned j = 0; j < this->partitionSets[max -1]->getElements().size() - 1;j++) {
					DfaNode *tempNode2 = this->partitionSets[max -1]->getElements()[j];
					if (checkSameTrans(tempNode, tempNode2)) {
						temp->addEle(tempNode2);
					} else {
						flag = 1;
					}
				}
				for (unsigned i = 0; i < temp->getElements().size(); i++) {
					this->partitionSets[max - 1]->removeEle(temp->getElements()[i]);
				}
				if (flag == 0) {
					temp->setFinished(true);
				}
				this->partitionSets.push_back(temp);
			}
			this->removeSet(this->partitionSets[max -1]);
			max--;
		}
		for (unsigned i = 0; i < this->partitionSets.size(); i++) {
			this->partitionSets[i]->setNumber(i+1);
		}
		counter = getNumOfUnfinishedSet();
		max = this->partitionSets.size();

	}
	vector<pair<int, DfaNode*>> qTransition;
	pair<int, DfaNode*> pStart = getNodeWithNum(nonMinimizedDFA);
	for (unsigned i = 0; i < this->partitionSets.size(); i++) {
		qTransition.push_back(
		pair<int, DfaNode*> (this->partitionSets[i]->getNumber(),
				this->partitionSets[i]->getElements()[0]));
		for (unsigned j = 1; j < this->partitionSets[i]->getElements().size(); j++) {
			delete this->partitionSets[i]->getElements()[j];
		}
	}
	for (unsigned i = 0; i < qTransition.size(); i++) {
		for (unsigned  j = 0; j < qTransition[i].second->getEdges().size(); j++) {
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
	finalMachine->push_back(qTransition[pStart.first - 1].second);
	for (int i = 0; (unsigned)i < qTransition.size(); i++) {
		if ((pStart.first - 1) != i)
			finalMachine->push_back(qTransition[i].second);
	}
}

void DfaMinimizer :: addSet(PartitionSet* clo) {
	this->partitionSets.push_back(clo);
}

bool DfaMinimizer :: removeSet(PartitionSet* clo) {
	for (auto it = this->partitionSets.begin(); it != this->partitionSets.end(); it++) {
				  if ((*it)->getNumber() == clo->getNumber()) {
					  this->partitionSets.erase(it);
					  return true;
				  }
			}
	return false;
}
bool DfaMinimizer :: checkSameTrans(DfaNode* ele1, DfaNode* ele2) {
	if (ele1->getEdges().size() != ele2->getEdges().size()) {
		return false;
	}
	for (unsigned i = 0; i < ele1->getEdges().size(); ++i) {
		int flag = 0;
		for (unsigned j = 0; j < ele2->getEdges().size(); ++j) {
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
void DfaMinimizer :: initTwoSets(DfaNode *nonMinimizedDfa, PartitionSet *clS, PartitionSet *clF) {
	for (auto it = this->eles.begin(); it!= this->eles.end(); ++it) {
		if ((*it)->isAcceptedState()) {
			clF->addEle(*it);
		} else {
			clS->addEle(*it);
		}

	}
}

int  DfaMinimizer :: getNumByNode(DfaNode* node) {
	for (unsigned i = 0; i != this->partitionSets.size(); i++) {
		for (unsigned j = 0 ; j < this->partitionSets[i]->getElements().size(); j++) {
			if (this->partitionSets[i]->getElements()[j] == node ) {
				return this->partitionSets[i]->getNumber();
			}
		}

	}
	cout << "error"<< endl;
	// error TODO to be handled
	return 0;
}
vector<PartitionSet*> DfaMinimizer ::  getSet(){
	return this->partitionSets;
}

int DfaMinimizer::getNumOfUnfinishedSet() {
	int count = 0;
	for (unsigned i = 0; i < this->partitionSets.size(); i++) {
		if (!this->partitionSets[i]->isFinished()) {
			count++;
		}
	}
	return count;
}


bool PartitionSet:: isFinished() {
	return this->finished;
}
void PartitionSet::setFinished(bool finish) {
  this->finished = finish;
}

pair<int, DfaNode*> DfaMinimizer:: getNodeWithNum(DfaNode * node) {
	int temp = getNumByNode(node);
	pair<int, DfaNode*> p(temp, node);
	return p;
}

