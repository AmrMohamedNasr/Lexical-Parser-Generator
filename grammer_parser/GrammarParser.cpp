/*
 * GrammerParser.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */
#include "GrammarParser.h"

bool GrammarParser::parse_grammar(vector<string> *regExpNames, vector<string> *regExp, ifstream * grammar_stream) {
	string line;
	if (grammar_stream->is_open()) {
		while (getline (*grammar_stream,line) ) {
			regExpNames->push_back(line);
		}
	}
	return true;
}



