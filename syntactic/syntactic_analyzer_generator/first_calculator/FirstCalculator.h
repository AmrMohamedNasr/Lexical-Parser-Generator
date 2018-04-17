/*
 * FirstCalculator.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FIRST_CALCULATOR_FIRSTCALCULATOR_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FIRST_CALCULATOR_FIRSTCALCULATOR_H_

#include <vector>
#include <unordered_set>
#include "../models/GrammarElement.h"

using namespace std;

class FirstCalculator {
	public:
		void get_first_sets(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions);
};



#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FIRST_CALCULATOR_FIRSTCALCULATOR_H_ */
