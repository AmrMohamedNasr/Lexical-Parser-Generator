//
// Created by programajor on 3/16/18.
//

#include "NfaCombiner.h"
#include "../builder/NfaBuilder.h"

Node * NFACombiner::getCombinedNfa(vector<Nfa * > * separatedStateAcceptors) {
    NfaBuilder nfaBuilder;
    Nfa * final = nullptr;
    bool first = true;
    for (Nfa * nfa : (*separatedStateAcceptors)) {
        if (first) {
            first = false;
            final = nfa;
        } else {
        	Nfa * temp = final;
            final = nfaBuilder.construct_or_nfa(final, nfa);
            delete temp;
        }
    }
    Node * res = final->start;
    for (Nfa * nfa : (*separatedStateAcceptors)) {
		delete nfa;
	}
    return res;
}
