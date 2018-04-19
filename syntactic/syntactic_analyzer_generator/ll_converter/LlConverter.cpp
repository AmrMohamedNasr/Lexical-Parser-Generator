/*
 * LlConverter.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: michael
 */
#include "LlConverter.h"
#include <iterator>
#include <vector>
#include <map>
#include <unordered_set>
#include <stack>
#include "../../syntactic_analyzer_generator/models/GrammarElement.h"


void LlConverter::remove_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions) {
	remove_indirect_left_recursion(rules, expressions);
}

bool LlConverter::check_direct_left_recursion(GrammarElement *rule) {
	NonTerminal * temp = dynamic_cast<NonTerminal *>(rule);
	for (unsigned i = 0; i < temp->leads_to.size(); ++i) {
		if (temp->leads_to[i]->expression[0] == rule) {
			return true;
		}
	}
	return false;
}

void LlConverter::remove_direct_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions, GrammarElement * adjustRule) {
		if (adjustRule->type == NON_TERMINAL && check_direct_left_recursion(adjustRule)) {
			NonTerminal * rule = dynamic_cast<NonTerminal *>(adjustRule);
			NonTerminal * newRule = new NonTerminal();
			newRule->type = NON_TERMINAL;
			newRule->eps = true;
			newRule->name = rule->name + "'";
			vector<GrammarExpression *> *exprs = &(rule->leads_to);
			int size = exprs->size();
			for (unsigned j = 0; j < size; ++j) {
				 if ((*exprs)[j]->expression[0]->type == NON_TERMINAL) {
					 NonTerminal * comparable = dynamic_cast<NonTerminal *> ((*exprs)[j]->expression[0]);
					 if (comparable == rule) {
						 (*exprs)[j]->expression.erase((*exprs)[j]->expression.begin());
						 (*exprs)[j]->expression.push_back(newRule);
						 (*exprs)[j]->belongs_to = newRule;
						 newRule->referenced_in.push_back((*exprs)[j]);
						 newRule->leads_to.push_back((*exprs)[j]);
						 rule->leads_to.erase(rule->leads_to.begin()+j);
					 } else {
						 (*exprs)[j]->expression.push_back(newRule);
						 newRule->referenced_in.push_back((*exprs)[j]);
					 }
				 } else {
					 (*exprs)[j]->expression.push_back(newRule);
					 newRule->referenced_in.push_back((*exprs)[j]);
				 }
			}
			rules->push_back(newRule);
		}
}
void LlConverter::remove_indirect_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions) {
	int size = rules->size();
	for (unsigned i = 0; i < size; ++i) {
		if ((*rules)[i]->type == NON_TERMINAL) {
			map<GrammarElement*,int > matcher;
			unordered_set <GrammarExpression *> chooser;
			NonTerminal * temp = dynamic_cast<NonTerminal *>((*rules)[i]);
			for (unsigned j = 0; j < i; ++j) {
				matcher.insert(pair<GrammarElement*,int> ((*rules)[j], j));
			}
			stack <GrammarExpression *> s;
			if ( check_indirect_left_recursion(temp, temp, &matcher, &chooser)) {
				for (unsigned j = 0; j < temp->leads_to.size(); j++ ) {
					unordered_set<GrammarExpression *>::const_iterator it = chooser.find(temp->leads_to[i]);
					if ((it) != chooser.end()) {
						s.push(temp->leads_to[j]);
						temp->leads_to.erase(temp->leads_to.begin() + j);
					}
				}
				while(!s.empty()) {
					GrammarExpression * expr = s.top();
					s.pop();
					NonTerminal * ele =  dynamic_cast<NonTerminal *> (expr->expression[0]);
					expr->expression.erase(expr->expression.begin());
					for (unsigned k = 0; k < ele->leads_to.size(); ++k) {
						for (unsigned j = 0; j < expr->expression.size(); ++j) {
							ele->leads_to[k]->expression.push_back(expr->expression[j]);
						}
						GrammarExpression * exprTemp = ele->leads_to[k];
						exprTemp->belongs_to = temp;
						temp->leads_to.push_back(expr);
					}
					for (unsigned j = 0; j < temp->leads_to.size(); j++ ) {
						unordered_set<GrammarExpression *>::const_iterator it = chooser.find(temp->leads_to[i]);
						if ((it) != chooser.end()) {
							s.push(temp->leads_to[j]);
							temp->leads_to.erase(temp->leads_to.begin() + j);
						}
					}
				}


			}
			remove_direct_left_recursion(rules, expressions, temp);
		}
	}
}

bool LlConverter::check_indirect_left_recursion(GrammarElement * source, GrammarElement * rule, map<GrammarElement *, int>* matcher, unordered_set<GrammarExpression*> *chooser) {
	NonTerminal * temp = dynamic_cast<NonTerminal *>(rule);
	NonTerminal * src = dynamic_cast<NonTerminal *>(source);
	bool left = false;
	for (unsigned i = 0; i < temp->leads_to.size(); ++i) {
		if (temp->leads_to[i]->expression[0]->type == NON_TERMINAL &&
				temp->leads_to[i]->expression[0] != temp &&
				temp->leads_to[i]->expression[0] != src) {
			map<GrammarElement *, int>::const_iterator it = (*matcher).find(temp->leads_to[i]->expression[0]);
			if ((it) != (*matcher).end()) {
				if (check_indirect_left_recursion(
						src, temp->leads_to[i]->expression[0], matcher, chooser)) {
						(*chooser).insert(temp->leads_to[i]);
						left = true;
				}
			}
		}
	}
	if (left)
		return true;
	return false;

}


