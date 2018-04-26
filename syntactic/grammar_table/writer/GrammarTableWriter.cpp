//
// Created by programajor on 4/26/18.
//

#include <iostream>
#include <iomanip>
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
                *stream << SYNC_ENTRY << endl;
            } else if (!table->has_entry(nonTerminal, terminal)) {
                *stream << HAS_NO_ENTRY << endl;
            } else {
                vector<string> vec = table->get_entry(nonTerminal, terminal);
                *stream << vec.size() << endl;
                for (int k = 0; k < vec.size(); ++k) {
                    *stream << vec[k] << endl;
                }
            }
        }
    }
}

void GrammarTableWriter::writeGrammarTableInHumanReadableFormat(GrammarTable *table, ostream *stream) {
    vector<string> nonTerminals = table->get_non_terminals();
    vector<string> terminals = table->get_terminals();

    *stream << left << setw(20) << "NT \\ T";
    for (int i = 0; i < terminals.size(); ++i) {
        *stream << setw(25) << terminals[i];
    }
    *stream << endl;

    for (int i = 0; i < nonTerminals.size(); ++i) {
        string nonTerminal = nonTerminals[i];
        *stream << left << setw(20) << nonTerminal;
        for (int j = 0; j < terminals.size(); ++j) {
            string terminal = terminals[i];
            if (!table->has_entry(nonTerminal, terminal)) {
                *stream << setw(25) << "";
            } else if (table->is_synch(nonTerminal, terminal)) {
                *stream << setw(25) << "Synch";
            } else {
                vector<string> vec = table->get_entry(nonTerminal, terminal);
                if (vec.size() == 0) {
                    *stream << setw(25) << nonTerminal + " -> EPS";
                } else {
                    string next;
                    for (int k = 0; k < vec.size(); ++k) {
                        next += (" " + vec[k]);
                    }
                    *stream << setw(25) << (nonTerminal + " ->" + next);
                }
            }
        }
        *stream << endl;
    }
}
