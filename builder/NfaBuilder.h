//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NFABUILDER_H
#define COMPILERS_NFABUILDER_H


#include "../models/FiniteStateAcceptor.h"

class NfaBuilder {
    public:

        /**
         * takes the input grammar and returns separated NFAs from it.
         * @param grammar the grammar from the given text file.
         * @return a list of separated NFAs created from the grammar file.
         */
        vector<FiniteStateAcceptor> getSeparatedNfas(string grammar);
};


#endif //COMPILERS_NFABUILDER_H
