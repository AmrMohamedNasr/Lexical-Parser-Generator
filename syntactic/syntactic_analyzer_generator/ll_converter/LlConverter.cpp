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


void LlConverter::remove_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions, unordered_set<NonTerminal *> *changed) {
	unsigned size = rules->size();
	for (unsigned i = 0; i < size; ++i) {
		if ((*rules)[i]->getType() == NON_TERMINAL) {
			map<GrammarElement*,int > matcher;
			unordered_set <GrammarExpression *> chooser;
			NonTerminal * temp = static_cast<NonTerminal *>((*rules)[i]);
			for (unsigned j = 0; j < i; ++j) {
				matcher.insert(pair<GrammarElement*,int> ((*rules)[j], j));
			}
			stack <GrammarExpression *> s;
			std::unordered_set<GrammarExpression *>::const_iterator it;
			if ( check_indirect_left_recursion(temp, temp, &matcher, &chooser)) {
				for (unsigned j = 0; j < temp->leads_to.size(); j++ ) {
					it = chooser.find(temp->leads_to[j]);
					if (it != chooser.end()) {
						s.push(temp->leads_to[j]);
						temp->leads_to.erase(temp->leads_to.begin() + j);
					}
				}
				while(!s.empty()) {
					GrammarExpression * expr = s.top();
					s.pop();
					NonTerminal * ele = static_cast<NonTerminal *> (expr->expression[0]);
					expr->expression.erase(expr->expression.begin());
					for (unsigned k = 0; k < ele->leads_to.size(); ++k) {
						// boolean considered for the new expression to be substituted.
						bool considered = false;
						it = chooser.find(ele->leads_to[k]);
						if (it != chooser.end()) {
							considered = true;
						}
						GrammarExpression * exprTemp = new GrammarExpression(temp);
						for (unsigned count = 0; count < ele->leads_to[k]->expression.size(); ++count) {
							exprTemp->expression.push_back(ele->leads_to[k]->expression[count]);
						}
						for (unsigned j = 0; j < expr->expression.size(); ++j) {
							exprTemp->expression.push_back(expr->expression[j]);
						}
						temp->leads_to.push_back(exprTemp);
						(*expressions).insert(exprTemp);
						if (considered) {
							chooser.insert(exprTemp);
						}
					}
					for (unsigned j = 0; j < temp->leads_to.size(); j++ ) {
						it = chooser.find(temp->leads_to[j]);
						if (it != chooser.end()) {
							s.push(temp->leads_to[j]);
							temp->leads_to.erase(temp->leads_to.begin() + j);
						}
					}
				}
			}
			remove_direct_left_recursion(rules, expressions, temp, changed);
		}
	}
}

void LlConverter::remove_direct_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions, GrammarElement * adjustRule, unordered_set<NonTerminal *> *changed) {
		if (adjustRule->getType() == NON_TERMINAL && check_direct_left_recursion(adjustRule)) {
			GrammarElement * rule = static_cast<NonTerminal *>(adjustRule);
			GrammarElement * newRule = new NonTerminal(rule->getName() + "'", NON_TERMINAL);
			static_cast<NonTerminal *>(newRule)->eps = true;
			vector<GrammarExpression *> *exprs = &(static_cast<NonTerminal *>(rule)->leads_to);
			unsigned size = exprs->size();
			for (unsigned j = 0; j < size; ++j) {
				 if ((*exprs)[j]->expression[0]->getType() == NON_TERMINAL) {
					 NonTerminal * comparable = static_cast<NonTerminal *> ((*exprs)[j]->expression[0]);
					 if (comparable == rule) {
						 (*exprs)[j]->expression.erase((*exprs)[j]->expression.begin());
						 (*exprs)[j]->expression.push_back(newRule);
						 (*exprs)[j]->belongs_to = static_cast<NonTerminal *>(newRule);
						 static_cast<NonTerminal *>(newRule)->referenced_in.push_back((*exprs)[j]);
						 static_cast<NonTerminal *>(newRule)->leads_to.push_back((*exprs)[j]);
						 static_cast<NonTerminal *>(rule)->leads_to.erase(static_cast<NonTerminal *>(rule)->leads_to.begin()+j);
					 } else {
						 (*exprs)[j]->expression.push_back(newRule);
						 static_cast<NonTerminal *>(newRule)->referenced_in.push_back((*exprs)[j]);
					 }
				 } else {
					 (*exprs)[j]->expression.push_back(newRule);
					 static_cast<NonTerminal *>(newRule)->referenced_in.push_back((*exprs)[j]);
				 }
			}
			(*changed).insert(static_cast<NonTerminal *>(rule));
			(*changed).insert(static_cast<NonTerminal *>(newRule));
			rules->push_back(newRule);
		}
}

bool LlConverter::check_direct_left_recursion(GrammarElement *rule) {
	NonTerminal * temp = static_cast<NonTerminal *>(rule);
	for (unsigned i = 0; i < temp->leads_to.size(); ++i) {
		if (temp->leads_to[i]->expression[0] == rule) {
			return true;
		}
	}
	return false;
}

bool LlConverter::check_indirect_left_recursion(GrammarElement * source, GrammarElement * rule, map<GrammarElement *, int>* matcher, unordered_set<GrammarExpression*> *chooser) {
	NonTerminal* temp = static_cast<NonTerminal *>(rule);
	NonTerminal* src = static_cast<NonTerminal *>(source);
	bool left = false;
	for (unsigned i = 0; i < temp->leads_to.size(); ++i) {
		if (temp->leads_to[i]->expression[0] == src && temp != src) {
			left = true;
		}else if (temp->leads_to[i]->expression[0]->getType() == NON_TERMINAL &&
				temp->leads_to[i]->expression[0] != temp) {
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

void LlConverter::left_factor(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions, unordered_set<NonTerminal *> *changed) {
	for (unsigned i = 0; i < rules->size(); ++i) {
		if ((*rules)[i]->getType() == NON_TERMINAL) {
			NonTerminal * rule = static_cast<NonTerminal *>((*rules)[i]);
			unordered_set<GrammarExpression *> to_be_changed;
			bool direct = false;
			while (check_left_factoring(rule, &to_be_changed, &direct)) {
				if (direct) {
					generate_direct_left_factoring((*rules)[i], rules, expressions, changed, &to_be_changed);
				} else {
					int counter = 0;
					for (auto itr = to_be_changed.begin(); itr != to_be_changed.end(); ++itr) {
						if ((*itr)->expression[0]->getType() == NON_TERMINAL) {
							NonTerminal * temp = static_cast<NonTerminal *>((*itr)->expression[0]);
							(*itr)->expression.erase((*itr)->expression.begin());
							for (unsigned j = 0; j < temp->leads_to.size(); ++j) {
								GrammarExpression * exprTemp = new GrammarExpression(rule);
								for (unsigned k = 0; k < temp->leads_to[j]->expression.size(); ++k) {
									exprTemp->expression.push_back(temp->leads_to[j]->expression[k]);
								}
								for (unsigned k = 0; k < (*itr)->expression.size(); ++k) {
									exprTemp->expression.push_back((*itr)->expression[k]);
								}
								rule->leads_to.push_back(exprTemp);
								(*expressions).insert(exprTemp);
								rule->leads_to.erase(rule->leads_to.begin() + counter);
							}
						}

						counter++;
					}
					direct = false;
					to_be_changed.clear();
				}
			}
		}
	}
}

bool LlConverter::check_left_factoring(GrammarElement * source, unordered_set<GrammarExpression*> *to_be_changed, bool * direct) {
	map<GrammarElement*, int> first_eles;
	unordered_set<string> first_strings;
	NonTerminal * src = static_cast<NonTerminal *>(source);
	bool left = false;
	// check if it needs direct left factoring.
	for (unsigned i = 0; i < src->leads_to.size(); ++i) {
		map<GrammarElement *, int>::const_iterator it = first_eles.find(src->leads_to[i]->expression[0]);
		if (it != first_eles.end()) {
			*direct = true;
			to_be_changed->insert(src->leads_to[i]);
			to_be_changed->insert(src->leads_to[(*it).second]);
			left = true;
		} else {
			first_eles.insert(pair<GrammarElement*, int>(src->leads_to[i]->expression[0], i));
		}
	}
	// if it need direct left factoring.
	// check if it needs indirect left factoring.
	for (auto itr = src->leads_to[0]->first_strings.begin(); itr != src->leads_to[0]->first_strings.end(); ++itr) {
		first_strings.insert(*itr);
	}
	for (unsigned i = 1; i < src->leads_to.size(); ++i) {
		for (auto itr = src->leads_to[i]->first_strings.begin(); itr != src->leads_to[i]->first_strings.end(); ++itr) {
			unordered_set<string>::const_iterator it = first_strings.find(*itr);
			if (it != first_strings.end()) {
				to_be_changed->insert(src->leads_to[i]);
				if (src->leads_to[0]->first_strings.find(*itr) == it) {
					to_be_changed->insert(src->leads_to[0]);
				}
				*direct = false;
				left = true;
			} else {
				first_strings.insert(*itr);
			}
		}
	}
	if (left) {
		return true;
	}
	return false;

}

void LlConverter:: generate_direct_left_factoring(GrammarElement * source,
												vector<GrammarElement *> *rules,
												unordered_set<GrammarExpression *> * expressions,
												unordered_set<NonTerminal *> *changed,
												unordered_set<GrammarExpression*> *to_be_changed) {
	map <GrammarElement *, vector<GrammarExpression *>> matched_exprs;
	for (auto itr = to_be_changed->begin(); itr != to_be_changed->end(); ++itr) {
		map<GrammarElement *, vector<GrammarExpression *>>::iterator it = matched_exprs.find((*itr)->expression[0]);
		if (it != matched_exprs.end()) {
			(*it).second.push_back((*itr));
		} else {
			vector<GrammarExpression *> temp;
			temp.push_back((*itr));
			matched_exprs.insert(pair<GrammarElement *, vector<GrammarExpression *>> (
															(*itr)->expression[0], temp));
		}
	}
	NonTerminal * src = static_cast<NonTerminal *>(source);
	for (auto itr = matched_exprs.begin(); itr != matched_exprs.end(); ++itr) {
		char num_of_factors = '1';
		GrammarExpression * newExpr = new GrammarExpression(src);

		bool sameFirst = true;
		while (sameFirst) {
			newExpr->expression.push_back((*itr).second[0]->expression[0]);
			if ((*itr).second[0]->expression[0]->getType() == NON_TERMINAL) {
				NonTerminal * temp = static_cast<NonTerminal *>((*itr).second[0]->expression[0]);
				temp->referenced_in.push_back(newExpr);
			}
			for (unsigned i = 0; i < (*itr).second.size(); ++i) {
				(*itr).second[i]->expression.erase((*itr).second[i]->expression.begin());
			}
			unordered_set <GrammarElement *> first_eles;
			first_eles.insert((*itr).second[0]->expression[0]);
			for (unsigned j = 1; j < (*itr).second.size(); ++j) {
				unordered_set <GrammarElement *>::iterator it = first_eles.find((*itr).second[j]->expression[0]);
				if (it == first_eles.end()) {
					j = (*itr).second.size();
					sameFirst = false;
				}
			}
		}
		NonTerminal * newEle = new NonTerminal(
				src->getName() + "_" +  num_of_factors, NON_TERMINAL);
		num_of_factors++;
		newEle->referenced_in.push_back(newExpr);
		newExpr->expression.push_back(newEle);
		unordered_set<GrammarExpression *> to_be_removed;
		for( unsigned i = 0; i < (*itr).second.size(); ++i) {
			to_be_removed.insert((*itr).second[i]);
		}
		for (unsigned i = 0; i < src->leads_to.size(); ++i) {
			unordered_set<GrammarExpression *>::iterator it = to_be_removed.find(src->leads_to[i]);
			if (it != to_be_removed.end()) {
				src->leads_to.erase(src->leads_to.begin() + i);
			}
		}
		src->leads_to.push_back(newExpr);
		for (auto itra = to_be_removed.begin(); itra != to_be_removed.end(); ++itra) {
			(*itra)->belongs_to = newEle;
			newEle->leads_to.push_back((*itra));
		}
		(*rules).push_back(newEle);
		(*expressions).insert(newExpr);
		(*changed).insert(newEle);
	}
}
