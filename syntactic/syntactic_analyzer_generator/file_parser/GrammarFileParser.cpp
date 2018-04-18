//
// Created by programajor on 4/18/18.
//

#include <vector>
#include <string>
#include "../models/GrammarElement.h"
#include "GrammarFileParser.h"

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
    map<string, GrammarElement*> nameToExpression;
    if (lexical_file_stream->is_open()) {
        LineType prevLineType = FULL;
        while (getline (*lexical_file_stream, line) ) {
            smatch matcher;
            lines.push_back(line);
            if (regex_match(line, fullExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE || prevLineType == MIDDLE) {
                    addError(&errors , "Multiple Equal Signs", lines.size());
                }
                regex_search(line, matcher, fullExpressionLine);
                string name = matcher[1];
                if (nameToExpression.find(name) == nameToExpression.end()) {
//                    GrammarElement* element = (GrammarElement*));
                }
                prevLineType = FULL;
            } else if (regex_match(line, leftAndEqualExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE || prevLineType == MIDDLE) {
                    addError(&errors , "Multiple Equal Signs", lines.size());
                }
                regex_search(line, matcher, leftAndEqualExpressionLine);
                prevLineType = LEFT_MIDDLE;
            } else if (regex_match(line, rightAndEqualExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE) {
                    addError(&errors , "Multiple Equal Signs", lines.size());
                } else if (prevLineType != LEFT) {
                    addError(&errors , "Non Terminal not Available, Cannot start with equal", lines.size());
                }
                prevLineType = RIGHT_MIDDLE;
            } else if (regex_match(line, leftPartExpressionLine)) {
                if (prevLineType == LEFT || prevLineType == LEFT_MIDDLE) {
                    addError(&errors , "No RHS for non terminal", lines.size() - 1);
                }
                regex_search(line, matcher, leftPartExpressionLine);
                prevLineType = LEFT;
            } else if (regex_match(line, rightPartExpressionLine)) {
                if (prevLineType == LEFT || rules->size() == 0) {
                    addError(&errors , "No EQUAL sign for non terminal", lines.size() - 1);
                }
                prevLineType = RIGHT;
            } else if (regex_match(line, EqualPartExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE) {
                    addError(&errors , "Multiple Equal Signs", lines.size());
                } else if (prevLineType != LEFT) {
                    addError(&errors , "Non Terminal not Available, Cannot start with equal", lines.size());
                }
                prevLineType = MIDDLE;
            } else if (line.empty()) {
                continue;
            }
        }
    } else {
        errors.push_back("Input Stream is Closed");
    }
    return errors;
}

void GrammarFileParser::addError(vector<string> *errors, string error, int lineNumber) {
    errors->push_back("ERROR: " + error + " at " + to_string(lineNumber));
}
