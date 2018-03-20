/*
 * GrammerParserTest.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */

#include "GrammarParser.h"
#include "../p1_tests.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include "../models/NfaToken.h"

using namespace std;

static const vector<NfaToken> correctTokens = {
		NfaToken (REGULAR_EXPRESSION, "id", vector<MiniToken> ({
				MiniToken (CHAR_GROUP, "a-z"),
				MiniToken (CHAR_GROUP, "A-Z"),
				MiniToken (OPERATION, "|"),
				MiniToken (CHAR_GROUP, "a-z"),
				MiniToken (CHAR_GROUP, "A-Z"),
				MiniToken (OPERATION, "|"),
				MiniToken (CHAR_GROUP, "0-9"),
				MiniToken (OPERATION, "|"),
				MiniToken (OPERATION, "*"),
				MiniToken (OPERATION, "@")
		})),
		NfaToken (KEYWORD, "boolean", vector<MiniToken> ({MiniToken (WORD, "boolean")})),
		NfaToken (KEYWORD, "int", vector<MiniToken> ({MiniToken (WORD, "int")})),
		NfaToken (KEYWORD, "float", vector<MiniToken> ({MiniToken (WORD, "float")})),
		NfaToken (REGULAR_EXPRESSION, "num", vector<MiniToken> ({
				MiniToken (CHAR_GROUP, "0-9"),
				MiniToken (OPERATION, "+"),
				MiniToken (CHAR_GROUP, "0-9"),
				MiniToken (OPERATION, "+"),
				MiniToken (OPERATION, "|"),
				MiniToken (WORD, "."),
				MiniToken (OPERATION, "@"),
				MiniToken (CHAR_GROUP, "0-9"),
				MiniToken (OPERATION, "+"),
				MiniToken (OPERATION, "@"),
				MiniToken (EPSILON, "\\L"),
				MiniToken (WORD, "E"),
				MiniToken (CHAR_GROUP, "0-9"),
				MiniToken (OPERATION, "+"),
				MiniToken (OPERATION, "@"),
				MiniToken (OPERATION, "|"),
				MiniToken (OPERATION, "@")
		})),
		NfaToken (REGULAR_EXPRESSION, "relop", vector<MiniToken> ({
				MiniToken (WORD, "=="),
				MiniToken (WORD, "!="),
				MiniToken (OPERATION, "|"),
				MiniToken (WORD, ">"),
				MiniToken (OPERATION, "|"),
				MiniToken (WORD, ">="),
				MiniToken (OPERATION, "|"),
				MiniToken (WORD, "<"),
				MiniToken (OPERATION, "|"),
				MiniToken (WORD, "<="),
				MiniToken (OPERATION, "|")
		})),
		NfaToken (REGULAR_EXPRESSION, "assign", vector<MiniToken> ({MiniToken (WORD, "=")})),
		NfaToken (KEYWORD, "if", vector<MiniToken> ({MiniToken (WORD, "if")})),
		NfaToken (KEYWORD, "else", vector<MiniToken> ({MiniToken (WORD, "else")})),
		NfaToken (KEYWORD, "while", vector<MiniToken> ({MiniToken (WORD, "while")})),
		NfaToken (PUNCTUATION, ";", vector<MiniToken> ({MiniToken (WORD, ";")})),
		NfaToken (PUNCTUATION, ",", vector<MiniToken> ({MiniToken (WORD, ",")})),
		NfaToken (PUNCTUATION, "(", vector<MiniToken> ({MiniToken (WORD, "(")})),
		NfaToken (PUNCTUATION, ")", vector<MiniToken> ({MiniToken (WORD, ")")})),
		NfaToken (PUNCTUATION, "{", vector<MiniToken> ({MiniToken (WORD, "{")})),
		NfaToken (PUNCTUATION, "}", vector<MiniToken> ({MiniToken (WORD, "}")})),
		NfaToken (REGULAR_EXPRESSION, "addop", vector<MiniToken> ({
			MiniToken (WORD, "+"),
			MiniToken (WORD, "-"),
			MiniToken (OPERATION, "|"),
		})),
		NfaToken (REGULAR_EXPRESSION, "mulop", vector<MiniToken> ({
			MiniToken (WORD, "*"),
			MiniToken (WORD, "/"),
			MiniToken (OPERATION, "|"),
		}))
};

void test_grammar_parser(void) {
	GrammarParser gp;
	vector<NfaToken> regTokens;
	bool error = false;
	ifstream infile;
	infile.open("rules.txt");
	if (!gp.parse_grammar(&regTokens, &infile)) {
		cout << "ERROR DETECTED IN RIGHT PROGRAM!!" << endl;
	}
	unsigned i = 0;
	for (auto it = regTokens.begin(); it != regTokens.end(); ++it) {
	    NfaToken tok = (*it);
	    if (tok.tokenName.compare(correctTokens[i].tokenName) != 0) {
	    	error = true;
	    	cout << "WRONG : Expect : \"" << correctTokens[i].tokenName << "\" Found : \"" << tok.tokenName << "\"" << endl;
	    }
	    i++;
	}
	infile.close();
	if (!error) {
		cout << "Grammar Parser Success..." << endl;
	}
}


