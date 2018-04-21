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

void test_direct_left_recursion();
void test_indirect_left_recursion();
void test_direct_left_factoring();
void test_indirect_left_factoring();
void test_ll_converter() {
	//test_direct_left_recursion();
	//test_indirect_left_recursion();
	test_direct_left_factoring();
	//test_indirect_left_factoring();
}

void test_direct_left_recursion() {
	GrammarElement* bterm = new NonTerminal("bterm", NON_TERMINAL);
	GrammarElement* bfactor = new NonTerminal("bfactor", NON_TERMINAL);
	GrammarElement* bexpr = new NonTerminal("bexpr", NON_TERMINAL);
	GrammarElement* oR = new GrammarElement("or", TERMINAL);
	GrammarElement* openBracket = new GrammarElement("(", TERMINAL);
	GrammarElement* closeBracket = new GrammarElement(")", TERMINAL);
	GrammarElement* aND = new GrammarElement("and", TERMINAL);
	GrammarElement* nOT = new GrammarElement("not", TERMINAL);
	GrammarElement* tRUE = new GrammarElement("true", TERMINAL);
	GrammarElement* fALSE = new GrammarElement("false", TERMINAL);
	// first rule
	GrammarExpression* exp11 = new GrammarExpression(bexpr);
	exp11->expression = { bexpr, oR, bterm };
	exp11->first_strings = { "not", "(", "true", "false" };
	GrammarExpression* exp12 = new GrammarExpression(bexpr);
	exp12->expression = { bterm };
	exp12->first_strings = { "not", "(", "true", "false" };
	static_cast<NonTerminal*>(bexpr)->referenced_in = {exp11 };
	static_cast<NonTerminal*>(bexpr)->leads_to = { exp11, exp12 };
	static_cast<NonTerminal*>(bexpr)->first_strings = { "not", "(", "true", "false" };
	static_cast<NonTerminal*>(bexpr)->follow_strings = { "$", ")"};
	// second rule
	GrammarExpression* exp21 = new GrammarExpression(bterm);
	exp21->expression = { bterm, aND, bfactor };
	exp21->first_strings = { "not", "(", "true", "false" };
	GrammarExpression* exp22 = new GrammarExpression(bterm);
	exp22->expression = { bfactor };
	exp22->first_strings = { "not", "(", "true", "false" };
	static_cast<NonTerminal*>(bterm)->referenced_in = { exp11, exp12, exp21 };
	static_cast<NonTerminal*>(bterm)->leads_to = { exp21, exp22 };
	static_cast<NonTerminal*>(bterm)->first_strings = { "not", "(", "true", "false" };
	static_cast<NonTerminal*>(bterm)->follow_strings = { "$", "or", ")"};
	//third rule
	GrammarExpression* exp31 = new GrammarExpression(bfactor);
	exp31->expression = { nOT, bfactor };
	exp31->first_strings = {"not"};
	GrammarExpression* exp32 = new GrammarExpression(bfactor);
	exp32->expression = { openBracket, bexpr, closeBracket };
	exp32->first_strings = {"("};
	GrammarExpression* exp33 = new GrammarExpression(bfactor);
	exp33->expression = { tRUE };
	exp33->first_strings = {"true"};
	GrammarExpression* exp34 = new GrammarExpression(bfactor);
	exp34->expression = { fALSE };
	exp34->first_strings = {"false"};
	static_cast<NonTerminal*>(bfactor)->referenced_in = { exp31, exp21, exp22 };
	static_cast<NonTerminal*>(bfactor)->leads_to = { exp31, exp32, exp33, exp34 };
	static_cast<NonTerminal*>(bfactor)->first_strings = { "not", "(", "true", "false" };
	static_cast<NonTerminal*>(bfactor)->follow_strings = { "$", "or", ")", "and" };

	vector <GrammarElement* > set = {bexpr, bterm, bfactor, nOT, aND, oR, closeBracket, openBracket, tRUE, fALSE };
	unordered_set <GrammarExpression*> set2 = {exp11, exp12, exp21, exp22, exp31, exp32, exp33, exp34};
	unordered_set <NonTerminal*> changed;
	LlConverter converter;
	converter.remove_left_recursion(&set, &set2, &changed);
	// if pass integration test passed

	if (set[0]->getName() == "bexpr") {
		NonTerminal * temp = static_cast<NonTerminal *>(set[0]);
		if (temp->leads_to[0]->expression[0] != set[1]) {
			cout << "Error in Left recursion" << "Expected reference to \" bterm \" " <<endl;
		}
		if (temp->leads_to[0]->expression[1] != set[10]) {
			cout << "Error in Left recursion" << "Expected reference to \" bterm \" " <<endl;
		}
	} else {
		cout << "Error in Referencing sets" << endl;
	}
	cout << "Eliminating direct left recursion success..." << endl;
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
	NonTerminal* a = new NonTerminal("A", NON_TERMINAL);
	NonTerminal* b = new NonTerminal("B", NON_TERMINAL);
	NonTerminal* c = new NonTerminal("C", NON_TERMINAL);
	NonTerminal* d = new NonTerminal("D", NON_TERMINAL);

	GrammarElement* x = new GrammarElement("x", TERMINAL);
	GrammarElement* y = new GrammarElement("y", TERMINAL);
	GrammarElement* cS = new GrammarElement("c", TERMINAL);
	GrammarElement* dS = new GrammarElement("d", TERMINAL);

	GrammarExpression* exp11 = new GrammarExpression(a);
	exp11->expression = { b, x, y};
	b->referenced_in.push_back(exp11);
	GrammarExpression* exp12 = new GrammarExpression(a);
	exp12->expression = { x };
	GrammarExpression* exp21 = new GrammarExpression(b);
	exp21->expression = { c, d};
	d->referenced_in.push_back(exp21);
	c->referenced_in.push_back(exp21);
	GrammarExpression* exp31 = new GrammarExpression(c);
	exp31->expression = { a };
	a->referenced_in.push_back(exp31);
	GrammarExpression* exp32 = new GrammarExpression(c);
	exp32->expression = { cS };
	GrammarExpression* exp41 = new GrammarExpression(d);
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
	NonTerminal * ele =  static_cast<NonTerminal *> (set[8]);
	NonTerminal * ele1 =  static_cast<NonTerminal *> (set[2]);
	if (ele->getName() == "C'" ) {
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
	delete a;
	delete b;
	delete c;
	delete d;
	delete x;
	delete y;
	delete cS;
	delete dS;
}

void test_direct_left_factoring() {
	NonTerminal* a = new NonTerminal("A", NON_TERMINAL);
	NonTerminal* b = new NonTerminal("B", NON_TERMINAL);
	GrammarElement* aS = new GrammarElement("a", TERMINAL);
	GrammarElement* bS = new GrammarElement("b", TERMINAL);
	GrammarElement* cS = new GrammarElement("c", TERMINAL);
	GrammarElement* dS = new GrammarElement("d", TERMINAL);
	GrammarElement* gS = new GrammarElement("g", TERMINAL);
	GrammarElement* eS = new GrammarElement("e", TERMINAL);
	GrammarElement* fS = new GrammarElement("f", TERMINAL);

	GrammarExpression* exp11 = new GrammarExpression(a);
	exp11->expression = { aS, bS, b };
	GrammarExpression* exp12 = new GrammarExpression(a);
	exp12->expression = { aS, b };
	GrammarExpression* exp13 = new GrammarExpression(a);
	exp13->expression = { cS, dS, gS };
	GrammarExpression* exp14 = new GrammarExpression(a);
	exp14->expression = { cS, dS, eS, b };
	GrammarExpression* exp15 = new GrammarExpression(a);
	exp15->expression = { cS, dS, fS, b };
	vector <GrammarElement* > set = {a};
	unordered_set <GrammarExpression*> set2 = {exp11, exp12, exp13, exp14, exp15};
	unordered_set <NonTerminal*> set3;
	LlConverter converter;
	converter.left_factor(&set, &set2, &set3);
	NonTerminal * ele0 =  static_cast<NonTerminal *> (set[0]);
	NonTerminal * ele =  static_cast<NonTerminal *> (set[1]);
	NonTerminal * ele2 =  static_cast<NonTerminal *> (set[2]);
	if (set.size() == 3) {
		if (set2.size() == 7) {
			if (ele->getName() == "A_1") {
				if (ele->getType() == NON_TERMINAL) {
					if (ele->leads_to[0]->expression[0] == bS ||
							ele->leads_to[0]->expression[0] == b) {
						if (ele->leads_to[1]->expression[0] == bS ||
							ele->leads_to[1]->expression[0] == b) {
							if (ele->leads_to.size() == 2) {
								if (ele->leads_to[0]->belongs_to == ele &&
									ele->leads_to[0]->belongs_to == ele) {
									if (ele->referenced_in[0] == ele0->leads_to[0] ||
										ele->referenced_in[0] == ele0->leads_to[1]	) {
										if (ele2->leads_to.size() == 3) {
											if (ele2->leads_to[0]->expression[0] == gS ||
												ele2->leads_to[0]->expression[0] == eS ||
												ele2->leads_to[0]->expression[0] == fS) {
												if (ele2->leads_to[1]->expression[0] == gS ||
													ele2->leads_to[1]->expression[0] == eS ||
													ele2->leads_to[1]->expression[0] == fS) {
													if (ele2->referenced_in[0] == ele0->leads_to[0] ||
														ele2->referenced_in[0] == ele0->leads_to[1]) {
														if (ele2->getName() == "A_2") {
															cout << "Direct left factoring Success..." << endl;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}


}

