/*
 * GrammarFileParserTest.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include "../../../test_headers/p2_tests.h"

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include "GrammarFileParser.h"

void projectPdfTestCase();

void sheetThreeProblemFourTestCase();

void projectPdfTestCase2();

void sheetThreeProblemFourTestCase2();

using namespace std;

void test_grammar_file_parser() {
    projectPdfTestCase();
//    sheetThreeProblemFourTestCase();
//    projectPdfTestCase2();
//    sheetThreeProblemFourTestCase2();
}

void sheetThreeProblemFourTestCase2() {
    GrammarFileParser fileParser;
    ifstream infile;
    infile.open("./test_files/syntatic_grammar_parser/sheet_3_problem_4.txt");
    if (!infile) {
        cout << "GRAMMAR PARSER TEST : COULDN\"T OPEN WANTED FILE" << endl;
        return;
    }
    vector<GrammarElement *> rules;
    unordered_set<GrammarExpression *> expressions;
    unordered_set<string> terminals;
    unordered_set<string> non_terminals;
    GrammarElement *startRule;

    GrammarElement* SE = new NonTerminal("S", NON_TERMINAL);
    NonTerminal* S = static_cast<NonTerminal*>(SE);
    S->eps = false;
    GrammarElement* RE = new NonTerminal("R", NON_TERMINAL);
    NonTerminal* R = static_cast<NonTerminal*>(RE);
    R->eps = true;
    GrammarElement* TE = new NonTerminal("T", NON_TERMINAL);
    NonTerminal* T = static_cast<NonTerminal*>(TE);
    T->eps = true;
    GrammarElement* UE = new NonTerminal("U", NON_TERMINAL);
    NonTerminal* U = static_cast<NonTerminal*>(UE);
    U->eps = true;
    GrammarElement* VE = new NonTerminal("V", NON_TERMINAL);
    NonTerminal* V = static_cast<NonTerminal*>(VE);
    V->eps = true;

    GrammarElement* s = new GrammarElement("s", TERMINAL);
    GrammarElement* b = new GrammarElement("b", TERMINAL);
    GrammarElement* t = new GrammarElement("t", TERMINAL);
    GrammarElement* u = new GrammarElement("u", TERMINAL);
    GrammarElement* v = new GrammarElement("v", TERMINAL);

    GrammarExpression* ex1 = new GrammarExpression(S);
    ex1->expression = {R, T};
    S->leads_to.push_back(ex1);

    GrammarExpression* ex2 = new GrammarExpression(R);
    ex2->expression = {s, U, R, b};
    R->leads_to.push_back(ex2);

    GrammarExpression* ex3 = new GrammarExpression(T);
    ex3->expression = {V, t, T};
    T->leads_to.push_back(ex3);

    GrammarExpression* ex4 = new GrammarExpression(U);
    ex4->expression = {u, U};
    U->leads_to.push_back(ex4);

    GrammarExpression* ex5 = new GrammarExpression(V);
    ex5->expression = {v, V};
    V->leads_to.push_back(ex5);

    vector<GrammarElement *> expectedRules = {SE, RE, TE, UE, VE};

    vector<string> errors = fileParser.parse_grammar_file(&rules, &expressions, &infile,
                                                          &terminals, &non_terminals, startRule);
    if (!errors.size() == 0) {
        cout << "Syntactic Grammar Parser Errors: " + to_string(errors.size()) + " errors detected" << endl;
        for (int i = 0; i < errors.size(); ++i) {
            cout << errors[i] << endl;
        }
    }

    if (non_terminals.size() != 5) {
        cout << "Syntactic Grammar Parser Errors: Non terminals found " + to_string(non_terminals.size())
                + " instead of 5" << endl;
        for (auto it = non_terminals.begin(); it != non_terminals.end(); it++) {
            cout << (*it) << endl;
        }
    }

    if (rules.size() != expectedRules.size()) {
        cout << "Syntactic Grammar Parser Errors: Rules found " + to_string(rules.size())
                + " instead of 13" << endl;
        for (int i = 0; i < rules.size(); ++i) {
            cout << rules[i]->getName() << endl;
        }
    }

    if (rules.size() == expectedRules.size()) {
        for (int i = 0; i < expectedRules.size(); i++) {
            NonTerminal* rule = static_cast<NonTerminal *>(rules[i]);
            NonTerminal* expectedRule = static_cast<NonTerminal *>(expectedRules[i]);
            if (rule->getName() != expectedRule->getName()) {
                cout << "Grammar Rule with name " << rule->getName() << " instead of "
                     << " instead of " << expectedRule->getName() << endl;
            } else if (rule->getType() != expectedRule->getType()) {
                cout << "Grammar Rule with name " << rule->getName() << " has type "
                     << to_string(rule->getType())
                     << " rules instead of " << to_string(expectedRule->getType()) << endl;
            } else if (rule->eps != expectedRule->eps) {
                cout << "Grammar Rule with name " << rule->getName() << " has eps "
                     << to_string(rule->eps)
                     << " rules instead of " << to_string(expectedRule->eps) << endl;
            } else if (rule->leads_to.size() != expectedRule->leads_to.size()) {
                cout << "Grammar Rule with name " << rule->getName() << " has "
                    << to_string(rule->leads_to.size())
                    << " rules instead of " << to_string(expectedRule->leads_to.size()) << endl;
            } else {
                for (int j = 0; j < rule->leads_to.size(); ++j) {
                    GrammarExpression *expression = rule->leads_to[j];
                    GrammarExpression *expectedExpression = expectedRule->leads_to[j];
                    if (expression->expression.size() != expectedExpression->expression.size()) {
                        cout << "Grammar Rule with name " << rule->getName() << "Expression"
                             << j + 1 << " has size " << to_string(expression->expression.size())
                             << " instead of " << to_string(expectedExpression->expression.size()) << endl;
                    } else {
                        for (int k = 0; k < expression->expression.size(); ++k) {
                            GrammarElement *element = expression->expression[k];
                            GrammarElement *expectedElement = expectedExpression->expression[k];
                            if (element->getName() != expectedElement->getName()) {
                                cout << "Grammar Element Number " << k + 1 << " in expression "
                                     <<  j + 1 << " in rule" << i + 1 << " has name " << element->getName()
                                     << " instead of " << expectedElement->getName() << endl;
                            } else if (element->getType() != expectedElement->getType()) {
                                cout << "Grammar Element Number " << k + 1 << " in expression "
                                     <<  j + 1 << " in rule" << i + 1 << " has type " << element->getType()
                                     << " instead of " << expectedElement->getType() << endl;
                            }
                        }
                    }
                }
            }
        }

//
//        int expectedSizes[] = {1, 1, 1, 1, 1};
//        bool error = false;
//        for (int i = 0; i < 5; ++i) {
//            NonTerminal *nonTerminal = static_cast<NonTerminal *>(rules[i]);
//            if (static_cast<NonTerminal *>(rules[i])->leads_to.size() != expectedSizes[i]) {
//                string name = rules[i]->getName();
//                cout << "Grammar Rule with name " << name << " has "
//                     << to_string(static_cast<NonTerminal *>(rules[i])->leads_to.size())
//                     << " rules instead of " << to_string(expectedSizes[i]) << endl;
//                error = true;
//            }
//        }
//        if (!error) {
//            NonTerminal* S = static_cast<NonTerminal *>(rules[0]);
//            if (S->leads_to[0]->expression.size() != 2 || S->eps ||
//                S->leads_to[0]->expression[0]->getName() != "R" ||
//                S->leads_to[0]->expression[1]->getName() != "T") {
//                cout << "Error in expression 1 in S" << endl;
//            }
//
//            NonTerminal* R = static_cast<NonTerminal *>(rules[1]);
//            if (R->leads_to[0]->expression.size() != 4 || !R->eps ||
//                R->leads_to[0]->expression[0]->getName() != "s" ||
//                R->leads_to[0]->expression[1]->getName() != "U" ||
//                R->leads_to[0]->expression[2]->getName() != "R" ||
//                R->leads_to[0]->expression[3]->getName() != "b") {
//                cout << "Error in expression 1 in R" << endl;
//            }
//
//            NonTerminal* T = static_cast<NonTerminal *>(rules[2]);
//            if (T->leads_to[0]->expression.size() != 3 || !T->eps ||
//                T->leads_to[0]->expression[0]->getName() != "V" ||
//                T->leads_to[0]->expression[1]->getName() != "t" ||
//                T->leads_to[0]->expression[2]->getName() != "T") {
//                cout << "Error in expression 1 in T" << endl;
//            }
//
//            NonTerminal* U = static_cast<NonTerminal *>(rules[3]);
//            if (U->leads_to[0]->expression.size() != 2 || !U->eps ||
//                U->leads_to[0]->expression[0]->getName() != "u" ||
//                U->leads_to[0]->expression[1]->getName() != "U") {
//                cout << "Error in expression 1 in U" << endl;
//            }
//
//            NonTerminal* V = static_cast<NonTerminal *>(rules[4]);
//            if (V->leads_to[0]->expression.size() != 2 || !V->eps ||
//                V->leads_to[0]->expression[0]->getName() != "v" ||
//                V->leads_to[0]->expression[1]->getName() != "V") {
//                cout << "Error in expression 1 in V" << endl;
//            }
//        }
    }
}

void projectPdfTestCase2() {

}

void sheetThreeProblemFourTestCase() {
    GrammarFileParser fileParser;
    ifstream infile;
    infile.open("./test_files/syntatic_grammar_parser/sheet_3_problem_4.txt");
    if (!infile) {
        cout << "GRAMMAR PARSER TEST : COULDN\"T OPEN WANTED FILE" << endl;
        return;
    }
    vector<GrammarElement *> rules;
    unordered_set<GrammarExpression *> expressions;
    unordered_set<string> terminals;
    unordered_set<string> non_terminals;
    GrammarElement *startRule;
    vector<string> errors = fileParser.parse_grammar_file(&rules, &expressions, &infile,
                                                          &terminals, &non_terminals, startRule);
    if (!errors.size() == 0) {
        cout << "Syntactic Grammar Parser Errors: " + to_string(errors.size()) + " errors detected" << endl;
        for (int i = 0; i < errors.size(); ++i) {
            cout << errors[i] << endl;
        }
    }

    if (non_terminals.size() != 5) {
        cout << "Syntactic Grammar Parser Errors: Non terminals found " + to_string(non_terminals.size())
                + " instead of 5" << endl;
        for (auto it = non_terminals.begin(); it != non_terminals.end(); it++) {
            cout << (*it) << endl;
        }
    }

    if (rules.size() != 5) {
        cout << "Syntactic Grammar Parser Errors: Rules found " + to_string(rules.size())
                + " instead of 13" << endl;
        for (int i = 0; i < rules.size(); ++i) {
            cout << rules[i]->getName() << endl;
        }
    }

    if (rules.size() == 5) {
        int expectedSizes[] = {1, 1, 1, 1, 1};
        bool error = false;
        for (int i = 0; i < 5; ++i) {
            NonTerminal *nonTerminal = static_cast<NonTerminal *>(rules[i]);
            if (static_cast<NonTerminal *>(rules[i])->leads_to.size() != expectedSizes[i]) {
                string name = rules[i]->getName();
                cout << "Grammar Rule with name " << name << " has "
                     << to_string(static_cast<NonTerminal *>(rules[i])->leads_to.size())
                     << " rules instead of " << to_string(expectedSizes[i]) << endl;
                error = true;
            }
        }
        if (!error) {
            NonTerminal* S = static_cast<NonTerminal *>(rules[0]);
            if (S->leads_to[0]->expression.size() != 2 || S->eps ||
                S->leads_to[0]->expression[0]->getName() != "R" ||
                S->leads_to[0]->expression[1]->getName() != "T") {
                cout << "Error in expression 1 in S" << endl;
            }

            NonTerminal* R = static_cast<NonTerminal *>(rules[1]);
            if (R->leads_to[0]->expression.size() != 4 || !R->eps ||
                R->leads_to[0]->expression[0]->getName() != "s" ||
                R->leads_to[0]->expression[1]->getName() != "U" ||
                R->leads_to[0]->expression[2]->getName() != "R" ||
                R->leads_to[0]->expression[3]->getName() != "b") {
                cout << "Error in expression 1 in R" << endl;
            }

            NonTerminal* T = static_cast<NonTerminal *>(rules[2]);
            if (T->leads_to[0]->expression.size() != 3 || !T->eps ||
                T->leads_to[0]->expression[0]->getName() != "V" ||
                T->leads_to[0]->expression[1]->getName() != "t" ||
                T->leads_to[0]->expression[2]->getName() != "T") {
                cout << "Error in expression 1 in T" << endl;
            }

            NonTerminal* U = static_cast<NonTerminal *>(rules[3]);
            if (U->leads_to[0]->expression.size() != 2 || !U->eps ||
                U->leads_to[0]->expression[0]->getName() != "u" ||
                U->leads_to[0]->expression[1]->getName() != "U") {
                cout << "Error in expression 1 in U" << endl;
            }

            NonTerminal* V = static_cast<NonTerminal *>(rules[4]);
            if (V->leads_to[0]->expression.size() != 2 || !V->eps ||
                V->leads_to[0]->expression[0]->getName() != "v" ||
                V->leads_to[0]->expression[1]->getName() != "V") {
                cout << "Error in expression 1 in V" << endl;
            }
        }
    }
}

void projectPdfTestCase() {
    GrammarFileParser fileParser;
    ifstream infile;
    infile.open("./test_files/syntatic_grammar_parser/correct_rules.txt");
    if (!infile) {
        cout << "GRAMMAR PARSER TEST : COULDN\"T OPEN WANTED FILE" << endl;
        return;
    }
    vector<GrammarElement *> rules;
    unordered_set<GrammarExpression *> expressions;
    unordered_set<string> terminals;
    unordered_set<string> non_terminals;
    GrammarElement *startRule;
    vector<string> errors = fileParser.parse_grammar_file(&rules, &expressions, &infile,
                                                          &terminals, &non_terminals, startRule);

    if (!errors.size() == 0) {
        cout << "Syntactic Grammar Parser Errors: " + to_string(errors.size()) + " errors detected" << endl;
        for (int i = 0; i < errors.size(); ++i) {
            cout << errors[i] << endl;
        }
    }

    if (non_terminals.size() != 13) {
        cout << "Syntactic Grammar Parser Errors: Non terminals found " + to_string(non_terminals.size())
                + " instead of 13" << endl;
        for (auto it = non_terminals.begin(); it != non_terminals.end(); it++) {
            cout << (*it) << endl;
        }
    }

    if (rules.size() != 13) {
        cout << "Syntactic Grammar Parser Errors: Rules found " + to_string(rules.size())
                + " instead of 13" << endl;
        for (int i = 0; i < rules.size(); ++i) {
            cout << rules[i]->getName() << endl;
        }
    }

    if (rules.size() == 13) {
        int expectedSizes[] = {1, 2, 4, 1, 1, 1, 1, 2, 2, 3, 2, 2, 3};
        bool error = false;
        for (int i = 0; i < 13; ++i) {
            NonTerminal* nonTerminal = static_cast<NonTerminal *>(rules[i]);
            if (static_cast<NonTerminal *>(rules[i])->leads_to.size() != expectedSizes[i]) {
                string name = rules[i]->getName();
                cout << "Grammar Rule with name " << name <<" has " << to_string(static_cast<NonTerminal *>(rules[i])->leads_to.size())
                     << " rules instead of " << to_string(expectedSizes[i]) << endl;
                error = true;
            }
        }

        if (!error) {
            NonTerminal* METHOD_BODY = static_cast<NonTerminal *>(rules[0]);
            if (METHOD_BODY->leads_to[0]->expression.size() != 1 || METHOD_BODY->leads_to[0]->expression[0]->getName() != "STATEMENT_LIST") {
                cout << "Error in expression 1 in METHOD_BODY" << endl;
            }

            NonTerminal* STATEMENT_LIST = static_cast<NonTerminal *>(rules[1]);
            if (STATEMENT_LIST->leads_to[0]->expression.size() != 1 || STATEMENT_LIST->leads_to[0]->expression[0]->getName() != "STATEMENT") {
                cout << "Error in expression 1 in STATEMENT_LIST" << endl;
            }

            if (STATEMENT_LIST->leads_to[1]->expression.size() != 2
                || STATEMENT_LIST->leads_to[1]->expression[0]->getName() != "STATEMENT_LIST"
                || STATEMENT_LIST->leads_to[1]->expression[1]->getName() != "STATEMENT") {
                cout << "Error in expression 2 in STATEMENT_LIST" << endl;
            }

            NonTerminal* STATEMENT = static_cast<NonTerminal *>(rules[2]);
            if (STATEMENT->leads_to[0]->expression.size() != 1
                || STATEMENT->leads_to[0]->expression[0]->getName() != "DECLARATION") {
                cout << "Error in expression 1 in STATEMENT" << endl;
            }

            if (STATEMENT->leads_to[1]->expression.size() != 1
                || STATEMENT->leads_to[1]->expression[0]->getName() != "IF") {
                cout << "Error in expression 2 in STATEMENT" << endl;
            }

            if (STATEMENT->leads_to[2]->expression.size() != 1
                || STATEMENT->leads_to[2]->expression[0]->getName() != "WHILE") {
                cout << "Error in expression 3 in STATEMENT" << endl;
            }

            if (STATEMENT->leads_to[3]->expression.size() != 1
                || STATEMENT->leads_to[3]->expression[0]->getName() != "ASSIGNMENT") {
                cout << "Error in expression 4 in STATEMENT" << endl;
            }

            NonTerminal* DECLARATION = static_cast<NonTerminal *>(rules[3]);
            if (DECLARATION->leads_to[0]->expression.size() != 3
                || DECLARATION->leads_to[0]->expression[0]->getName() != "PRIMITIVE_TYPE"
                || DECLARATION->leads_to[0]->expression[1]->getName() != "id"
                || DECLARATION->leads_to[0]->expression[2]->getName() != ";") {
                cout << "Error in expression 1 in DECLARATION" << endl;
            }

            NonTerminal* IF = static_cast<NonTerminal *>(rules[4]);
            if (IF->leads_to[0]->expression.size() != 11
                || IF->leads_to[0]->expression[0]->getName() != "if"
                || IF->leads_to[0]->expression[1]->getName() != "("
                || IF->leads_to[0]->expression[2]->getName() != "EXPRESSION"
                || IF->leads_to[0]->expression[3]->getName() != ")"
                || IF->leads_to[0]->expression[4]->getName() != "{"
                || IF->leads_to[0]->expression[5]->getName() != "STATEMENT"
                || IF->leads_to[0]->expression[6]->getName() != "}"
                || IF->leads_to[0]->expression[7]->getName() != "else"
                || IF->leads_to[0]->expression[8]->getName() != "{"
                || IF->leads_to[0]->expression[9]->getName() != "STATEMENT"
                || IF->leads_to[0]->expression[10]->getName() != "}") {
                cout << "Error in expression 1 in IF" << endl;
            }

            NonTerminal* WHILE = static_cast<NonTerminal *>(rules[5]);
            if (WHILE->leads_to[0]->expression.size() != 7
                || WHILE->leads_to[0]->expression[0]->getName() != "while"
                || WHILE->leads_to[0]->expression[1]->getName() != "("
                || WHILE->leads_to[0]->expression[2]->getName() != "EXPRESSION"
                || WHILE->leads_to[0]->expression[3]->getName() != ")"
                || WHILE->leads_to[0]->expression[4]->getName() != "{"
                || WHILE->leads_to[0]->expression[5]->getName() != "STATEMENT"
                || WHILE->leads_to[0]->expression[6]->getName() != "}") {
                cout << "Error in expression 1 in WHILE" << endl;
            }

            NonTerminal* ASSIGNMENT = static_cast<NonTerminal *>(rules[6]);
            if (ASSIGNMENT->leads_to[0]->expression.size() != 4
                || ASSIGNMENT->leads_to[0]->expression[0]->getName() != "id"
                || ASSIGNMENT->leads_to[0]->expression[1]->getName() != "="
                || ASSIGNMENT->leads_to[0]->expression[2]->getName() != "EXPRESSION"
                || ASSIGNMENT->leads_to[0]->expression[3]->getName() != ";") {
                cout << "Error in expression 1 in ASSIGNMENT" << endl;
            }

            NonTerminal* PRIMITIVE_TYPE = static_cast<NonTerminal *>(rules[7]);
            if (PRIMITIVE_TYPE->leads_to[0]->expression.size() != 1
                || PRIMITIVE_TYPE->leads_to[0]->expression[0]->getName() != "int") {
                cout << "Error in expression 1 in PRIMITIVE_TYPE" << endl;
            }

            if (PRIMITIVE_TYPE->leads_to[1]->expression.size() != 1
                || PRIMITIVE_TYPE->leads_to[1]->expression[0]->getName() != "float") {
                cout << "Error in expression 2 in PRIMITIVE_TYPE" << endl;
            }

            NonTerminal* EXPRESSION = static_cast<NonTerminal *>(rules[8]);
            if (EXPRESSION->leads_to[0]->expression.size() != 1
                || EXPRESSION->leads_to[0]->expression[0]->getName() != "SIMPLE_EXPRESSION") {
                cout << "Error in expression 1 in EXPRESSION" << endl;
            }

            if (EXPRESSION->leads_to[1]->expression.size() != 3
                || EXPRESSION->leads_to[1]->expression[0]->getName() != "SIMPLE_EXPRESSION"
                || EXPRESSION->leads_to[1]->expression[1]->getName() != "relop"
                || EXPRESSION->leads_to[1]->expression[2]->getName() != "SIMPLE_EXPRESSION") {
                cout << "Error in expression 2 in EXPRESSION" << endl;
            }

            NonTerminal* SIMPLE_EXPRESSION = static_cast<NonTerminal *>(rules[9]);
            if (SIMPLE_EXPRESSION->leads_to[0]->expression.size() != 1
                || SIMPLE_EXPRESSION->leads_to[0]->expression[0]->getName() != "TERM") {
                cout << "Error in expression 1 in SIMPLE_EXPRESSION" << endl;
            }

            if (SIMPLE_EXPRESSION->leads_to[1]->expression.size() != 2
                || SIMPLE_EXPRESSION->leads_to[1]->expression[0]->getName() != "SIGN"
                || SIMPLE_EXPRESSION->leads_to[1]->expression[1]->getName() != "TERM") {
                cout << "Error in expression 2 in SIMPLE_EXPRESSION" << endl;
            }

            if (SIMPLE_EXPRESSION->leads_to[2]->expression.size() != 3
                || SIMPLE_EXPRESSION->leads_to[2]->expression[0]->getName() != "SIMPLE_EXPRESSION"
                || SIMPLE_EXPRESSION->leads_to[2]->expression[1]->getName() != "addop"
                || SIMPLE_EXPRESSION->leads_to[2]->expression[2]->getName() != "TERM") {
                cout << "Error in expression 3 in SIMPLE_EXPRESSION" << endl;
            }

            NonTerminal* TERM = static_cast<NonTerminal *>(rules[10]);
            if (TERM->leads_to[0]->expression.size() != 1
                || TERM->leads_to[0]->expression[0]->getName() != "FACTOR") {
                cout << "Error in expression 1 in TERM" << endl;
            }

            if (TERM->leads_to[1]->expression.size() != 3
                || TERM->leads_to[1]->expression[0]->getName() != "TERM"
                || TERM->leads_to[1]->expression[1]->getName() != "mulop"
                || TERM->leads_to[1]->expression[2]->getName() != "FACTOR") {
                cout << "Error in expression 2 in TERM" << endl;
            }

            NonTerminal* SIGN = static_cast<NonTerminal *>(rules[11]);
            if (SIGN->leads_to[0]->expression.size() != 1
                || SIGN->leads_to[0]->expression[0]->getName() != "+") {
                cout << "Error in expression 1 in SIGN" << endl;
            }

            if (SIGN->leads_to[1]->expression.size() != 1
                || SIGN->leads_to[1]->expression[0]->getName() != "-") {
                cout << "Error in expression 2 in SIGN" << endl;
            }

            NonTerminal* FACTOR = static_cast<NonTerminal *>(rules[12]);
            if (FACTOR->leads_to[0]->expression.size() != 1
                || FACTOR->leads_to[0]->expression[0]->getName() != "id") {
                cout << "Error in expression 1 in FACTOR" << endl;
            }

            if (FACTOR->leads_to[1]->expression.size() != 1
                || FACTOR->leads_to[1]->expression[0]->getName() != "num") {
                cout << "Error in expression 2 in FACTOR" << endl;
            }

            if (FACTOR->leads_to[2]->expression.size() != 3
                || FACTOR->leads_to[2]->expression[0]->getName() != "("
                || FACTOR->leads_to[2]->expression[1]->getName() != "EXPRESSION"
                || FACTOR->leads_to[2]->expression[2]->getName() != ")") {
                cout << "Error in expression 3 in FACTOR" << endl;
            }
        }
    }
}
