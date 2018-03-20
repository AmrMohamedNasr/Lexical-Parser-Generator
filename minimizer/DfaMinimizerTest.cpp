/*
 * DfaMinimizerTest.cpp
 *
 *  Created on: Mar 20, 2018
 *      Author: michael
 */
#include "../p1_tests.h"
#include <vector>
#include <iostream>
#include "../models/Node.h"
#include "../models/Edge.h"
#include <string>
#include "../minimizer/DfaMinimizer.h"
using namespace std;

void test_minimizer(void) {
	Node a("A",false);
	Node b("B",false);
	Node c("C",false);
	Node d("D",false);
	Node e("E",true);
	Edge ab('a', 'a', &b);
	Edge ac('b', 'b', &c);
	Edge cc('b', 'b', &c);
	Edge ec('b', 'b', &c);
	Edge de('b', 'b', &e);
	Edge bd('b', 'b', &d);
	Edge cb('a', 'a', &b);
	Edge bb('a', 'a', &b);
	Edge db('a', 'a', &b);
	Edge eb('a', 'a', &b);
	e.addEdge(&ec);
	e.addEdge(&eb);
	d.addEdge(&db);
	d.addEdge(&de);
	c.addEdge(&cc);
	c.addEdge(&cb);
	b.addEdge(&bb);
	b.addEdge(&bd);
	a.addEdge(&ab);
	a.addEdge(&ac);
	DfaMinimizer g;
	Closure cl(1);
	Element ele(&a);
	cl.addEle(&ele);
	bool flag = cl.nodeExists(&ele);
	if (!flag) {
		cout << "error\n";
	}
	cl.removeEle(&ele);



}

