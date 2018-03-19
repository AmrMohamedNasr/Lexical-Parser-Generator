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

using namespace std;

void test_grammar_parser(void) {
	GrammarParser gp;
	vector<string> regName, regExp;
	bool error = false;
	ifstream infile;
	infile.open("rules.txt");
	gp.parse_grammar(&regName, &regExp, &infile);
	for (auto it = regName.begin(); it != regName.end(); ++it) {
	    cout << *it << endl;
	}
	infile.close();
	if (!error) {
		cout << "Grammar Parser Success..." << endl;
	}
}


