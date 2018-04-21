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
    // setup mock object
    GrammarElement *METHOD_BODY_E = new NonTerminal("METHOD_BODY", NON_TERMINAL);
    GrammarElement *STATEMENT_LIST_E = new NonTerminal("STATEMENT_LIST", NON_TERMINAL);
    GrammarElement *STATEMENT_E = new NonTerminal("STATEMENT", NON_TERMINAL);
    GrammarElement *DECLARATION_E = new NonTerminal("DECLARATION", NON_TERMINAL);
    GrammarElement *PRIMITIVE_TYPE_E = new NonTerminal("PRIMITIVE_TYPE", NON_TERMINAL);
    GrammarElement *IF_E = new NonTerminal("IF", NON_TERMINAL);
    GrammarElement *WHILE_E = new NonTerminal("WHILE", NON_TERMINAL);
    GrammarElement *ASSIGNMENT_E = new NonTerminal("ASSIGNMENT", NON_TERMINAL);
    GrammarElement *EXPRESSION_E = new NonTerminal("EXPRESSION", NON_TERMINAL);
    GrammarElement *SIMPLE_EXPRESSION_E = new NonTerminal("SIMPLE_EXPRESSION", NON_TERMINAL);
    GrammarElement *TERM_E = new NonTerminal("TERM", NON_TERMINAL);
    GrammarElement *SIGN_E = new NonTerminal("SIGN", NON_TERMINAL);
    GrammarElement *FACTOR_E = new NonTerminal("FACTOR", NON_TERMINAL);

    NonTerminal *METHOD_BODY = static_cast<NonTerminal *>(METHOD_BODY_E);
    NonTerminal *STATEMENT_LIST = static_cast<NonTerminal *>(STATEMENT_LIST_E);
    NonTerminal *STATEMENT = static_cast<NonTerminal *>(STATEMENT_E);
    NonTerminal *DECLARATION = static_cast<NonTerminal *>(DECLARATION_E);
    NonTerminal *IF = static_cast<NonTerminal *>(IF_E);
    NonTerminal *WHILE = static_cast<NonTerminal *>(WHILE_E);
    NonTerminal *ASSIGNMENT = static_cast<NonTerminal *>(ASSIGNMENT_E);
    NonTerminal *PRIMITIVE_TYPE = static_cast<NonTerminal *>(PRIMITIVE_TYPE_E);
    NonTerminal *EXPRESSION = static_cast<NonTerminal *>(EXPRESSION_E);
    NonTerminal *SIMPLE_EXPRESSION = static_cast<NonTerminal *>(SIMPLE_EXPRESSION_E);
    NonTerminal *TERM = static_cast<NonTerminal *>(TERM_E);
    NonTerminal *FACTOR = static_cast<NonTerminal *>(FACTOR_E);
    NonTerminal *SIGN = static_cast<NonTerminal *>(SIGN_E);

    METHOD_BODY->eps = false;
    STATEMENT_LIST->eps = false;
    STATEMENT->eps = false;
    DECLARATION->eps = false;
    IF->eps = false;
    WHILE->eps = false;
    ASSIGNMENT->eps = false;
    PRIMITIVE_TYPE->eps = false;
    EXPRESSION->eps = false;
    SIMPLE_EXPRESSION->eps = false;
    TERM->eps = false;
    SIGN->eps = false;
    FACTOR->eps = false;

    GrammarElement* id_terminal = new GrammarElement("id", TERMINAL);
    GrammarElement* semicolon_terminal = new GrammarElement(";", TERMINAL);
    GrammarElement* int_terminal = new GrammarElement("int", TERMINAL);
    GrammarElement* float_terminal = new GrammarElement("float", TERMINAL);
    GrammarElement* if_terminal = new GrammarElement("if", TERMINAL);
    GrammarElement* openBracket_terminal = new GrammarElement("(", TERMINAL);
    GrammarElement* closedBracket_terminal = new GrammarElement(")", TERMINAL);
    GrammarElement* openCurlyBracket_terminal = new GrammarElement("{", TERMINAL);
    GrammarElement* closedCurlyBracket_terminal = new GrammarElement("}", TERMINAL);
    GrammarElement* else_terminal = new GrammarElement("else", TERMINAL);
    GrammarElement* while_terminal = new GrammarElement("while", TERMINAL);
    GrammarElement* relop_terminal = new GrammarElement("relop", TERMINAL);
    GrammarElement* addop_terminal = new GrammarElement("addop", TERMINAL);
    GrammarElement* mulop_terminal = new GrammarElement("mulop", TERMINAL);
    GrammarElement* equal_terminal = new GrammarElement("=", TERMINAL);
    GrammarElement* num_terminal = new GrammarElement("num", TERMINAL);
    GrammarElement* plus_terminal = new GrammarElement("+", TERMINAL);
    GrammarElement* minus_terminal = new GrammarElement("-", TERMINAL);

    GrammarExpression* ex1 = new GrammarExpression(METHOD_BODY);
    ex1->expression = {STATEMENT_LIST};
    METHOD_BODY->leads_to.push_back(ex1);

    GrammarExpression* ex2 = new GrammarExpression(STATEMENT_LIST);
    ex2->expression = {STATEMENT};
    STATEMENT_LIST->leads_to.push_back(ex2);

    GrammarExpression* ex3 = new GrammarExpression(STATEMENT_LIST);
    ex3->expression = {STATEMENT_LIST, STATEMENT};
    STATEMENT_LIST->leads_to.push_back(ex3);

    GrammarExpression* ex4 = new GrammarExpression(STATEMENT);
    ex4->expression = {DECLARATION};
    STATEMENT->leads_to.push_back(ex4);

    GrammarExpression* ex5 = new GrammarExpression(STATEMENT);
    ex5->expression = {IF};
    STATEMENT->leads_to.push_back(ex5);

    GrammarExpression* ex6 = new GrammarExpression(STATEMENT);
    ex6->expression = {WHILE};
    STATEMENT->leads_to.push_back(ex6);

    GrammarExpression* ex7 = new GrammarExpression(STATEMENT);
    ex7->expression = {ASSIGNMENT};
    STATEMENT->leads_to.push_back(ex7);

    GrammarExpression* ex8 = new GrammarExpression(DECLARATION);
    ex8->expression = {PRIMITIVE_TYPE, id_terminal, semicolon_terminal};
    DECLARATION->leads_to.push_back(ex8);

    GrammarExpression* ex9 = new GrammarExpression(IF);
    ex9->expression = {if_terminal, openBracket_terminal, EXPRESSION, closedBracket_terminal,
                       openCurlyBracket_terminal, STATEMENT, closedCurlyBracket_terminal,
                       else_terminal, openCurlyBracket_terminal, STATEMENT,
                       closedCurlyBracket_terminal};
    IF->leads_to.push_back(ex9);

    GrammarExpression* ex10 = new GrammarExpression(WHILE);
    ex10->expression = {while_terminal, openBracket_terminal, EXPRESSION, closedBracket_terminal,
                        openCurlyBracket_terminal, STATEMENT, closedCurlyBracket_terminal};
    WHILE->leads_to.push_back(ex10);

    GrammarExpression* ex11 = new GrammarExpression(ASSIGNMENT);
    ex11->expression = {id_terminal, equal_terminal, EXPRESSION, semicolon_terminal};
    ASSIGNMENT->leads_to.push_back(ex11);

    GrammarExpression* ex12 = new GrammarExpression(PRIMITIVE_TYPE);
    ex12->expression = {int_terminal};
    PRIMITIVE_TYPE->leads_to.push_back(ex12);

    GrammarExpression* ex13 = new GrammarExpression(PRIMITIVE_TYPE);
    ex13->expression = {float_terminal};
    PRIMITIVE_TYPE->leads_to.push_back(ex13);

    GrammarExpression* ex14 = new GrammarExpression(EXPRESSION);
    ex14->expression = {SIMPLE_EXPRESSION};
    EXPRESSION->leads_to.push_back(ex14);

    GrammarExpression* ex15 = new GrammarExpression(EXPRESSION);
    ex15->expression = {SIMPLE_EXPRESSION, relop_terminal, SIMPLE_EXPRESSION};
    EXPRESSION->leads_to.push_back(ex15);

    GrammarExpression* ex16 = new GrammarExpression(SIMPLE_EXPRESSION);
    ex16->expression = {TERM};
    SIMPLE_EXPRESSION->leads_to.push_back(ex16);

    GrammarExpression* ex17 = new GrammarExpression(SIMPLE_EXPRESSION);
    ex17->expression = {SIGN, TERM};
    SIMPLE_EXPRESSION->leads_to.push_back(ex17);

    GrammarExpression* ex18 = new GrammarExpression(SIMPLE_EXPRESSION);
    ex18->expression = {SIMPLE_EXPRESSION, addop_terminal, TERM};
    SIMPLE_EXPRESSION->leads_to.push_back(ex18);

    GrammarExpression* ex19 = new GrammarExpression(TERM);
    ex19->expression = {FACTOR};
    TERM->leads_to.push_back(ex19);

    GrammarExpression* ex20 = new GrammarExpression(TERM);
    ex20->expression = {TERM, mulop_terminal, FACTOR};
    TERM->leads_to.push_back(ex20);

    GrammarExpression* ex21 = new GrammarExpression(SIGN);
    ex21->expression = {plus_terminal};
    SIGN->leads_to.push_back(ex21);

    GrammarExpression* ex22 = new GrammarExpression(SIGN);
    ex22->expression = {minus_terminal};
    SIGN->leads_to.push_back(ex22);

    GrammarExpression* ex23 = new GrammarExpression(FACTOR);
    ex23->expression = {id_terminal};
    FACTOR->leads_to.push_back(ex23);

    GrammarExpression* ex24 = new GrammarExpression(FACTOR);
    ex24->expression = {num_terminal};
    FACTOR->leads_to.push_back(ex24);

    GrammarExpression* ex25 = new GrammarExpression(FACTOR);
    ex25->expression = {openBracket_terminal, EXPRESSION, closedBracket_terminal};
    FACTOR->leads_to.push_back(ex25);

    // set first
    SIGN->first_strings.insert({"+", "-"});
    FACTOR->first_strings.insert({"id", "num", "("});
    TERM->first_strings.insert({"id", "num", "("});
    SIMPLE_EXPRESSION->first_strings.insert({"id", "num", "(", "+", "-"});
    EXPRESSION->first_strings.insert({"id", "num", "(", "+", "-"});
    ASSIGNMENT->first_strings.insert({"id"});
    WHILE->first_strings.insert({"while"});
    IF->first_strings.insert({"if"});
    PRIMITIVE_TYPE->first_strings.insert({"int", "float"});
    DECLARATION->first_strings.insert({"int", "float"});
    STATEMENT->first_strings.insert({"int", "float", "if", "while", "id"});
    STATEMENT_LIST->first_strings.insert({"int", "float", "if", "while", "id"});
    METHOD_BODY->first_strings.insert({"int", "float", "if", "while", "id"});

    // set follow
    METHOD_BODY->follow_strings.insert({"$"});
    STATEMENT_LIST->follow_strings.insert({"$"});
    STATEMENT->follow_strings.insert({"$"});
    DECLARATION->follow_strings.insert({"$"});
    PRIMITIVE_TYPE->follow_strings.insert({"id"});
    IF->follow_strings.insert({"$"});
    WHILE->follow_strings.insert({"$"});
    ASSIGNMENT->follow_strings.insert({"$"});
    EXPRESSION->follow_strings.insert({"$"});
    SIMPLE_EXPRESSION->follow_strings.insert({"$", "relop"});
    TERM->follow_strings.insert({"$", "relop"});
    FACTOR->follow_strings.insert({"$", "relop"});
    SIGN->follow_strings.insert({"id", "num", "("});


    vector<GrammarElement *> rules = {METHOD_BODY_E, STATEMENT_LIST_E, STATEMENT_E,
                                              DECLARATION_E, IF_E, WHILE_E, ASSIGNMENT_E,
                                              PRIMITIVE_TYPE_E, EXPRESSION_E, SIMPLE_EXPRESSION_E,
                                              TERM_E, SIGN_E, FACTOR_E};

    GrammarTableBuilder grammarTableBuilder;
//    grammarTableBuilder.build_grammar_table(a);
}
