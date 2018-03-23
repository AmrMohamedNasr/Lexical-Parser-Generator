//
// Created by programajor on 3/23/18.
//

#include <iostream>
#include "../../p1_tests.h"
#include "../../minimizer/DfaMinimizer.h"
#include "../../models/DfaEdge.h"
#include "../model/TransitionTable.h"
#include "../builder/TableBuilder.h"
#include "TableWriter.h"


void test_transition_table_writer_human_form(void) {
    // sheet 2 1-c
    DfaNode x("X",false);
    DfaNode y("Y",true);
    DfaNode z("Z",false);
    DfaNode w("W",true);
    DfaNode t("T",true);
    DfaNode u("U",true);
    DfaNode v("V",true);
    DfaNode q("Q",true);
    DfaEdge xy('0', '0', &x, &y);
    DfaEdge yz('0', '0', &y, &z);
    DfaEdge yw('1', '1', &y, &w);
    DfaEdge zt('0', '0', &z, &t);
    DfaEdge zz('1', '1', &z, &z);
    DfaEdge wu('0', '0', &w, &u);
    DfaEdge wz('1', '1', &w, &z);
    DfaEdge tv('1', '1', &t, &v);
    DfaEdge uq('0', '0', &u, &q);
    DfaEdge uv('1', '1', &u, &v);
    DfaEdge vu('0', '0', &v, &u);
    DfaEdge vz('1', '1', &v, &z);
    DfaEdge qt('0', '0', &q, &t);
    DfaEdge qw('1', '1', &q, &w);
    q.addEdge(&qw);
    q.addEdge(&qt);
    v.addEdge(&vz);
    v.addEdge(&vu);
    u.addEdge(&uv);
    u.addEdge(&uq);
    t.addEdge(&tv);
    w.addEdge(&wz);
    w.addEdge(&wu);
    z.addEdge(&zz);
    z.addEdge(&zt);
    y.addEdge(&yw);
    y.addEdge(&yz);
    x.addEdge(&xy);

    DfaMinimizer g;
    vector<DfaNode*> result;
    g.getMinimizedDFA(&result, &x);

    vector<char> alphabets;
    alphabets.push_back('0');
    alphabets.push_back('1');

    TableBuilder builder;
    TransitionTable table = builder.buildTransitionTable(result, alphabets);

    vector<DfaNode *> nodes = table.getNodes();
    vector<string> input = table.getInputs();
    vector<vector<DfaNode *>> transitions = table.getTransitions();

    std::streambuf * buf;
    std::ofstream of;
    of.open("file1.txt");
    buf = of.rdbuf();
//    buf = std::cout.rdbuf();
    std::ostream out(buf);

    TableWriter writer;
    writer.writeTransitionTableInHumanReadableFormat(table, &out);
}

void test_transition_table_writer_readable_form(void) {
    // sheet 2 1-c
    DfaNode x("X",false);
    DfaNode y("Y",true);
    DfaNode z("Z",false);
    DfaNode w("W",true);
    DfaNode t("T",true);
    DfaNode u("U",true);
    DfaNode v("V",true);
    DfaNode q("Q",true);
    DfaEdge xy('0', '0', &x, &y);
    DfaEdge yz('0', '0', &y, &z);
    DfaEdge yw('1', '1', &y, &w);
    DfaEdge zt('0', '0', &z, &t);
    DfaEdge zz('1', '1', &z, &z);
    DfaEdge wu('0', '0', &w, &u);
    DfaEdge wz('1', '1', &w, &z);
    DfaEdge tv('1', '1', &t, &v);
    DfaEdge uq('0', '0', &u, &q);
    DfaEdge uv('1', '1', &u, &v);
    DfaEdge vu('0', '0', &v, &u);
    DfaEdge vz('1', '1', &v, &z);
    DfaEdge qt('0', '0', &q, &t);
    DfaEdge qw('1', '1', &q, &w);
    q.addEdge(&qw);
    q.addEdge(&qt);
    v.addEdge(&vz);
    v.addEdge(&vu);
    u.addEdge(&uv);
    u.addEdge(&uq);
    t.addEdge(&tv);
    w.addEdge(&wz);
    w.addEdge(&wu);
    z.addEdge(&zz);
    z.addEdge(&zt);
    y.addEdge(&yw);
    y.addEdge(&yz);
    x.addEdge(&xy);

    DfaMinimizer g;
    vector<DfaNode*> result;
    g.getMinimizedDFA(&result, &x);

    vector<char> alphabets;
    alphabets.push_back('0');
    alphabets.push_back('1');

    TableBuilder builder;
    TransitionTable table = builder.buildTransitionTable(result, alphabets);

    vector<DfaNode *> nodes = table.getNodes();
    vector<string> input = table.getInputs();
    vector<vector<DfaNode *>> transitions = table.getTransitions();

    std::streambuf * buf;
    std::ofstream of;
    of.open("file2.txt");
    buf = of.rdbuf();
//    buf = std::cout.rdbuf();
    std::ostream out(buf);

    TableWriter writer;
    writer.writeTransitionTableInReadableForamt(table, &out);
}