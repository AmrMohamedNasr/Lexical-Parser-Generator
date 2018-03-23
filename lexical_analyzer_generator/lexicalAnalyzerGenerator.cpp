/*
 * lexicalAnalyzerGenerator.cpp
 *
 *  Created on: Mar 21, 2018
 *      Author: amrnasr
 */
#include "lexicalAnalyzerGenerator.h"
#include <fstream>

using namespace std;

string handle_file_name_extension(string file_name);

void LexicalAnalyzerGenerator::generate_lexical_analyzer(string file_name) {
	ifstream inFile;
	inFile.open(file_name);
	if (!inFile) {
	    cout << "Unable to open file " << file_name << endl;
	}
	vector<NfaToken> tokens;
	vector<string> priority;
	set<char> alpha;
	vector<string> errors = this->grammarParser.parse_grammar(&tokens, &priority, &inFile, &alpha);
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
	dfaStartNode->getEdges();
	vector<DfaNode *> finalMachine;
	this->minimzer.getMinimizedDFA(&finalMachine, dfaStartNode);
	TransitionTable table = this->tableBuilder.buildTransitionTable(finalMachine, &alpha);
	streambuf *buf;
	ofstream of, of2;
	string fileName = handle_file_name_extension(file_name);
	of.open(fileName);
	of2.open("H_" + fileName);
	if (!of || !of2) {
		cout << "Couldn't write in output file \"" + handle_file_name_extension(file_name) + "\"" << endl;
	} else {
		buf = of.rdbuf();
		ostream outFile(buf);
		streambuf *cbuf;
		cbuf = cout.rdbuf();
		ostream cons (cbuf);
		streambuf *f2buf;
		f2buf = of2.rdbuf();
		ostream outFileH(f2buf);
		this->tableWriter.writeTransitionTableInHumanReadableFormat(table, &cons);
		this->tableWriter.writeTransitionTableInHumanReadableFormat(table, &outFileH);
		this->tableWriter.writeTransitionTableInReadableForamt(table, &outFile);
	}
	vector<DfaNode *> rem_nodes = table.getNodes();
	for (auto i = rem_nodes.begin(); i != rem_nodes.end(); i++) {
		delete (*i);
	}
}


string handle_file_name_extension(string file_name) {
	if (file_name.size() > 3 && file_name.substr(file_name.size() - 4) == ".txt") {
		return (file_name.substr(0, file_name.size() - 4) + ".trnstb");
	} else {
		return file_name + ".trnstb";
	}
}
