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
void test_ll_converter() {
	test_left_recursion();
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
	exp32->expression = { closeBracket };
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

	LlConverter converter;
	converter.remove_left_recursion(&set, &set2);
	// if pass integration test passed


}


