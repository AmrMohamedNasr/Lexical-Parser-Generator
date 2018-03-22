//
// Created by programajor on 3/16/18.
//

#include "NfaCombiner.h"
#include "../builder/NfaBuilder.h"

Nfa * NFACombiner::getCombinedNfa(vector<Nfa * > * separatedStateAcceptors) {
    NfaBuilder nfaBuilder;
    Nfa * final = nullptr;
    bool first = true;
    for (Nfa * nfa : (*separatedStateAcceptors)) {
        if (first) {
            first = false;
            final = nfa;
        } else {
            final = nfaBuilder.construct_or_nfa(final, nfa);
        }
    }
    return final;
}
