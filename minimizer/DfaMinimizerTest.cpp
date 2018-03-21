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


void another_minimizer_test() {
	Node x("A",false);
	Node y("B",false);
	Node z("C",true);
	Node w("D",false);
	Node t("E",false);
	Edge xy('0', '0', &y);
	Edge xz('1', '1', &z);
	Edge yx('0', '0', &x);
	Edge yz('1', '1', &z);
	Edge zx('0', '0', &x);
	Edge zw('1', '1', &w);
	Edge wt('0', '0', &t);
	Edge wz('1', '1', &z);
	Edge tt('0', '0', &t);
	Edge tz('1', '1', &z);
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
	Node* result = g.getMinimizedDFA(&x);
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
//	if (result->getEdges()[1]->get_target_node() != z){
//		cout << "error" << endl;
//	}
//	if (z.getEdges()[0]->get_target_node() != x ||
//			z.getEdges()[0]->get_target_node() != x ||
//			&z.getEdges()[0]->get_target_node() != &y ||
//			&z.getEdges()[0]->get_target_node() != &w ||
//			&z.getEdges()[0]->get_target_node() != &t) {
//		cout << "error" << endl;
//	}
}


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

	another_minimizer_test();

}

