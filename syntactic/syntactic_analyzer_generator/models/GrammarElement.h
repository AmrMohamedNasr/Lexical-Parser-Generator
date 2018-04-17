/*
 * GrammarElement.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMARELEMENT_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMARELEMENT_H_

#include "GrammarExpression.h"
#include <string>
#include <vector>

using namespace std;

class GrammarExpression;

enum ElementType {TERMINAL, NON_TERMINAL};

class GrammarElement {
	public:
		string name;
		ElementType type;
		bool eps;
		bool start;
		vector<GrammarExpression *> leads_to;
		vector<GrammarExpression *> referenced_in;
		unordered_set<GrammarElement *> first_elements;
		unordered_set<string> first_strings;
		bool first_contains_eps;
		unordered_set<GrammarElement *> follow_elements_follow;
		unordered_set<GrammarElement *> follow_elements_first;
		unordered_set<string> follow_strings;
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMARELEMENT_H_ */
