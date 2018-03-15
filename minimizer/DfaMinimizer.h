//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_DFAMINIMIZER_H
#define COMPILERS_DFAMINIMIZER_H


#include "../models/FiniteStateAcceptor.h"

class DfaMinimizer {

    public:
        /**
         * takes non minimized DFA from the converter and return it minimized.
         * @param nonMinimizedDFA the non minimized DFA from the converter
         * @return a minimized DFA from the given non minimized one.
         */
        FiniteStateAcceptor getMinimizedDFA(FiniteStateAcceptor nonMinimizedDFA);
};


#endif //COMPILERS_DFAMINIMIZER_H
