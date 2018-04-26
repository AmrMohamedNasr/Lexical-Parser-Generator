/*
 * ParserTest.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include <iostream>
#include "../../../test_headers/p2_tests.h"
#include "../../grammar_table/model/GrammarTable.h"
#include "Parser.h"
#include "../../syntactic_analyzer_generator/models/GrammarElement.h"

bool compareVectors(vector<string>* v1, vector<string>* v2);
bool test_1();

void test_parser() {
    bool valid = true;
    valid &= test_1();

    if (valid) {
        cout << "Parser tests passed ..\n";
    }
}


/**.
 *      a        b         $
 * S    S->aBa
 * B    B->eps  B->bB
 */
bool test_1() {
    // setup Grammar Table
    GrammarTable grammarTable;
    grammarTable.add_entry("S", "a", {"a", "B", "a"});
    grammarTable.add_entry("B", "a", {});
    grammarTable.add_entry("B", "b", {"b", "B"});
    grammarTable.set_start("S");

    Parser parser;
    parser.set_grammar_table(grammarTable);
    parser.init_parser();
    Token* token1 = new Token(REAL_TOKEN, "", "a");
    Token* token2 = new Token(REAL_TOKEN, "", "b");
    Token* token3 = new Token(REAL_TOKEN, "", "b");
    Token* token4 = new Token(REAL_TOKEN, "", "a");
    parser.derive_token(*token1);
    parser.derive_token(*token2);
    parser.derive_token(*token3);
    parser.derive_token(*token4);

    vector<vector<string>> derivations;
    vector<string> errors;
    parser.finish_derivation(&errors, &derivations);
    vector<vector<string>> expectedDerivations = {{"S"},
                                          {"a", "B", "a"},
                                          {"a", "b", "B", "a"},
                                          {"a" ,"b", "b", "B", "a"},
                                          {"a", "b", "b", "a"}};


    bool valid = true;
    if (derivations.size() != expectedDerivations.size()) {
        cout << "Parser Error:\n";
        cout << "Derivation vector count not matched.Expected(" << expectedDerivations.size() << "), Actual("
             << derivations.size() << ").\n";
        valid = false;
    }

    for (int i = 0; i < derivations.size() && valid; i++) {
        valid &= compareVectors(&expectedDerivations[i], &derivations[i]);
    }

    return valid;
}

/**.
 * @param v1 expected vector
 * @param v2 actual vector
 */
bool compareVectors(vector<string>* v1, vector<string>* v2) {
    bool valid = true;
    if (v1->size() != v2->size()) {
        cout << "Parser Error:\n";
        cout << "Derivation vector count not matched.Expected(" << v1->size() << "), Actual("
             << v2->size() << ").\n";
        cout << "Vector values\n";
        for (int i = 0; i < v2->size(); i++) {
            string s2 = (*v2)[i];
            cout << "Element[" << i << "] = " << s2 << ".\n";
        }

        valid = false;
    }

    for (int i = 0; i < v1->size() && valid; i++) {
        string s1 = (*v1)[i];
        string s2 = (*v2)[i];
        if (s1 != s2) {
            cout << "Expected derivation not matched. Expected(" << s1 << "), Actual(" << s2 <<").\n" ;
            valid = false;
        }
    }

    return valid;
}
