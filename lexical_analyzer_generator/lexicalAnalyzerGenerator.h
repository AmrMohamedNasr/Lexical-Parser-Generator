/*
 * lexicalAnalyzerGenerator.h
 *
 *  Created on: Mar 21, 2018
 *      Author: amrnasr
 */

#ifndef LEXICAL_ANALYZER_GENERATOR_LEXICALANALYZERGENERATOR_H_
#define LEXICAL_ANALYZER_GENERATOR_LEXICALANALYZERGENERATOR_H_

#include "../grammer_parser/GrammarParser.h"
#include "../builder/NfaBuilder.h"
#include "../combiner/NfaCombiner.h"
#include "../converter/NfaDfaConverter.h"
#include "../minimizer/DfaMinimizer.h"

class LexicalAnalyzerGenerator {
	private:
		GrammarParser grammarParser;
		NfaBuilder builder;
		NFACombiner combiner;
		NfaDfaConverter converter;
		DfaMinimizer minimzer;
	public:
		Node *generate_lexical_analyzer(string file_name);
};


#endif /* LEXICAL_ANALYZER_GENERATOR_LEXICALANALYZERGENERATOR_H_ */
