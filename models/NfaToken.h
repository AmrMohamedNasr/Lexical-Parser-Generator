/*
 * NfaToken.h
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */

#ifndef MODELS_NFATOKEN_H_
#define MODELS_NFATOKEN_H_

#include <string>
#include <vector>

using namespace std;

class MiniToken {
	public:
		enum MiniType {OPERATION, CHAR_GROUP, WORD};
		string tok;
};

class NfaToken {
	public:
		string tokenName;
		vector<MiniToken> tokens;
		enum tokenType{PUNCTUATION, KEYWORD, REGULAR_EXPRESSION};
};



#endif /* MODELS_NFATOKEN_H_ */
