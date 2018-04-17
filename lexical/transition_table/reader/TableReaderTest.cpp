//
// Created by programajor on 3/23/18.
//

#include "../../../test_headers/p1_tests.h"
#include "TableReader.h"

void test_transition_table_reader() {

    std::streambuf * buf;
    std::ifstream of;
    of.open("file2.txt");
    buf = of.rdbuf();
//    buf = std::cout.rdbuf();
    std::ostream out(buf);

    TableReader reader;
    TransitionTable* table = reader.readTransitionTable(&of);

    vector<DfaNode *> nodes = table->getNodes();
    vector<string> input = table->getInputs();
    vector<vector<DfaNode *>> transitions = table->getTransitions();
//    vector<vector<DfaNode *>> t2 = table->getTransitions();


}
