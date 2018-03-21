/*
 * lexicalAnalyzerGenerator.cpp
 *
 *  Created on: Mar 21, 2018
 *      Author: amrnasr
 */
#include "lexicalAnalyzerGenerator.h"
#include <fstream>

using namespace std;

Node * LexicalAnalyzerGenerator::generate_lexical_analyzer(string file_name) {
	ifstream inFile;
	inFile.open(file_name);
	if (!inFile) {
	    cout << "Unable to open file " << file_name << endl;
	    return nullptr;
	}
	vector<NfaToken> tokens;
	vector<string> errors = this->grammarParser.parse_grammar(&tokens, &inFile);
	inFile.close();
	if (!errors.empty()) {
		cout << "Couldn't build lexical analyzer! File format error :" << endl;
		for (unsigned i = 0; i < errors.size(); i++) {
			cout << errors[i] << endl;
		}
		return nullptr;
	}
	vector<Nfa> nfas = this->builder.get_separated_nfas(tokens);
	Node * startNode = this->combiner.getCombinedNfa(nfas);
	startNode = this->converter.getNonMinimizedDFA(startNode);
	startNode = this->minimzer.getMinimizedDFA(startNode);
	return startNode;
}



