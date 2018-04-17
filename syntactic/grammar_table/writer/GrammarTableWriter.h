/*
 * GrammarTableWriter.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_GRAMMAR_TABLE_WRITER_GRAMMARTABLEWRITER_H_
#define SYNTACTIC_GRAMMAR_TABLE_WRITER_GRAMMARTABLEWRITER_H_

#include "../model/GrammarTable.h"

class GrammarTableWriter {
	public:
		void writeGrammarTableInHumanReadableFormat(GrammarTable *table, ostream* stream);
		void writeGrammarTableInReadableForamt(GrammarTable *table, ostream* stream);
};


#endif /* SYNTACTIC_GRAMMAR_TABLE_WRITER_GRAMMARTABLEWRITER_H_ */
