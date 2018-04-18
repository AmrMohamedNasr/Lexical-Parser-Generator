/*
 * GrammarFileParser.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FILE_PARSER_GRAMMARFILEPARSER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FILE_PARSER_GRAMMARFILEPARSER_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_set>
#include "../models/GrammarElement.h"
#include "../models/GrammarExpression.h"

using namespace std;

class GrammarFileParser {
	public:
		// Will return vector of errors, empty if no errors.
		vector<string> parse_grammar_file(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions,
				ifstream * lexical_file_stream, unordered_set<string> *terminals,
				unordered_set<string> *non_terminals, GrammarElement * startRule);

    private:
    static const regex startExpressionLine;
    static const regex continueExpressionLine;

    void addError(vector<string> *errors, string error, int lineNumber);
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FILE_PARSER_GRAMMARFILEPARSER_H_ */
