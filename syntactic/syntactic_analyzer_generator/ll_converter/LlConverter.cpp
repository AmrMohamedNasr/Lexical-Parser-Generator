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
#include "../../syntactic_analyzer_generator/models/GrammarElement.h"


void LlConverter::remove_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions) {
	remove_indirect_left_recursion(rules, expressions);
	remove_direct_left_recursion(rules, expressions);
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

void LlConverter::remove_direct_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions) {
	for (unsigned i = 0; i < rules->size(); ++i) {
		if ((*rules)[i]->type == NON_TERMINAL && check_direct_left_recursion((*rules)[i])) {
			NonTerminal * rule = dynamic_cast<NonTerminal *>((*rules)[i]);
			NonTerminal * newRule = new NonTerminal();
			newRule->type = NON_TERMINAL;
			newRule->eps = true;
			newRule->name = rule->name + "'";
			GrammarExpression* epsExpr = new GrammarExpression();
			epsExpr->belongs_to = newRule;
			epsExpr->eps = true;
			newRule->leads_to.push_back(epsExpr);
			vector<GrammarExpression *> *exprs = &(rule->leads_to);
			for (unsigned j = 0; j < exprs->size(); ++j) {
				 if ((*exprs)[j]->expression[0]->type == NON_TERMINAL) {
					 NonTerminal * comparable = dynamic_cast<NonTerminal *> ((*exprs)[j]->expression[0]);
					 if (comparable == (*rules)[i]) {
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
}
void LlConverter::remove_indirect_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions) {
	for (unsigned i = 1; i < rules->size(); ++i) {
		for (unsigned j = 0; j < i; ++j) {
			if ((*rules)[j]->type == NON_TERMINAL &&
					check_indirect_left_recursion(rules, expressions, i)) {
				//convert_to_direct((*rules)[i]);
			}
		}
	}
}

bool LlConverter::check_indirect_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions, int index) {
	map<GrammarElement*,GrammarExpression* > matcher;
	NonTerminal * temp = dynamic_cast<NonTerminal *>((*rules)[index]);
	for (unsigned i = 0; i < temp->leads_to.size(); ++i) {
		matcher.insert(pair<GrammarElement*,GrammarExpression*> (temp, temp->leads_to[i]));
	}
	for (unsigned j = 0; j < index; ++j) {
		if ((*rules)[j]->type == NON_TERMINAL) {
			map<GrammarElement*,GrammarExpression*>::const_iterator it = (matcher.find((*rules)[j]));
			if ((it) != matcher.end()) {

			}

		}
	}
		return false;
}


