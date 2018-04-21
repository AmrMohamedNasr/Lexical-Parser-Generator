/*
 * LlConverterTest.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */
#include "../../syntactic_analyzer_generator/ll_converter/LlConverter.h"
#include "../../../syntactic/syntactic_analyzer_generator/models/GrammarExpression.h"
#include "../../../syntactic/syntactic_analyzer_generator/models/GrammarElement.h"
#include "../../../syntactic/syntactic_analyzer_generator/models/NonTerminal.h"
#include "../../../test_headers/p2_tests.h"

void test_left_recursion();
void test_indirect_left_recursion();
void test_ll_converter() {
	test_left_recursion();
	test_indirect_left_recursion();
}

void test_left_recursion() {
	NonTerminal* bterm = new NonTerminal();
	NonTerminal* bfactor = new NonTerminal();
	NonTerminal* bexpr = new NonTerminal();
	GrammarElement* oR = new GrammarElement();
	oR->name = "or";
	oR->type = TERMINAL;
	GrammarElement* openBracket = new GrammarElement();
	openBracket->name = "(";
	openBracket->type = TERMINAL;
	GrammarElement* closeBracket = new GrammarElement();
	closeBracket->name = ")";
	closeBracket->type = TERMINAL;
	GrammarElement* aND = new GrammarElement();
	aND->name = "and";
	aND->type = TERMINAL;
	GrammarElement* nOT = new GrammarElement();
	nOT->name = "not";
	nOT->type = TERMINAL;
	GrammarElement* tRUE = new GrammarElement();
	tRUE->name = "true";
	tRUE->type = TERMINAL;
	GrammarElement* fALSE = new GrammarElement();
	fALSE->name = "false";
	fALSE->type = TERMINAL;
	// first rule
	GrammarExpression* exp11 = new GrammarExpression();
	exp11->belongs_to = bexpr;
	exp11->expression = { bexpr, oR, bterm };
	exp11->first_strings = { "not", "(", "true", "false" };
	GrammarExpression* exp12 = new GrammarExpression();
	exp12->belongs_to = bexpr;
	exp12->expression = { bterm };
	exp12->first_strings = { "not", "(", "true", "false" };
	bexpr->type = NON_TERMINAL;
	bexpr->referenced_in = {exp11 };
	bexpr->name = "bexpr";
	bexpr->leads_to = { exp11, exp12 };
	bexpr->first_strings = { "not", "(", "true", "false" };
	bexpr->follow_strings = { "$", ")"};
	// second rule
	GrammarExpression* exp21 = new GrammarExpression();
	exp21->belongs_to = bterm;
	exp21->expression = { bterm, aND, bfactor };
	exp21->first_strings = { "not", "(", "true", "false" };
	GrammarExpression* exp22 = new GrammarExpression();
	exp22->belongs_to = bterm;
	exp22->expression = { bfactor };
	exp22->first_strings = { "not", "(", "true", "false" };
	bterm->type = NON_TERMINAL;
	bterm->referenced_in = { exp11, exp12, exp21 };
	bterm->name = "bterm";
	bterm->leads_to = { exp21, exp22 };
	bterm->first_strings = { "not", "(", "true", "false" };
	bterm->follow_strings = { "$", "or", ")"};
	//third rule
	GrammarExpression* exp31 = new GrammarExpression();
	exp31->belongs_to = bfactor;
	exp31->expression = { nOT, bfactor };
	exp31->first_strings = {"not"};
	GrammarExpression* exp32 = new GrammarExpression();
	exp32->belongs_to = bfactor;
	exp32->expression = { openBracket, bexpr, closeBracket };
	exp32->first_strings = {"("};
	GrammarExpression* exp33 = new GrammarExpression();
	exp33->belongs_to = bfactor;
	exp33->expression = { tRUE };
	exp33->first_strings = {"true"};
	GrammarExpression* exp34 = new GrammarExpression();
	exp34->belongs_to = bfactor;
	exp34->expression = { fALSE };
	exp34->first_strings = {"false"};
	bfactor->type = NON_TERMINAL;
	bfactor->referenced_in = { exp31, exp21, exp22 };
	bfactor->name = "bfactor";
	bfactor->leads_to = { exp31, exp32, exp33, exp34 };
	bfactor->first_strings = { "not", "(", "true", "false" };
	bfactor->follow_strings = { "$", "or", ")", "and" };

	vector <GrammarElement* > set = {bexpr, bterm, bfactor, nOT, aND, oR, closeBracket, openBracket, tRUE, fALSE };
	unordered_set <GrammarExpression*> set2 = {exp11, exp12, exp21, exp22, exp31, exp32, exp33, exp34};
	unordered_set <NonTerminal*> changed;
	LlConverter converter;
	converter.remove_left_recursion(&set, &set2, &changed);
	// if pass integration test passed

	if (set[0]->name == "bexpr") {
		NonTerminal * temp = dynamic_cast<NonTerminal *>(set[0]);
		if (temp->leads_to[0]->expression[0] != set[1]) {
			cout << "Error in Left recursion" << "Expected reference to \" bterm \" " <<endl;
		}
		if (temp->leads_to[0]->expression[1] != set[10]) {
			cout << "Error in Left recursion" << "Expected reference to \" bterm \" " <<endl;
		}
	} else {
		cout << "Error in Referencing sets" << endl;
	}
	cout << "Eliminating left recursion success" << endl;
	delete bexpr;
	delete bterm;
	delete bfactor;
	delete oR;
	delete openBracket;
	delete closeBracket;
	delete aND;
	delete nOT;
	delete tRUE;
	delete fALSE;
}
void test_indirect_left_recursion() {
	NonTerminal* a = new NonTerminal();
	a->name = "A";
	a->type = NON_TERMINAL;
	NonTerminal* b = new NonTerminal();
	b->name = "B";
	b->type = NON_TERMINAL;
	NonTerminal* c = new NonTerminal();
	c->name = "C";
	c->type = NON_TERMINAL;
	NonTerminal* d = new NonTerminal();
	d->name = "D";
	d->type = NON_TERMINAL;
	GrammarElement* x = new GrammarElement();
	x->name = "x";
	x->type = TERMINAL;
	GrammarElement* y = new GrammarElement();
	y->name = "y";
	y->type = TERMINAL;
	GrammarElement* cS = new GrammarElement();
	cS->name = ")";
	cS->type = TERMINAL;
	GrammarElement* dS = new GrammarElement();
	dS->name = "and";
	dS->type = TERMINAL;
	GrammarExpression* exp11 = new GrammarExpression();
	exp11->belongs_to = a;
	exp11->expression = { b, x, y};
	b->referenced_in.push_back(exp11);
	GrammarExpression* exp12 = new GrammarExpression();
	exp12->belongs_to = a;
	exp12->expression = { x };
	GrammarExpression* exp21 = new GrammarExpression();
	exp21->belongs_to = b;
	exp21->expression = { c, d};
	d->referenced_in.push_back(exp21);
	c->referenced_in.push_back(exp21);
	GrammarExpression* exp31 = new GrammarExpression();
	exp31->belongs_to = c;
	exp31->expression = { a };
	a->referenced_in.push_back(exp31);
	GrammarExpression* exp32 = new GrammarExpression();
	exp32->belongs_to = c;
	exp32->expression = { cS };
	GrammarExpression* exp41 = new GrammarExpression();
	exp41->belongs_to = d;
	exp41->expression = { dS };
	a->leads_to = { exp11, exp12};
	b->leads_to = { exp21 };
	c->leads_to = { exp31, exp32 };
	d->leads_to = { exp41 };

	vector <GrammarElement* > set = {a, b, c, d, x, y, cS, dS};
	unordered_set <GrammarExpression*> set2 = {exp11, exp12, exp21, exp31, exp32, exp41};
	unordered_set <NonTerminal*> changed;
	LlConverter converter;
	converter.remove_left_recursion(&set, &set2, &changed);
	NonTerminal * ele =  dynamic_cast<NonTerminal *> (set[8]);
	NonTerminal * ele1 =  dynamic_cast<NonTerminal *> (set[2]);
	if (ele->name == "C'" ) {
		if (ele->leads_to.size() == 1) {
			if (ele->eps) {
				if (ele->leads_to[0]->belongs_to == ele) {
					if (ele->leads_to[0]->expression.size() == 4) {
						if (ele->leads_to[0]->expression[3] == ele) {
							if (ele->referenced_in.size() == 3) {
								if (ele->referenced_in[0]->belongs_to == c ||
									ele->referenced_in[0]->belongs_to == c ||
									ele->referenced_in[0]->belongs_to == ele) {
									if (ele->referenced_in[1]->belongs_to == c ||
										ele->referenced_in[1]->belongs_to == c ||
										ele->referenced_in[1]->belongs_to == ele) {
										if (ele->referenced_in[2]->belongs_to == c ||
											ele->referenced_in[2]->belongs_to == c ||
											ele->referenced_in[2]->belongs_to == ele) {
											if ( ele1->leads_to.size() == 2) {
												if (ele1->leads_to[1]->expression[0] == x &&
													ele1->leads_to[1]->expression[1] == ele) {
													if (ele1->leads_to[0]->expression[0] == cS &&
														ele1->leads_to[0]->expression[1] == ele) {
														if (ele1->referenced_in.size() == 1 &&
															ele1->referenced_in[0] == exp21	) {
															cout << "Eliminating indirect left recursion success..." << endl;
														} else {
															cout << "Error in indirect left recursion" << endl;
														}

													} else {
														cout << "Error in indirect left recursion" << endl;
													}
												} else {
													cout << "Error in indirect left recursion" << endl;
												}
											} else {
												cout << "Error in indirect left recursion" << endl;
											}
										} else {
											cout << "Error in indirect left recursion" << endl;
										}
									} else {
										cout << "Error in indirect left recursion" << endl;
									}
								} else {
									cout << "Error in indirect left recursion" << endl;
								}
							} else {
								cout << "Error in indirect left recursion" << endl;
							}
						} else {
							cout << "Error in indirect left recursion" << endl;
						}
					} else {
						cout << "Error in indirect left recursion" << endl;
					}
				} else {
					cout << "Error in indirect left recursion" << endl;
				}
			} else {
				cout << "Error in indirect left recursion" << endl;
			}
		} else {
			cout << "Error in indirect left recursion" << endl;
		}
	} else {
		cout << "Error in indirect left recursion" << endl;
	}
}



