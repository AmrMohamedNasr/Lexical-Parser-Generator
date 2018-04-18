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
	private:
		bool check_direct_left_recursion(GrammarElement *rule);
		void remove_direct_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions);
		void remove_indirect_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions);
		bool check_indirect_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions, int index);
	public:
		void remove_left_recursion(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions);
		void left_factor(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions);
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_LL_CONVERTER_LLCONVERTER_H_ */
