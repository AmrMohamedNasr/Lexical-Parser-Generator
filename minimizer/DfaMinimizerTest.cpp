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
	Node x("A",false);
	Node y("B",true);
	Node z("C",false);
	Node w("D",true);
	Node t("E",true);
	Node u("K",true);
	Node v("H",true);
	Node q("G",true);
	Node e("\0", false);
	Edge xy('0', '0', &y);
	Edge xe('1', '1', &e);
	Edge yz('0', '0', &z);
	Edge yw('1', '1', &w);
	Edge zt('0', '0', &t);
	Edge zz('1', '1', &z);
	Edge wu('0', '0', &u);
	Edge wz('1', '1', &z);
	Edge te('0', '0', &e);
	Edge tv('1', '1', &v);
	Edge uq('0', '0', &q);
	Edge uv('1', '1', &v);
	Edge vu('0', '0', &u);
	Edge vz('1', '1', &z);
	Edge qt('0', '0', &t);
	Edge qw('1', '1', &w);
	Edge ee('0', '0', &e);
	Edge ee1('1', '1', &e);
	e.addEdge(&ee);
	e.addEdge(&ee1);
	q.addEdge(&qw);
	q.addEdge(&qt);
	v.addEdge(&vz);
	v.addEdge(&vu);
	u.addEdge(&uv);
	u.addEdge(&uq);
	t.addEdge(&te);
	t.addEdge(&tv);
	w.addEdge(&wz);
	w.addEdge(&wu);
	z.addEdge(&zz);
	z.addEdge(&zt);
	y.addEdge(&yw);
	y.addEdge(&yz);
	x.addEdge(&xy);
	x.addEdge(&xe);
	DfaMinimizer g;
	Closure cl(1);

	Node * result = g.getMinimizedDFA(&x);
	cout << "result is here";



}

