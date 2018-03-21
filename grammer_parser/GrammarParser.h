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
#include <regex>
#include <string>
#include "../models/NfaToken.h"

using namespace std;

class GrammarParser {
	private:
		static const regex regDefRegex;
		static const regex regExpRegex;
		static const regex keyWordRegex;
		static const regex punctRegex;
	public:
		vector<string> parse_grammar(vector<NfaToken> *tokens , ifstream * grammar_stream);
};



#endif /* GRAMMAR_PARSER_GRAMMARPARSER_H_ */
