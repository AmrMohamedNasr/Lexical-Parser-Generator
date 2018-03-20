/*
 * GrammerParser.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */
#include "GrammarParser.h"
#include "../models/NfaToken.h"
#include <map>
#include <regex.h>

const regex GrammarParser::regDefRegex = regex("\\s*([A-Za-z][A-Za-z0-9_]*)\\s*=\\s*(.*)$");
const regex GrammarParser::regExpRegex = regex("\\s*([A-Za-z][A-Za-z0-9_]*)\\s*:\\s*(.*)$");
const regex GrammarParser::keyWordRegex = regex("\\s*\\{((?:\\s*[^\\s]*\\s*)*)}\\s*");
const regex GrammarParser::punctRegex = regex("\\s*\\[((?:\\s*[^\\s]*\\s*)*)]\\s*");

string filter_string(string str);
bool isReservedSymbol(char c);
bool escapeReserved(string str, bool regOps);
vector<string> split_spaces(string str);
vector<string> regular_expression_split(string str, map<string, vector<string>> mapOfDefinitions);
vector<MiniToken> regular_expression_postfix(vector<string> regexp);

bool GrammarParser::parse_grammar(vector<NfaToken> *result, ifstream * grammar_stream) {
	string line;
	map<string, vector<string>> mapOfDefinitions;
	if (grammar_stream->is_open()) {
		while (getline (*grammar_stream,line) ) {
			if (regex_match(line, punctRegex)) {
				smatch sm;
				regex_search(line,sm,punctRegex);
				if (!escapeReserved(sm[1], false)) {
					return false;
				}
				string filtered = filter_string(sm[1]);
				vector<string> tokens = split_spaces(filtered);
				for (unsigned i = 0; i < tokens.size(); i++) {
					NfaToken token (PUNCTUATION, tokens[i]);
					MiniToken mtoken (WORD, tokens[i]);
					token.tokens.push_back(mtoken);
					result->push_back(token);
				}
			} else if (regex_match(line, keyWordRegex)) {
				smatch sm;
				regex_search(line,sm,keyWordRegex);
				if (!escapeReserved(sm[1], false)) {
					return false;
				}
				string filtered = filter_string(sm[1]);
				vector<string> tokens = split_spaces(filtered);
				for (unsigned i = 0; i < tokens.size(); i++) {
					NfaToken token (KEYWORD, tokens[i]);
					MiniToken mtoken (WORD, tokens[i]);
					token.tokens.push_back(mtoken);
					result->push_back(token);
				}
			} else if (regex_match(line, regDefRegex)) {
				smatch sm;
				regex_search(line,sm,regDefRegex);
				string tokenName = sm[1];
				string tokenRegex = sm[2];
				vector<string> tokens = regular_expression_split(tokenRegex, mapOfDefinitions);
				mapOfDefinitions.insert(make_pair(tokenName, tokens));
			} else if (regex_match(line, regExpRegex)) {
				smatch sm;
				regex_search(line,sm,regExpRegex);
				string tokenName = sm[1];
				string tokenRegex = sm[2];
				vector<MiniToken> tokens = regular_expression_postfix(regular_expression_split(tokenRegex, mapOfDefinitions));
				NfaToken token(REGULAR_EXPRESSION, tokenName);
				for (unsigned i = 0; i < tokens.size(); i++) {
					token.tokens.push_back(tokens[i]);
				}
				result->push_back(token);
			} else {
				return false;
			}
		}
	}
	return true;
}

string filter_string(string str) {
	string res= "";
	for (unsigned i = 0; i < str.size(); i++) {
		if (str.at(i) == '\\' && i < str.size() - 1 && isReservedSymbol(str.at(i+1))) {
			i++;
		}
		res += str.at(i);
	}
	return res;
}

bool escapeReserved(string str, bool regOps) {
	for (unsigned i = 0; i < str.size(); i++) {
		if (str.at(i) == '\\' && i < str.size() - 1 && isReservedSymbol(str.at(i+1))) {
			i++;
		}
		if (isReservedSymbol(str.at(i)) && i > 0 && str.at(i-1) != '\\') {
			if (regOps) {
				if (str.at(i) == '=' || str.at(i) == ':') {
					return false;
				}
			} else {
				return false;
			}
		}
	}
	return true;
}

bool isReservedSymbol(char c) {
	return (c == '+' || c == '-' || c == '|' || c == '=' || c == '*'
					  || c == '(' || c == ')' || c == ':');
}

vector<string> split_spaces(string str) {
	string buf;
	stringstream ss(str);
	vector<string> tokens;
	while (ss >> buf) {
		tokens.push_back(buf);
	}
	return tokens;
}

vector<string> regular_expression_split(string str, map<string, vector<string>> mapOfDefinitions) {
	vector<string> res;
	return res;
}
vector<MiniToken> regular_expression_postfix(vector<string> regexp) {
	vector<MiniToken> tokens;

	return tokens;
}
