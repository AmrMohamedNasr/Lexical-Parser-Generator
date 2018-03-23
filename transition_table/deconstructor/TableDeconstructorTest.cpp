//
// Created by programajor on 3/23/18.
//

#include <fstream>
#include "../../p1_tests.h"
#include "../reader/TableReader.h"
#include "TableDeconstructor.h"

void test_transition_table_deconstructor(void) {
    std::streambuf * buf;
    std::ifstream of;
    of.open("file2.txt");
    buf = of.rdbuf();
//    buf = std::cout.rdbuf();
    std::ostream out(buf);

    TableReader reader;
    TransitionTable* table = reader.readTransitionTable(&of);

    TableDeconstructor deconstructor;
    vector<DfaNode*> nodes = deconstructor.deconstructGraph(*table);

    nodes.size();

}