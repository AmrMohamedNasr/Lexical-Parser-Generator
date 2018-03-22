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


void minimizer_test_3() {
	DfaNode x("X",false);
	DfaNode y("Y",false);
	DfaNode z("Z",true);
	DfaNode w("W",false);
	DfaNode t("T",false);
	DfaNode u("U",true);
	DfaNode v("V",true);
	DfaNode phi("", true);
	DfaEdge xy('0', '0', &x, &y);
	DfaEdge xz('1', '1', &x, &z);
	DfaEdge yy('0', '0', &y, &y);
	DfaEdge yw('1', '1', &y, &w);
	DfaEdge zt('0', '0', &z, &t);
	DfaEdge zu('1', '1', &z, &u);
	DfaEdge wt('0', '0', &w, &t);
	DfaEdge wv('1', '1', &w, &v);
	DfaEdge ty('0', '0', &t, &y);
	DfaEdge tz('1', '1', &t, &z);
	DfaEdge uphi('0', '0', &u, &phi);
	DfaEdge ut('1', '1', &u, &t);
	DfaEdge vy('0', '0', &v, &y);
	DfaEdge vy_1('1', '1', &v, &y);
	DfaEdge phiphi('0', '0', &phi, &phi);
	DfaEdge phiphi_1('1', '1', &phi, &phi);
	x.addEdge(&xz);
	x.addEdge(&xy);
	t.addEdge(&ty);
	t.addEdge(&tz);
	w.addEdge(&wv);
	w.addEdge(&wt);
	z.addEdge(&zt);
	z.addEdge(&zu);
	y.addEdge(&yy);
	y.addEdge(&yw);
	phi.addEdge(&phiphi);
	phi.addEdge(&phiphi_1);
	v.addEdge(&vy_1);
	v.addEdge(&vy);
	u.addEdge(&uphi);
	u.addEdge(&ut);

	DfaMinimizer g;
	DfaNode* result = g.getMinimizedDFA(&x);
	if ((result->getEdges()[0]->get_target_node()) != &z){
		cout << "error4" << endl;
	}
	if ((result->getEdges()[1]->get_target_node()) != &y){
			cout << "error5" << endl;
	}
	if ((z.getEdges()[1]->get_target_node()) != result){
				cout << "error hna" << endl;
	}
	cout << "Minimizer Success..." << endl;
}


void minimizer_test_2() {
	DfaNode x("X",false);
	DfaNode y("Y",false);
	DfaNode z("Z",true);
	DfaNode w("W",false);
	DfaNode t("T",false);
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
		cout << "error1" << endl;
	}
	if ((result->getEdges()[1]->get_target_node()) != &z){
			cout << "error2" << endl;
	}
	if ((z.getEdges()[0]->get_target_node()) != result
			|| (z.getEdges()[1]->get_target_node()) != result){
				cout << "error3" << endl;
	}
	minimizer_test_3();
}


void test_minimizer(void) {
	DfaNode x("X",false);
	DfaNode y("Y",true);
	DfaNode z("Z",false);
	DfaNode w("W",true);
	DfaNode t("T",true);
	DfaNode u("U",true);
	DfaNode v("V",true);
	DfaNode q("Q",true);
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

	minimizer_test_2();

}

