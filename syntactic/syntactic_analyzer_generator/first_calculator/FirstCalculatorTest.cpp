/*
 * FirstCalculatorTest->cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include "../../../test_headers/p2_tests.h"
#include "FirstCalculator.h"
#include "../models/NonTerminal.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>

void build_test_graph1(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		unordered_map<GrammarExpression *, unordered_set<string>> *exp_ans);
bool test_graph1_results(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		unordered_map<GrammarExpression *, unordered_set<string>> *exp_ans);
bool compare_non_terminals(vector<NonTerminal *> * elements, vector<unordered_set<string>> ans, vector<bool> eps);
bool compare_exp(unordered_set<GrammarExpression *> *expressions,
		unordered_map<GrammarExpression *, unordered_set<string>> *exp_ans);
void destroy_graph(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions);

void test_first_calculator() {
	FirstCalculator cal;
	bool error = false;
	vector<GrammarElement *> ele;
	unordered_set<GrammarExpression *> exp;
	unordered_map<GrammarExpression *, unordered_set<string>> exp_ans;
	build_test_graph1(&ele, &exp, &exp_ans);
	cal.set_first_sets(&ele, &exp);
	error = error || test_graph1_results(&ele, &exp, &exp_ans);
	destroy_graph(&ele, &exp);
	ele.clear();
	exp.clear();
	if (error) {
		cout << "First Calculator Failed Test..." << endl;
	} else {
		cout << "First Calculator Success..." << endl;
	}
}

void build_test_graph1(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
	unordered_map<GrammarExpression *, unordered_set<string>> *exp_ans) {
	GrammarElement *e = new NonTerminal("E", NON_TERMINAL);
	GrammarElement *e1 = new NonTerminal("E'", NON_TERMINAL);
	GrammarElement *t = new NonTerminal("T", NON_TERMINAL);
	GrammarElement *t1 = new NonTerminal("T'", NON_TERMINAL);
	GrammarElement *f = new NonTerminal("F", NON_TERMINAL);
	GrammarElement *plus = new GrammarElement("+", TERMINAL);
	GrammarElement *mul = new GrammarElement("*", TERMINAL);
	GrammarElement *leftp = new GrammarElement("(", TERMINAL);
	GrammarElement *rightp = new GrammarElement(")", TERMINAL);
	GrammarElement *id = new GrammarElement("id", TERMINAL);
	elements->push_back(e);
	elements->push_back(t);
	elements->push_back(e1);
	elements->push_back(plus);
	elements->push_back(f);
	elements->push_back(t1);
	elements->push_back(mul);
	elements->push_back(leftp);
	elements->push_back(rightp);
	elements->push_back(id);
	static_cast<NonTerminal *>(e1)->eps = true;
	static_cast<NonTerminal *>(t1)->eps = true;
	GrammarExpression *ex1 = new GrammarExpression(e);
	GrammarExpression *ex2 = new GrammarExpression(e1);
	GrammarExpression *ex3 = new GrammarExpression(t);
	GrammarExpression *ex4 = new GrammarExpression(t1);
	GrammarExpression *ex5 = new GrammarExpression(f);
	GrammarExpression *ex6 = new GrammarExpression(f);
	expressions->insert(ex1);
	expressions->insert(ex2);
	expressions->insert(ex3);
	expressions->insert(ex4);
	expressions->insert(ex5);
	expressions->insert(ex6);
	ex1->expression.push_back(t);ex1->expression.push_back(e1);
	ex2->expression.push_back(plus);ex2->expression.push_back(t);ex2->expression.push_back(e1);
	ex3->expression.push_back(f);ex3->expression.push_back(t1);
	ex4->expression.push_back(mul);ex4->expression.push_back(f);ex4->expression.push_back(t1);
	ex5->expression.push_back(leftp);ex5->expression.push_back(e);ex5->expression.push_back(rightp);
	unordered_set<string> s1 = {"(", "id"}, s2 = {"+"}, s3 = {"(", "id"}, s4 = {"*"},
			s5 = {"("}, s6 = {"id"};
	ex6->expression.push_back(id);
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex1, s1));
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex2, s2));
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex3, s3));
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex4, s4));
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex5, s5));
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex6, s6));
	static_cast<NonTerminal *>(e)->leads_to.push_back(ex1);
	static_cast<NonTerminal *>(e1)->leads_to.push_back(ex2);
	static_cast<NonTerminal *>(t)->leads_to.push_back(ex3);
	static_cast<NonTerminal *>(t1)->leads_to.push_back(ex4);
	static_cast<NonTerminal *>(f)->leads_to.push_back(ex5);
	static_cast<NonTerminal *>(f)->leads_to.push_back(ex6);
	static_cast<NonTerminal *>(e)->referenced_in.push_back(ex5);
	static_cast<NonTerminal *>(e1)->referenced_in.push_back(ex1);
	static_cast<NonTerminal *>(e1)->referenced_in.push_back(ex2);
	static_cast<NonTerminal *>(t)->referenced_in.push_back(ex1);
	static_cast<NonTerminal *>(t)->referenced_in.push_back(ex2);
	static_cast<NonTerminal *>(t1)->referenced_in.push_back(ex3);
	static_cast<NonTerminal *>(t1)->referenced_in.push_back(ex4);
	static_cast<NonTerminal *>(f)->referenced_in.push_back(ex3);
	static_cast<NonTerminal *>(f)->referenced_in.push_back(ex4);
}

bool test_graph1_results(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		unordered_map<GrammarExpression *, unordered_set<string>> *exp_ans) {
	bool error = false;
	vector<unordered_set<string>> resele = {
			{"(", "id"}, {"(", "id"}, {"+"}, {"(", "id"},  {"*"}
	};
	vector<bool> reseleeps = {false, false, true, false, true};
	vector<NonTerminal *> nonTerminals;
	int t = 0,nt = 0;
	for (unsigned i = 0; i < elements->size(); i++) {
		GrammarElement * e = (*elements)[i];
		if (e->getName() == "E") {
			nt ^= 0b1;
			NonTerminal * ex = static_cast<NonTerminal*>(e);
			nonTerminals.push_back(ex);
		} else if (e->getName() == "E'") {
			nt ^= 0b10;
			NonTerminal * ex = static_cast<NonTerminal*>(e);
			nonTerminals.push_back(ex);
		} else if (e->getName() == "T") {
			nt ^= 0b100;
			NonTerminal * ex = static_cast<NonTerminal*>(e);;
			nonTerminals.push_back(ex);
		} else if (e->getName() == "T'") {
			nt ^= 0b1000;
			NonTerminal * ex = static_cast<NonTerminal*>(e);;
			nonTerminals.push_back(ex);
		} else if (e->getName() == "F") {
			nt ^= 0b10000;
			NonTerminal * ex = static_cast<NonTerminal*>(e);;
			nonTerminals.push_back(ex);
		} else {
			t++;
		}
	}
	if (nt != 0b11111) {
		cout << "Error : A Non-Terminal has not returned in the vector!" << endl;
		error = true;
	}
	if (t != 5) {
		cout << "Error : A Terminal has not returned in the vector!" << endl;
		error = true;
	}
	bool er1 = compare_non_terminals(&nonTerminals, resele, reseleeps);
	bool er2 = compare_exp(expressions, exp_ans);
	return error || er1 || er2;
}

bool compare_non_terminals(vector<NonTerminal *> * elements, vector<unordered_set<string>> ans, vector<bool> eps) {
	bool error = false;
	for (unsigned i = 0; i < elements->size(); i++) {
		NonTerminal e = *(*elements)[i];
		if (e.eps != eps[i]) {
			cout << "Error at rule " << e.getName() << " : Evalutes to epsilon is found "
					<< (e.eps?"True" : "False") << " which is wrong"<< endl;
			error = true;
		}
		if (e.first_strings != ans[i]) {
			cout << "Error at rule " << e.getName() << " : First not right" << endl;
			error = true;
		}
	}
	return error;
}
bool compare_exp(unordered_set<GrammarExpression *> *expressions, unordered_map<GrammarExpression *, unordered_set<string>> *exp_ans) {
	bool error = false;
	unsigned int i = 0;
	for (auto it = expressions->begin(); it != expressions->end(); it++) {
		if ((*it)->first_strings != (*exp_ans)[*it]) {
			cout << "Error at exp " << i+1 << " : First not right" << endl;
			(*it)->print_expression();
			error = true;
		}
		i++;
	}
	return error;
}

void destroy_graph(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions) {
	for (unsigned i = 0; i < elements->size(); i++) {
		delete (*elements)[i];
	}
	for (auto it = expressions->begin(); it != expressions->end(); it++) {
		delete (*it);
	}
}
