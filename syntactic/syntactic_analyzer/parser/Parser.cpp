/* 
 * Parser.cpp
 * Created on: 4/26/18
 *     Author: marc
 */

#include "Parser.h"

void Parser::init_parser() {
    current_derived_index = 0;
    rules.push_back("$");
    rules.push_back(table.get_start());
}

void Parser::set_grammar_table(GrammarTable gTable) {
    this->table = gTable;
}

void Parser::derive_token(Token token) {
    string value = token.token_class;

    // pop TOS
    string topStackVal = rules.back();
    rules.pop_back();
    derivations.push_back({topStackVal});

    // if it's non terminal, exchange with it's value from the table
    while (table.is_non_terminal(topStackVal)) {
        if (table.has_entry(topStackVal, value)) {
            // add to stack
            vector<string> rule = table.get_entry(topStackVal, value);
            add_new_rule(&rule);

            vector<string> derivation;
            // add new derivation
            add_matched_tokens(&derivation);
            add_current_rules(&derivation);
            derivations.push_back(derivation);
        } else if (table.is_synch(topStackVal, value)) {

        } else {
            // Mark error
        }
    }

    if (topStackVal == value) {
        matched_tokens.push_back(topStackVal);
    } else {
        // Mark error
    }
}


void Parser::finish_derivation(vector<string> *rerrors, vector<vector<string>> *rderiv) {
    copy_vector(&errors, rerrors);

    for (auto vec : derivations) {
        rderiv->push_back(vector<string>());
        copy_vector(&vec, &rderiv->back());
    }
}

void Parser::copy_vector(vector<string> *src, vector<string> *destination) {
    destination->assign(src->begin(), src->end());
}

void Parser::add_new_rule(vector<string>* rule) {
    for (long i = rule->size() - 1; i >= 0; i--) {
        rules.push_back((*rule)[i]);
    }
}

void Parser::add_matched_tokens(vector<string> *derivation) {
    for (auto const s : matched_tokens) {
        derivation->push_back(s);
    }
}

void Parser::add_current_rules(vector<string> *derivation) {
    for (long i = rules.size() - 1; i >= 0; i--) {
        derivation->push_back(rules[i]);
    }
}