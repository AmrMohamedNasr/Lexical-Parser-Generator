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
}

void test_left_recursion() {
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
	exp11->belongs_to = bexpr;
	exp11->expression = { bexpr, oR, bterm };
	exp11->first_strings = { "not", "(", "true", "false" };
	GrammarExpression* exp12 = new GrammarExpression(bexpr);
	exp12->belongs_to = bexpr;
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

	LlConverter converter;
	converter.remove_left_recursion(&set, &set2);
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
	cout << "Eliminating left recursion success" << endl;

}
void test_indirect_left_recursion() {

}

