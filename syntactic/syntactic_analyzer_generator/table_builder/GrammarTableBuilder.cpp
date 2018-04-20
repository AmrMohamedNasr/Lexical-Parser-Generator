/* 
 * GrammarTableBuilder.cpp
 * Created on: 4/20/18
 *     Author: marc
 */

#include "GrammarTableBuilder.h"
#include "../models/NonTerminal.h"

GrammarTable* GrammarTableBuilder::build_grammar_table(vector<GrammarElement *> *rules) {
    auto grammarTable = new GrammarTable();
    for (auto grammarElement : *rules) {
        NonTerminal* nonTerminal = dynamic_cast<NonTerminal*>(grammarElement);
        if (nonTerminal) {
            cout << nonTerminal->eps << endl;
        }
    }

    return grammarTable;
}