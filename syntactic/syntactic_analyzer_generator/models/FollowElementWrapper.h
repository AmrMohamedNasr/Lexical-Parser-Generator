/*
 * FollowElementWrapper.h
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FOLLOWELEMENTWRAPPER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FOLLOWELEMENTWRAPPER_H_

#include "GrammarElement.h"
#include <unordered_set>
#include <string>

using namespace std;

class FollowElementWrapper {
	public:
		GrammarElement * core;
		unordered_set<FollowElementWrapper *> follow_elements_follow;
		unordered_set<FollowElementWrapper *> follow_elements_first;
		unordered_set<string> follow_strings;
};



#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FOLLOWELEMENTWRAPPER_H_ */
