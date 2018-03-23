/*
 * tokenizer.h
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#ifndef LEXICAL_ANALYZER_TOKENIZER_TOKENIZER_H_
#define LEXICAL_ANALYZER_TOKENIZER_TOKENIZER_H_

#include <queue>
#include "../models/token.h"
#include "../../models/DfaNode.h"

class Tokenizer {
	private:
		queue<Token> tokens;
		DfaNode * machine;
	public:
		bool hasNext();
		Token nextToken();
		void tokenize(string str);
		void reset();
		Tokenizer(DfaNode * start);
};



#endif /* LEXICAL_ANALYZER_TOKENIZER_TOKENIZER_H_ */