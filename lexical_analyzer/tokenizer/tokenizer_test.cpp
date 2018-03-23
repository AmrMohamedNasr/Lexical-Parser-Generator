/*
 * tokenizer_test.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#include <iostream>
#include "../../p1_tests.h"
#include "../../models/DfaNode.h"
#include "../../models/DfaEdge.h"
#include "tokenizer.h"


void tokenizer_test_1();

void test_tokenizer() {
    tokenizer_test_1();
}


void tokenizer_test_1() {
    DfaNode * n1 = new DfaNode("n1-end",true);
    DfaNode * n2 = new DfaNode("n2",false);
    DfaNode * n3 = new DfaNode("n3-end",true);
    DfaNode * n4 = new DfaNode("n4",false);
    DfaNode * n5 = new DfaNode("n5",false);
    DfaNode * n6 = new DfaNode("n6",false);
    DfaNode * n7 = new DfaNode("n7-end",true);

    DfaEdge * n1n2 = new DfaEdge('1', '1', n1, n2);
    DfaEdge * n1n5 = new DfaEdge('0', '0', n1, n5);
    DfaEdge * n2n3 = new DfaEdge('0', '0', n2, n3);
    DfaEdge * n2n6 = new DfaEdge('1', '1', n2, n6);
    DfaEdge * n3n4 = new DfaEdge('0', '0', n3, n4);
    DfaEdge * n3n7 = new DfaEdge('1', '1', n3, n7);
    DfaEdge * n4n4 = new DfaEdge('0', '1', n4, n4);
    DfaEdge * n5n5 = new DfaEdge('0', '1', n5, n5);
    DfaEdge * n6n5 = new DfaEdge('1', '1', n6, n5);
    DfaEdge * n6n1 = new DfaEdge('0', '0', n6, n1);
    DfaEdge * n7n3 = new DfaEdge('0', '0', n7, n3);
    DfaEdge * n7n2 = new DfaEdge('1', '1', n7, n2);

    n1->addEdge(n1n2);
    n1->addEdge(n1n5);
    n2->addEdge(n2n3);
    n2->addEdge(n2n6);
    n3->addEdge(n3n4);
    n3->addEdge(n3n7);
    n4->addEdge(n4n4);
    n5->addEdge(n5n5);
    n6->addEdge(n6n1);
    n6->addEdge(n6n5);
    n7->addEdge(n7n2);
    n7->addEdge(n7n3);

    auto tokenizer = new Tokenizer(n1);


    string s1 = "";
    string s2 = "10101010";
    string s3 = "10101110";
    tokenizer->tokenize(s1);
    int i = 0;
    string expectedClasses[] = {"n1-end"};
    string expectedLexemes[] = {""};
    TOKEN_TYPE expectedTypes[] = {REAL_TOKEN};
    bool error = false;
    while (tokenizer->hasNext()) {
        Token t = tokenizer->nextToken();
        if (t.lexme != expectedLexemes[i] || t.token_class != expectedClasses[i]
                || t.type != expectedTypes[i]) {
            cout << "Tokenizer: test 1 error: " << i;
            error = true;
        }

        i++;
    }

    int i2 = 0;
    string expectedClasses2[] = {"n7-end", "n5-end", "n1-end"};
    string expectedLexemes2[] = {"10", "01", "110"};
    TOKEN_TYPE expectedTypes2[] = {REAL_TOKEN, ERROR_TOKEN, REAL_TOKEN};

    tokenizer->tokenize(s2);
    while (tokenizer->hasNext()) {
        Token t = tokenizer->nextToken();

        if (t.lexme != expectedLexemes2[i] || t.token_class != expectedClasses2[i]
            || t.type != expectedTypes2[i]) {
            cout << "Tokenizer: test 2 error: " << i;
            error = true;
        }

        i2++;
    }


    if (!error) {
        cout << "Tokenizer Success..." << endl;
    }
}