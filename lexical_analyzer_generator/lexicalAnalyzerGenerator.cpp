/*
 * lexicalAnalyzerGenerator.cpp
 *
 *  Created on: Mar 21, 2018
 *      Author: amrnasr
 */
#include "lexicalAnalyzerGenerator.h"
#include <fstream>

using namespace std;

void LexicalAnalyzerGenerator::generate_lexical_analyzer(string file_name) {
	ifstream inFile;
	inFile.open(file_name);
	if (!inFile) {
	    cout << "Unable to open file " << file_name << endl;
	}
	vector<NfaToken> tokens;
	vector<string> priority;
	vector<string> errors = this->grammarParser.parse_grammar(&tokens, &priority, &inFile);
	inFile.close();
	if (!errors.empty()) {
		cout << "Couldn't build lexical analyzer! File format error :" << endl;
		for (unsigned i = 0; i < errors.size(); i++) {
			cout << errors[i] << endl;
		}
	}
	vector<Nfa *> nfas;
	this->builder.get_separated_nfas(&nfas, &tokens);
	Node * startNode = this->combiner.getCombinedNfa(&nfas);
	DfaNode * dfaStartNode = this->converter.getNonMinimizedDFA(startNode, &priority);
	vector<DfaNode *> finalMachine;
	this->minimzer.getMinimizedDFA(&finalMachine, dfaStartNode);
}



