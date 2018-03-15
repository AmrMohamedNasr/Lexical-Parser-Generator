//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NFADFACONVERTER_H
#define COMPILERS_NFADFACONVERTER_H

#include "../models/FiniteStateAcceptor.h"

class NfaDfaConverter {

    public:
        /**
         * takes combined NFA from the combiner and converts it to a non minimized DFA.
         * @param combinedNfa the combined NFA from the combiner
         * @return a non minimized DFA from the given NFA.
         */
        FiniteStateAcceptor getNonMinimizedDFA(FiniteStateAcceptor combinedNfa);
};


#endif //COMPILERS_NFADFACONVERTER_H
