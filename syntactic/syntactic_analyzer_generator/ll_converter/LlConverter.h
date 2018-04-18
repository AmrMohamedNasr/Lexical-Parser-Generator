/*
 * LlConverter.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_LL_CONVERTER_LLCONVERTER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_LL_CONVERTER_LLCONVERTER_H_

#include <vector>
#include <unordered_set>
#include "../models/GrammarElement.h"
#include "../models/GrammarExpression.h"

using namespace std;

class LlConverter {
	public:
		void remove_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions);
		void left_factor(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions);
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_LL_CONVERTER_LLCONVERTER_H_ */
