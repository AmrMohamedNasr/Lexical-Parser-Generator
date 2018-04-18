/*
 * GrammarElement.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMARELEMENT_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMARELEMENT_H_

#include <string>
#include <vector>

using namespace std;


enum ElementType {TERMINAL, NON_TERMINAL};

class GrammarElement {
	public:
		string name;
		ElementType type;
		virtual ~GrammarElement() = default;
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMARELEMENT_H_ */
