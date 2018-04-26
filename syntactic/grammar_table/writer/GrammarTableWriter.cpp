//
// Created by programajor on 4/26/18.
//

#include <iostream>
#include "../model/GrammarTable.h"
#include "GrammarTableWriter.h"

void GrammarTableWriter::writeGrammarTableInReadableForamt(GrammarTable *table, ostream *stream) {
    vector<string> nonTerminals = table->get_non_terminals();
    vector<string> terminals = table->get_terminals();
    string start = table->get_start();

    *stream << nonTerminals.size() << endl;
    for (int i = 0; i < nonTerminals.size(); ++i) {
        *stream << nonTerminals[i] << endl;
    }

    *stream << terminals.size() << endl;
    for (int i = 0; i < terminals.size(); ++i) {
        *stream << terminals[i] << endl;
    }

    *stream << start << endl;

    for (int i = 0; i < nonTerminals.size(); ++i) {
        string nonTerminal = nonTerminals[i];
        for (int j = 0; j < terminals.size(); ++j) {
            string terminal = terminals[j];
            if (table->is_synch(nonTerminal, terminal)) {
                *stream << "-1" << endl;
            } else {
                vector<string> vec = table->get_entry(nonTerminal, terminal);
                *stream << vec.size() << endl;
                for (int k = 0; k < vec.size(); ++k) {
                    *stream << vec.[k] << endl;
                }
            }
        }
    }
}
