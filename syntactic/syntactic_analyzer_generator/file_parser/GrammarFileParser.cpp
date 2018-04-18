//
// Created by programajor on 4/18/18.
//

#include <vector>
#include <string>
#include "../models/GrammarElement.h"
#include "GrammarFileParser.h"
#include "../../../utils/Utils.h"
#include "../models/NonTerminal.h"

using namespace std;

enum LineType {FULL, LEFT, MIDDLE, RIGHT, LEFT_MIDDLE, RIGHT_MIDDLE};

const regex fullExpressionLine = regex("^\\s*#\\s*([A-Za-z0-9_]*)\\s*\\:\\:\\=\\s*(.*)\\s*");
const regex leftPartExpressionLine = regex("^\\s*#\\s*([A-Za-z0-9_]*)\\s*");
const regex leftAndEqualExpressionLine = regex("^\\s*#\\s*([A-Za-z0-9_]*)\\s*\\:\\:\\=\\s*");
const regex EqualPartExpressionLine = regex("\\s*\\:\\:\\=\\s*");
const regex rightPartExpressionLine = regex("\\s*(.*)\\s*");
const regex rightAndEqualExpressionLine = regex("\\s*\\:\\:\\=\\s*(.*)\\s*");

std::vector <string> GrammarFileParser::parse_grammar_file(
        vector < GrammarElement * > *rules, unordered_set < GrammarExpression * > *expressions,
        ifstream * lexical_file_stream, unordered_set < string > *terminals,
        unordered_set < string > *non_terminals, GrammarElement * startRule) {
    string line;
    vector<string> lines;
    vector<string> errors;
    map<string, NonTerminal*> nameToExpression;
    if (lexical_file_stream->is_open()) {
        LineType prevLineType = FULL;
        GrammarElement* prevGrammarElement = nullptr;
        string rightHandSide = "";
        while (getline (*lexical_file_stream, line) ) {
            smatch matcher;
            lines.push_back(line);
            if (line.empty()) {
                continue;
            } else if (regex_match(line, fullExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE || prevLineType == MIDDLE) {
                    addError(&errors , "Multiple Equal Signs", lines.size());
                }
                parseRightHandSide(rightHandSide, terminals, non_terminals, nameToExpression, rules, prevGrammarElement,
                                   &errors);
                rightHandSide = "";
                prevGrammarElement = insertNonTerminal(line, fullExpressionLine, nameToExpression,
                                         matcher, rules, prevGrammarElement, startRule, non_terminals);
                regex_search(line, matcher, fullExpressionLine);
                bool error = isValidatRightHandSide(matcher[2], &errors, lines.size());
                if (!error) {
                    rightHandSide += matcher[2];
                }
                prevLineType = FULL;
            } else if (regex_match(line, leftAndEqualExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE || prevLineType == MIDDLE) {
                    addError(&errors, "Multiple Equal Signs", lines.size());
                }
                parseRightHandSide(rightHandSide, terminals, non_terminals, nameToExpression, rules, prevGrammarElement,
                                   &errors);
                rightHandSide = "";
                prevGrammarElement = insertNonTerminal(line, leftAndEqualExpressionLine, nameToExpression,
                                                       matcher, rules, prevGrammarElement, startRule, non_terminals);
                prevLineType = LEFT_MIDDLE;
            } else if (regex_match(line, rightAndEqualExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE) {
                    addError(&errors, "Multiple Equal Signs", lines.size());
                } else if (prevLineType != LEFT) {
                    addError(&errors, "Non Terminal not Available, Cannot start with equal", lines.size());
                }
                regex_search(line, matcher, rightAndEqualExpressionLine);
                bool error = isValidatRightHandSide(matcher[1], &errors, lines.size());
                if (!error) {
                    rightHandSide += matcher[1];
                }
                prevLineType = RIGHT_MIDDLE;
            } else if (regex_match(line, leftPartExpressionLine)) {
                if (prevLineType == LEFT || prevLineType == LEFT_MIDDLE) {
                    addError(&errors, "No RHS for non terminal", lines.size() - 1);
                }
                parseRightHandSide(rightHandSide, terminals, non_terminals, nameToExpression, rules, prevGrammarElement,
                                   &errors);
                rightHandSide = "";
                prevGrammarElement = insertNonTerminal(line, leftPartExpressionLine, nameToExpression,
                                                       matcher, rules, prevGrammarElement, startRule, non_terminals);
                prevLineType = LEFT;
            } else if (regex_match(line, rightPartExpressionLine)) {
                if (prevLineType == LEFT || rules->size() == 0) {
                    addError(&errors, "No EQUAL sign for non terminal", lines.size() - 1);
                }
                regex_search(line, matcher, rightPartExpressionLine);
                bool error = isValidatRightHandSide(matcher[1], &errors, lines.size());
                if (!error) {
                    rightHandSide += matcher[1];
                }
                prevLineType = RIGHT;
            } else if (regex_match(line, EqualPartExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE) {
                    addError(&errors, "Multiple Equal Signs", lines.size());
                } else if (prevLineType != LEFT) {
                    addError(&errors, "Non Terminal not Available, Cannot start with equal", lines.size());
                }
                prevLineType = MIDDLE;
            } else {
                addError(&errors, "Invalid Line Syntax", lines.size());
            }
        }
    } else {
        errors.push_back("Input Stream is Closed");
    }
    return errors;
}

GrammarElement * GrammarFileParser::insertNonTerminal(string line, const regex pattern, map<string, NonTerminal *> nameToExpression, smatch matcher,
                                                      vector<GrammarElement *> *rules, GrammarElement *prevGrammarElement, GrammarElement *startRule,
                                                      unordered_set<string> *non_terminals) {
    regex_search(line, matcher, pattern);
    string name = matcher[1];
    if (nameToExpression.find(name) == nameToExpression.end()) {
        GrammarElement* element = new NonTerminal(name, NON_TERMINAL);
        nameToExpression[name] = static_cast<NonTerminal*> (element);
        rules->push_back(element);
        non_terminals->insert(name);
        if (prevGrammarElement == nullptr) {
            startRule = element;
        }
        return element;
    } else {
        return nameToExpression[name];
    }
}

void GrammarFileParser::addError(vector<string> *errors, string error, int lineNumber) {
    errors->push_back("ERROR: " + error + " at " + to_string(lineNumber));
}

void GrammarFileParser::parseRightHandSide(string rightHandSide, unordered_set<string> *terminals, unordered_set<string> *non_terminals,
                                           map<string, NonTerminal *> nameToExpression, vector<GrammarElement *> *rules,
                                           GrammarElement *prevGrammarElement, vector<string> *errors) {
    vector<string> strings = split_spaces(rightHandSide);
    if (strings.size() != 0) {
        vector<vector<string>> terminalsAndNonTerminals = splitOrs(strings, errors);
        for (int i = 0; i < terminalsAndNonTerminals.size(); i++) {
            GrammarExpression* expression = new GrammarExpression(prevGrammarElement);
            for (int j = 0; j < terminalsAndNonTerminals[i].size(); ++j) {
                string curr = terminalsAndNonTerminals[i][j];
                bool quoteFound = false;
                string temp = "";
                for (int k = 0; k < curr.length(); ++k) {
                    if (isQuote(curr[k])) {
                        if (quoteFound) {
                            if (!temp.empty()) {
                                errors->push_back("Empty Terminal");
                            } else {
                                GrammarElement* element = new GrammarElement(temp, TERMINAL);
                                terminals->insert(temp);
                                expression->expression.push_back(element);
                                temp = "";
                            }
                            quoteFound = false;
                        } else {
                            quoteFound = true;
                        }
                    } else {
                        temp += curr[k];
                    }
                }
                if (!temp.empty()) {
                    if (nameToExpression.find(temp) == nameToExpression.end()) {
                        GrammarElement* element = new NonTerminal(temp, NON_TERMINAL);
                        nameToExpression[temp] = static_cast<NonTerminal *>(element);
                        rules->push_back(element);
                        non_terminals->insert(temp);
                    }
                    expression->expression.push_back(static_cast<GrammarElement *> (nameToExpression[temp]));
                    nameToExpression[temp]->referenced_in.push_back(expression);
                    temp = "";
                }
            }
            if (prevGrammarElement != nullptr) {
                static_cast<NonTerminal*> (prevGrammarElement)->leads_to.push_back(expression);
            }
        }
    } else {
        errors->push_back("Empty RHS, Cannot parse grammar ");
    }
}

bool GrammarFileParser::isValidatRightHandSide(string rightHandSide, vector<string> *errors, int lineNumber) {
    int quotesCount = 0;
    for (int i = 0; i < rightHandSide.length(); ++i) {
        if (isQuote(rightHandSide[i])) {
            quotesCount++;
        }
    }
    if (quotesCount % 2 == 0) {
        return false;
    } else {
        addError(errors, "Unclosed Quote, INVALID RHS", lineNumber);
        return true;
    }
}

bool GrammarFileParser::isQuote(char c) {
    return c == '\'' || c == '’' || c == '‘';
}

vector<vector<string>> GrammarFileParser::splitOrs(vector<string> strings, vector<string> *errors) {
    vector<vector<string>> ret;
    string temp = "";
    for (int i = 0; i < strings.size(); ++i) {
        string curr = strings[i];
        if (curr.length() == 0) continue;
        if (i == 0 && curr[0] == '|') {
            errors->push_back("Cannot start RHS with |");
        } else if (i == strings.size() - 1 && curr[curr.length() - 1] == '|') {
            errors->push_back("Cannot end RHS with |");
        } else {
            for (int j = 0; j < curr.length(); ++j) {
                if (curr[j] == '|') {
                    ret[ret.size() - 1].push_back(temp);
                    temp = "";
                } else {
                    if (temp.empty()) {
                        vector<string> vec;
                        ret.push_back(vec);
                    }
                    temp += curr[j];
                }
            }
            if (!temp.empty()) {
                if (ret.size() == 0) {
                    vector<string> vec;
                    ret.push_back(vec);
                }
                ret[ret.size() - 1].push_back(temp);
                temp = "";
            }
        }
    }
    return ret;
}
