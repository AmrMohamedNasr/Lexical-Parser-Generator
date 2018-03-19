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

void test_grammar_parser(void) {
	GrammarParser gp;
	vector<NfaToken> regTokens;
	bool error = false;
	ifstream infile;
	infile.open("rules.txt");
	if (!gp.parse_grammar(&regTokens, &infile)) {
		cout << "ERROR DETECTED IN RIGHT PROGRAM!!" << endl;
	}
	for (auto it = regTokens.begin(); it != regTokens.end(); ++it) {
	    cout << (*it).tokenName << endl;
	}
	infile.close();
	if (!error) {
		cout << "Grammar Parser Success..." << endl;
	}
}


