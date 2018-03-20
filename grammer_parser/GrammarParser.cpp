/*
 * GrammerParser.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */
#include "GrammarParser.h"
#include "../models/NfaToken.h"
#include <map>
#include <regex>
#include <stack>
#include <list>

const regex GrammarParser::regDefRegex = regex("\\s*([A-Za-z][A-Za-z0-9_]*)\\s*=\\s*(.*)$");
const regex GrammarParser::regExpRegex = regex("\\s*([A-Za-z][A-Za-z0-9_]*)\\s*:\\s*(.*)$");
const regex GrammarParser::keyWordRegex = regex("\\s*\\{((?:\\s*[^\\s]*\\s*)*)}\\s*");
const regex GrammarParser::punctRegex = regex("\\s*\\[((?:\\s*[^\\s]*\\s*)*)]\\s*");

string filter_string(string str);
bool isReservedSymbol(char c);
bool escapeReserved(string str, bool regOps);
vector<string> split_spaces(string str);
vector<MiniToken> regular_expression_split(string str, map<string, vector<MiniToken>> mapOfDefinitions);
vector<MiniToken> regular_expression_postfix(vector<MiniToken> regexp, bool * error);
bool is_operation_char(char c);
char nonspacechar_before(string str, unsigned i);
char nonspacechar_after(string str, unsigned i);
bool is_parenthesis(char c);

bool GrammarParser::parse_grammar(vector<NfaToken> *result, ifstream * grammar_stream) {
	string line;
	map<string, vector<MiniToken>> mapOfDefinitions;
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
				if (!escapeReserved(tokenRegex, true)) {
					return false;
				}
				vector<MiniToken> tokens = regular_expression_split(tokenRegex, mapOfDefinitions);
				mapOfDefinitions.insert(make_pair(tokenName, tokens));
			} else if (regex_match(line, regExpRegex)) {
				smatch sm;
				regex_search(line,sm,regExpRegex);
				string tokenName = sm[1];
				string tokenRegex = sm[2];
				if (!escapeReserved(tokenRegex, true)) {
					return false;
				}
				bool error = false;
				vector<MiniToken> tokens = regular_expression_postfix(regular_expression_split(tokenRegex, mapOfDefinitions), &error);
				if (error) {
					return false;
				}
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
		if (isReservedSymbol(str.at(i)) && i > 0 && str.at(i-1) != '\\') {
			if (regOps) {
				if (str.at(i) == '=' || str.at(i) == ':') {
					return false;
				}
				if (str.at(i) == '-') {
					char bf = nonspacechar_before(str, i - 1);
					char af = nonspacechar_after(str, i + 1);
					if (af == '\0' || bf == '\0' || isReservedSymbol(af)) {
						return false;
					} else if (isReservedSymbol(bf)) {
						int j = i - 1;
						while (j >= 0 && isspace(str.at(j))) {
							j--;
						}
						if (j < 1 || str.at(j - 1) != '\\') {
							return false;
						}
					}

				}
			} else {
				return false;
			}
		} else if (isReservedSymbol(str.at(i)) && i == 0) {
			return false;
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

vector<MiniToken> regular_expression_split(string str, map<string, vector<MiniToken>> mapOfDefinitions) {
	vector<MiniToken> res;
	for (unsigned i = 0; i < str.length(); i++) {
		string k = "";
		char c = str.at(i);
		while (isspace(c)) {
			i++;
			c = str.at(i);
		}
		if (is_operation_char(c)) {
			k+=c;
			res.push_back(MiniToken(OPERATION, k));
		} else if (is_parenthesis(c)) {
			k+=c;
			res.push_back(MiniToken(PARENTHESES, k));
		} else if (c == '-') {
			k += nonspacechar_before(str, i - 1);
			k += c;
			char temp = nonspacechar_after(str, i + 1);
			k += temp;
			i = str.find(temp, i);
			res.push_back(MiniToken(CHAR_GROUP, k));
		} else {
			bool collecting_token = true;
			bool add_eps = false;
			while (collecting_token && i < str.length()) {
				c = str.at(i);
				if (isspace(c) || isReservedSymbol(c)) {
					collecting_token = false;
					i--;
				} else if (c == '\\') {
					if (i == str.length() - 1 || !isReservedSymbol(str.at(i+1))) {
						if (str.at(i+1) == 'L') {
							add_eps = true;
							collecting_token = false;
							i++;
						} else {
							k += c;
						}
					} else {
						i++;
						k += str.at(i);
					}
				} else if (i == str.length() - 1 || nonspacechar_after(str, i + 1) != '-') {
					k += c;
				} else {
					collecting_token = false;
				}
				i++;
			}
			i--;
			if (k != "") {
				if (mapOfDefinitions.find(k) != mapOfDefinitions.end()) {
					vector<MiniToken> temp = mapOfDefinitions.find(k)->second;
					res.push_back(MiniToken(PARENTHESES, "("));
					for (auto it = temp.begin(); it != temp.end(); it++) {
						res.push_back(*it);
					}
					res.push_back(MiniToken(PARENTHESES, ")"));
				} else {
					res.push_back(MiniToken(WORD, k));
				}
			}
			if (add_eps) {
				res.push_back(MiniToken(EPSILON, "\\L"));
			}
		}
	}
	list<MiniToken> expandedReg;
	for (unsigned i = 0; i < res.size() - 1; i++) {
		MiniToken cur = res[i];
		MiniToken next = res[i + 1];
		if ((cur.type == WORD || cur.type == CHAR_GROUP || cur.type == EPSILON ||
				(cur.type == PARENTHESES && cur.tok == ")") || (cur.type == OPERATION && (cur.tok == "*" || cur.tok == "+"))) &&
				(next.type == WORD || next.type == CHAR_GROUP || next.type == EPSILON ||
						(next.type == PARENTHESES && next.tok == "("))) {
			expandedReg.push_back(cur);
			expandedReg.push_back(MiniToken(OPERATION,"@"));
		} else {
			expandedReg.push_back(cur);
		}
	}
	expandedReg.push_back(res[res.size() - 1]);
	return vector<MiniToken>(expandedReg.begin(), expandedReg.end());
}
char nonspacechar_before(string str, unsigned i) {
	while (i >= 0) {
		if (!isspace(str.at(i))) {
			return str.at(i);
		}
		i--;
	}
	return '\0';
}

char nonspacechar_after(string str, unsigned i) {
	while (i < str.length()) {
		if (!isspace(str.at(i))) {
			return str.at(i);
		}
		i++;
	}
	return '\0';
}
bool is_parenthesis(char c) {
	return c == '(' || c == ')';
}
bool is_operation_char(char c) {
	return c == '*' || c == '+' || c == '|';
}

vector<MiniToken> regular_expression_postfix(vector<MiniToken> regexp, bool * error) {
	vector<MiniToken> tokens;
	stack<MiniToken> operations;
	unsigned i = 0;
	*error = false;
	bool last_token_operand = false;
	while (!(*error) && i < regexp.size()) {
		MiniToken cur = regexp[i];
		if (cur.type == WORD || cur.type == CHAR_GROUP || cur.type == EPSILON) {
			tokens.push_back(cur);
			last_token_operand = true;
		} else if (cur.type == OPERATION) {
			if (!last_token_operand) {
				*error = true;
			} else if (cur.tok == "|" || cur.tok == "@") {
				last_token_operand = false;
				while (!operations.empty()
						&& (operations.top().type == OPERATION &&
								!(operations.top().tok == "|" && cur.tok == "@"))
						&& !(operations.top().type == PARENTHESES && operations.top().tok == "(")) {
					tokens.push_back(operations.top());
					operations.pop();
				}
				operations.push(cur);
			} else if (cur.tok == "*" || cur.tok == "+"){
				tokens.push_back(cur);
			} else {
				*error = true;
			}
		} else if (cur.type == PARENTHESES) {
			if (cur.tok == "(") {
				last_token_operand = false;
				operations.push(cur);
			} else if (cur.tok == ")"){
				last_token_operand = true;
				if (operations.empty()) {
					*error = true;
				}
				MiniToken popped = operations.top();
				operations.pop();
				while (!operations.empty() && (popped.type != PARENTHESES || popped.tok != "(")) {
					tokens.push_back(popped);
					popped = operations.top();
					operations.pop();
				}
				if (popped.type != PARENTHESES || popped.tok != "(") {
					*error = true;
				}
			} else {
				*error = true;
			}
		} else {
			*error = true;
		}
		i++;
	}
	while (!operations.empty()) {
		if (operations.top().type == PARENTHESES) {
			*error = true;
		} else {
			tokens.push_back(operations.top());
			operations.pop();
		}
	}
	return tokens;
}
