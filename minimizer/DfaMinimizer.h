//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_DFAMINIMIZER_H
#define COMPILERS_DFAMINIMIZER_H


#include "../models/Node.h"

class DfaMinimizer {

    public:
        /**
         * takes non minimized DFA from the converter and return it minimized.
         * @param nonMinimizedDFA the non minimized DFA from the converter
         * @return a minimized DFA from the given non minimized one.
         */
        Node getMinimizedDFA(Node nonMinimizedDFA);
};


#endif //COMPILERS_DFAMINIMIZER_H
