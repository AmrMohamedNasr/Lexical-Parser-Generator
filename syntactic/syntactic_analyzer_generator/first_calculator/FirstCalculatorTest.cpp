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
	NonTerminal *e = new NonTerminal();
	NonTerminal *e1 = new NonTerminal();
	NonTerminal *t = new NonTerminal();
	NonTerminal *t1 = new NonTerminal();
	NonTerminal *f = new NonTerminal();
	GrammarElement *plus = new GrammarElement();;
	GrammarElement * mul = new GrammarElement();
	GrammarElement * leftp = new GrammarElement();
	GrammarElement * rightp = new GrammarElement();
	GrammarElement * id = new GrammarElement();
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
	id->type = TERMINAL;
	rightp->type = TERMINAL;
	leftp->type = TERMINAL;
	mul->type = TERMINAL;
	plus->type = TERMINAL;
	id->name = "id";
	rightp->name = ")";
	leftp->name = "(";
	mul->name = "*";
	plus->name = "+";
	e->type = NON_TERMINAL;
	e1->type = NON_TERMINAL;
	t->type = NON_TERMINAL;
	t1->type = NON_TERMINAL;
	f->type = NON_TERMINAL;
	e->name = "E";
	e1->name = "E'";
	t->name = "T";
	t1->name = "T'";
	f->name = "F";
	e1->eps = true;
	t1->eps = true;
	GrammarExpression *ex1 = new GrammarExpression();
	GrammarExpression *ex2 = new GrammarExpression();
	GrammarExpression *ex3 = new GrammarExpression();
	GrammarExpression *ex4 = new GrammarExpression();
	GrammarExpression *ex5 = new GrammarExpression();
	GrammarExpression *ex6 = new GrammarExpression();
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
	unordered_set<string> s1 = {"(", "id"}, s2 = {"+"}, s3 = {"(", "id"}, s4 = {"*"},
			s5 = {"("}, s6 = {"id"};
	ex6->expression.push_back(id);
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex1, s1));
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex2, s2));
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex3, s3));
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex4, s4));
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex5, s5));
	exp_ans->insert(pair<GrammarExpression *, unordered_set<string>>(ex6, s6));
	e->leads_to.push_back(ex1);
	e1->leads_to.push_back(ex2);
	t->leads_to.push_back(ex3);
	t1->leads_to.push_back(ex4);
	f->leads_to.push_back(ex5);
	f->leads_to.push_back(ex6);
	e->referenced_in.push_back(ex5);
	e1->referenced_in.push_back(ex1);e1->referenced_in.push_back(ex2);
	t->referenced_in.push_back(ex1);t->referenced_in.push_back(ex2);
	t1->referenced_in.push_back(ex3);t1->referenced_in.push_back(ex4);
	f->referenced_in.push_back(ex3);f->referenced_in.push_back(ex4);
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
		if (e->name == "E") {
			nt ^= 0b1;
			NonTerminal * ex = dynamic_cast<NonTerminal*>(e);
			nonTerminals.push_back(ex);
		} else if (e->name == "E'") {
			nt ^= 0b10;
			NonTerminal * ex = dynamic_cast<NonTerminal*>(e);
			nonTerminals.push_back(ex);
		} else if (e->name == "T") {
			nt ^= 0b100;
			NonTerminal * ex = dynamic_cast<NonTerminal*>(e);;
			nonTerminals.push_back(ex);
		} else if (e->name == "T'") {
			nt ^= 0b1000;
			NonTerminal * ex = dynamic_cast<NonTerminal*>(e);;
			nonTerminals.push_back(ex);
		} else if (e->name == "F") {
			nt ^= 0b10000;
			NonTerminal * ex = dynamic_cast<NonTerminal*>(e);;
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
			cout << "Error at rule " << e.name << " : Evalutes to epsilon is found "
					<< (e.eps?"True" : "False") << " which is wrong"<< endl;
			error = true;
		}
		if (e.first_strings != ans[i]) {
			cout << "Error at rule " << e.name << " : First not right" << endl;
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
