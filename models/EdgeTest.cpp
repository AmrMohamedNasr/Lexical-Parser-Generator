/*
 * EdgeTest.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */

#include "Edge.h"
#include <iostream>

using namespace std;

void test_edge(void) {
	Edge e('a','z',NULL);
	bool error = false;
	if (!e.valid_transition('a')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (!e.valid_transition('z')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (e.valid_transition('A')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (!e.valid_transition('f')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	e.disallow_character('f');
	if (e.valid_transition('f')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	e.disallow_character('a');
	if (e.valid_transition('f')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (e.valid_transition('a')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (!e.valid_transition('z')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (!error) {
		cout << "Edge Success..." << endl;
	}
}
