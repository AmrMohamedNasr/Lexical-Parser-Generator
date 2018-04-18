/*
 * GrammarExpression.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMAREXPRESSION_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMAREXPRESSION_H_

#include "GrammarElement.h"
#include "NonTerminal.h"
#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

class NonTerminal;

class GrammarExpression {
	public:
		vector<GrammarElement *> expression;
		NonTerminal * belongs_to;
		bool eps;
		unordered_set<string> first_strings;
		void print_expression(void) {
			cout << "Expression : ";
			for (unsigned i = 0; i < expression.size(); i++) {
				cout << expression[i]->name << " ";
			}
			cout << endl;
			cout << "First : ";
			for (auto it = first_strings.begin(); it != first_strings.end(); it++) {
				cout << "{\"" << *it << "\"}" << ", ";
			}
			cout << endl;
			cout << "Belongs to : " << belongs_to->name << endl;
		}
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMAREXPRESSION_H_ */
