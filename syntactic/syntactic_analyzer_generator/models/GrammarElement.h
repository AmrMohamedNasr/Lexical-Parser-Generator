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
    GrammarElement(string name, ElementType type);
    string getName();
    ElementType getType();

    private:
    string name;
    ElementType type;
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMARELEMENT_H_ */
