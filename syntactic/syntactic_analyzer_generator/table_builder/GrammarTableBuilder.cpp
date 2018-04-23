/* 
 * GrammarTableBuilder.cpp
 * Created on: 4/20/18
 *     Author: marc
 */

#include "GrammarTableBuilder.h"
#include "../models/NonTerminal.h"

GrammarTable* GrammarTableBuilder::build_grammar_table(vector<GrammarElement *> *rules) {
    auto grammarTable = new GrammarTable();
    bool first = true;
    for (auto grammarElement : *rules) {
        if (grammarElement->getType() == NON_TERMINAL) {
            auto nonTerminal = static_cast<NonTerminal*>(grammarElement);

            if (first) {
                first = false;
                grammarTable->set_start(nonTerminal->getName());
            }

            // loop through every expression in non terminal
            for (auto expression : nonTerminal->leads_to) {
                vector<string> expression_vector;
                // add all available first
                set_expression_vector(&expression_vector, expression);
                for (auto first : expression->first_strings) {
                    if (grammarTable->has_entry(nonTerminal->getName(), first)) {
                        // TODO add error
                    } else {
                        grammarTable->add_entry(nonTerminal->getName(), first, expression_vector);
                    }
                }

                // if expression can lead to eps, add eps to all follows of grammarElement
                if (expression->eps) {
                    for (auto follow : nonTerminal->follow_strings) {
                        if (grammarTable->has_entry(nonTerminal->getName(), follow)) {
                            // TODO add error
                        } else {
                            grammarTable->add_entry(nonTerminal->getName(), follow, {expression_vector});
                        }
                    }
                }
            }

            // if current element leads to eps, add eps o/p to follow
            if (nonTerminal->eps) {
                for (auto follow : nonTerminal->follow_strings) {
                    if (grammarTable->has_entry(nonTerminal->getName(), follow)) {
                        // TODO add error
                    } else {
                        grammarTable->add_entry(nonTerminal->getName(), follow, {});
                    }
                }
            } else { // add synch to follows
                for (auto follow : nonTerminal->follow_strings) {
                    if (!grammarTable->has_entry(nonTerminal->getName(), follow)) {
                        grammarTable->add_synch(nonTerminal->getName(), follow);
                    }
                }
            }
        }
    }

    return grammarTable;
}

void GrammarTableBuilder::set_expression_vector(vector<string>* expression_vector
        , GrammarExpression* grammarExpression) {
    for (auto grammar_element : grammarExpression->expression) {
        expression_vector->push_back(grammar_element->getName());
    }
}