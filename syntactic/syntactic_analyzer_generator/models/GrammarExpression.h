/*
 * GrammarExpression.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMAREXPRESSION_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMAREXPRESSION_H_

#include "GrammarElement.h"
#include <vector>
#include <unordered_set>

using namespace std;

class GrammarElement;

class GrammarExpression {
	public:
	GrammarExpression(GrammarElement *element);

	vector<GrammarElement *> expression;
		GrammarElement * belongs_to;
		bool eps;
		unordered_set<string> first_strings;
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMAREXPRESSION_H_ */
