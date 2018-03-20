//
// Created by programajor on 3/16/18.
//

#include <algorithm>
#include "NfaBuilder.h"
#include "../models/Edge.h"

void build_graph(NfaToken& nfa_token);

Nfa NfaBuilder::construct_eps_nfa() {
    auto start = new Node(!ACCEPT_STATE);
    auto end = new Node(ACCEPT_STATE);
    auto edge = new Edge('\0', '\0', end);
    start->addEdge(edge);
    auto nfa = new Nfa();
    nfa->start = start;
    nfa->end = end;
    return *nfa;
}

Nfa NfaBuilder::construct_letter_nfa(char c) {

}

Nfa NfaBuilder::construct_or_nfa(Nfa a, Nfa b) {

}

Nfa NfaBuilder::construct_and_nfa(Nfa a, Nfa b) {

}
Nfa NfaBuilder::construct_closure_nfa(Nfa a) {

}

Nfa NfaBuilder::construct_positive_closure_nfa(Nfa a) {

}

vector<Node> NfaBuilder::get_separated_nfas(vector<NfaToken> nfa_tokens) {
    for (NfaToken& nfaToken : nfa_tokens) {
        build_graph(nfaToken);
    }
}

void NfaBuilder::build_graph(NfaToken& nfa_token) {
    Nfa n = construct_eps_nfa();
    cout << (n.start->isAcceptedState()) << endl;
    cout << (n.end->isAcceptedState()) << endl;
}