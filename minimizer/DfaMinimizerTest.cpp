/*
 * DfaMinimizerTest.cpp
 *
 *  Created on: Mar 20, 2018
 *      Author: michael
 */
#include "../p1_tests.h"
#include <vector>
#include <iostream>
#include "../models/DfaNode.h"
#include "../models/DfaEdge.h"
#include <string>
#include "../minimizer/DfaMinimizer.h"
using namespace std;


void another_minimizer_test() {
	DfaNode x("A",false);
	DfaNode y("B",false);
	DfaNode z("C",true);
	DfaNode w("D",false);
	DfaNode t("E",false);
	DfaEdge xy('0', '0', &x, &y);
	DfaEdge xz('1', '1', &x, &z);
	DfaEdge yx('0', '0', &y, &x);
	DfaEdge yz('1', '1', &y, &z);
	DfaEdge zx('0', '0', &z, &x);
	DfaEdge zw('1', '1', &z, &w);
	DfaEdge wt('0', '0', &w, &t);
	DfaEdge wz('1', '1', &w, &z);
	DfaEdge tt('0', '0', &t, &t);
	DfaEdge tz('1', '1', &t, &z);
	x.addEdge(&xy);
	t.addEdge(&tz);
	t.addEdge(&tt);
	w.addEdge(&wz);
	w.addEdge(&wt);
	z.addEdge(&zw);
	z.addEdge(&zx);
	y.addEdge(&yx);
	y.addEdge(&yz);
	x.addEdge(&xz);
	DfaMinimizer g;
	DfaNode* result = g.getMinimizedDFA(&x);
	if ((result->getEdges()[0]->get_target_node()) != result){
		cout << "error" << endl;
	}
	if ((result->getEdges()[1]->get_target_node()) != &z){
			cout << "error" << endl;
	}
	if ((z.getEdges()[0]->get_target_node()) != result
			&& (z.getEdges()[1]->get_target_node()) != result){
				cout << "error" << endl;
	}
	cout << "Minimizer Success..." << endl;
}


void test_minimizer(void) {
	DfaNode x("A",false);
	DfaNode y("B",true);
	DfaNode z("C",false);
	DfaNode w("D",true);
	DfaNode t("E",true);
	DfaNode u("K",true);
	DfaNode v("H",true);
	DfaNode q("G",true);
	DfaNode e("\0", false);
	DfaEdge xy('0', '0', &x, &y);
	DfaEdge xe('1', '1', &x, &e);
	DfaEdge yz('0', '0', &y, &z);
	DfaEdge yw('1', '1', &y, &w);
	DfaEdge zt('0', '0', &z, &t);
	DfaEdge zz('1', '1', &z, &z);
	DfaEdge wu('0', '0', &w, &u);
	DfaEdge wz('1', '1', &w, &z);
	DfaEdge te('0', '0', &t, &e);
	DfaEdge tv('1', '1', &t, &v);
	DfaEdge uq('0', '0', &u, &q);
	DfaEdge uv('1', '1', &u, &v);
	DfaEdge vu('0', '0', &v, &u);
	DfaEdge vz('1', '1', &v, &z);
	DfaEdge qt('0', '0', &q, &t);
	DfaEdge qw('1', '1', &q, &w);
	DfaEdge ee('0', '0', &e, &e);
	DfaEdge ee1('1', '1', &e, &e);
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
	DfaNode * result = g.getMinimizedDFA(&x);

	another_minimizer_test();

}

