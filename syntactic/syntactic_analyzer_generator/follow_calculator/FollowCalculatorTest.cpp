/*
 * FollowCalculatorTest.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include "../../../test_headers/p2_tests.h"
#include "FollowCalculator.h"
#include "../models/NonTerminal.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>

void build_test_graph_f(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions);
bool test_graph_resultsf(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions);
bool compare_non_terminalsf(vector<NonTerminal *> * elements, vector<unordered_set<string>> ans);
void destroy_graphf(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions);

void test_follow_calculator() {
	FollowCalculator cal;
	bool error = false;
	vector<GrammarElement *> ele;
	unordered_set<GrammarExpression *> exp;
	build_test_graph_f(&ele, &exp);
	cal.set_follow_sets(&ele, &exp);
	error = error || test_graph_resultsf(&ele, &exp);
	destroy_graphf(&ele, &exp);
	ele.clear();
	exp.clear();
	if (error) {
		cout << "Follow Calculator Failed Test..." << endl;
	} else {
		cout << "Follow Calculator Success..." << endl;
	}
}



void build_test_graph_f(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions) {
	GrammarElement *e = new NonTerminal("E", NON_TERMINAL);
	GrammarElement *e1 = new NonTerminal("E'", NON_TERMINAL);
	GrammarElement *t = new NonTerminal("T", NON_TERMINAL);
	GrammarElement *t1 = new NonTerminal("T'", NON_TERMINAL);
	GrammarElement *f = new NonTerminal("F", NON_TERMINAL);
	GrammarElement *plus = new GrammarElement("id", TERMINAL);
	GrammarElement *mul = new GrammarElement(")", TERMINAL);
	GrammarElement *leftp = new GrammarElement("(", TERMINAL);
	GrammarElement *rightp = new GrammarElement("*", TERMINAL);
	GrammarElement *id = new GrammarElement("+", TERMINAL);
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
	ex1->belongs_to = e;
	ex2->belongs_to = e1;
	ex3->belongs_to = t;
	ex4->belongs_to = t1;
	ex5->belongs_to = f;
	ex6->belongs_to = f;
	ex1->expression.push_back(t);ex1->expression.push_back(e1);
	ex2->expression.push_back(plus);ex2->expression.push_back(t);ex2->expression.push_back(e1);
	ex3->expression.push_back(f);ex3->expression.push_back(t1);
	ex4->expression.push_back(mul);ex4->expression.push_back(f);ex4->expression.push_back(t1);
	ex5->expression.push_back(leftp);ex5->expression.push_back(e);ex5->expression.push_back(rightp);
	ex6->expression.push_back(id);
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
	unordered_set<string> s1 = {"(", "id"}, s2 = {"*"}, s3 = {"+"};
	static_cast<NonTerminal *>(e)->first_strings = s1;
	static_cast<NonTerminal *>(e1)->first_strings = s3;
	static_cast<NonTerminal *>(t)->first_strings = s1;
	static_cast<NonTerminal *>(t1)->first_strings = s2;
	static_cast<NonTerminal *>(f)->first_strings = s1;
}

bool test_graph_resultsf(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions) {
	bool error = false;
	vector<unordered_set<string>> resele = {
			{"$", ")"}, {"+", ")", "$"}, {"$", ")"}, {"+", "*", ")", "$"},  {"+", ")", "$"}
	};
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
			NonTerminal * ex = static_cast<NonTerminal*>(e);
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
	bool er1 = compare_non_terminalsf(&nonTerminals, resele);
	return error || er1;
}

bool compare_non_terminalsf(vector<NonTerminal *> * elements, vector<unordered_set<string>> ans) {
	bool error = false;
	for (unsigned i = 0; i < elements->size(); i++) {
		NonTerminal e = *(*elements)[i];
		if (e.follow_strings != ans[i]) {
			cout << "Error at rule " << e.getName() << " : Follow not right" << endl;
			error = true;
		}
	}
	return error;
}

void destroy_graphf(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions) {
	for (unsigned i = 0; i < elements->size(); i++) {
		delete (*elements)[i];
	}
	for (auto it = expressions->begin(); it != expressions->end(); it++) {
		delete (*it);
	}
}
