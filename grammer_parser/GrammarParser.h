/*
 * GrammarParser.h
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */

#ifndef GRAMMAR_PARSER_GRAMMARPARSER_H_
#define GRAMMAR_PARSER_GRAMMARPARSER_H_

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class GrammarParser {
	public:
		bool parse_grammar(vector<string> *regExpNames, vector<string> *regExp, ifstream * grammar_stream);
};



#endif /* GRAMMAR_PARSER_GRAMMARPARSER_H_ */
