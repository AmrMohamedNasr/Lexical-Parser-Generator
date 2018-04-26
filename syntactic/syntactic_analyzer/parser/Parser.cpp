/* 
 * Parser.cpp
 * Created on: 4/26/18
 *     Author: marc
 */

#include "Parser.h"

void Parser::init_parser() {
    current_derived_index = 0;
    rules.push("$");
    rules.push(table.get_start());
}

void Parser::set_grammar_table(GrammarTable gTable) {
    this->table = gTable;
}

void Parser::derive_token(Token token) {
    string value = token.token_class;

    // pop TOS
    string topStackVal = rules.top();
    rules.pop();

    // if it's non terminal, exchange with it's value from the table
    while (table.is_non_terminal(topStackVal)) {
        if (table.has_entry(topStackVal, value)) {
            vector<string> deriv = table.get_entry(topStackVal, value);

        } else if (table.is_synch(topStackVal, value)) {

        } else {

        }
    }

    if (topStackVal == value) {

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