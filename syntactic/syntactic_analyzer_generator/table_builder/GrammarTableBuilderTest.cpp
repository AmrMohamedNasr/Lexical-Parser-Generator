/*
 * GrammarTableBuilderTest.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include "../../../test_headers/p2_tests.h"
#include "GrammarTableBuilder.h"
#include "../models/NonTerminal.h"

void test_grammar_table_builder() {
    GrammarTableBuilder grammarTableBuilder;
    NonTerminal nonTerminal1;
    NonTerminal nonTerminal2;
    nonTerminal1.eps = true;
    nonTerminal2.eps = false;
    GrammarElement g;
    auto a = new vector<GrammarElement*>();
    a->push_back(&nonTerminal1);
    a->push_back(&nonTerminal2);

    grammarTableBuilder.build_grammar_table(a);
}
