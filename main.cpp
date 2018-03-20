
#include <iostream>
#include "p1_tests.h"
#include "models/Node.h"
#include "converter/NfaDfaConverter.h"

using namespace std;

void run_tests(void);

int main() {
//	run_tests();
	Node n1 = Node("1", false);
	Node n2 = Node("2", false);
	Node n3 = Node("3_if", true);
	Node n4 = Node("4", false);
	Node n5 = Node("5", false);
	Node n6 = Node("6", false);
	Node n7 = Node("7", false);
	Node n8 = Node("8_then", true);
	Node n9 = Node("9", false);
	Node n10 = Node("10", false);
	Node n11 = Node("11", false);
	Node n12 = Node("12", false);
	Node n13 = Node("13_else", true);
	Node n14 = Node("14", false);
	Node n15 = Node("15", false);
	Node n16 = Node("16", false);
	Node n17 = Node("17", false);
	Node n18 = Node("18", false);
	Node n19 = Node("19", false);
	Node n20 = Node("20_operation", true);
	Node n21 = Node("21", false);
	Node n22 = Node("22", false);
	Node n23 = Node("23_id", true);
	Node n24 = Node("24", false);
	Node n25 = Node("25_num", true);

	Edge e1 = Edge('\0', '\0', &n1);
	Edge e2 = Edge('\0', '\0', &n4);
	Edge e3 = Edge('\0', '\0', &n9);
	Edge e4 = Edge('\0', '\0', &n14);
	Edge e5 = Edge('\0', '\0', &n17);
	Edge e6 = Edge('\0', '\0', &n18);
	Edge e7 = Edge('\0', '\0', &n21);
	Edge e8 = Edge('\0', '\0', &n22);
	Edge e9 = Edge('\0', '\0', &n24);

	n17.addEdge(&e4);
	n17.addEdge(&e6);
	n17.addEdge(&e7);

	n16.addEdge(&e1);
	n16.addEdge(&e2);
	n16.addEdge(&e3);
	n16.addEdge(&e5);
	n16.addEdge(&e8);
	n16.addEdge(&e9);

	Edge e10 = Edge('i', 'i', &n2);
	Edge e11 = Edge('f', 'f', &n3);

	n1.addEdge(&e10);
	n2.addEdge(&e11);

	Edge e12 = Edge('t', 't', &n5);
	Edge e13 = Edge('h', 'h', &n6);
	Edge e14 = Edge('e', 'e', &n7);
	Edge e15 = Edge('n', 'n', &n8);

	n4.addEdge(&e12);
	n5.addEdge(&e13);
	n6.addEdge(&e14);
	n7.addEdge(&e15);

	Edge e29 = Edge('e', 'e', &n10);
	Edge e30 = Edge('l', 'l', &n11);
	Edge e31 = Edge('s', 's', &n12);
	Edge e32 = Edge('e', 'e', &n13);

	n9.addEdge(&e29);
	n10.addEdge(&e30);
	n11.addEdge(&e31);
	n12.addEdge(&e32);

	Edge e16 = Edge('<', '<', &n15);
	Edge e17 = Edge('=', '=', &n20);
	Edge e18 = Edge('>', '>', &n20);
	Edge e19 = Edge('>', '>', &n19);
	Edge e20 = Edge('=', '=', &n20);
	Edge e21 = Edge('=', '=', &n20);

	n14.addEdge(&e16);
	n15.addEdge(&e17);
	n15.addEdge(&e18);
	n18.addEdge(&e19);
	n19.addEdge(&e20);
	n21.addEdge(&e21);

	Edge e22 = Edge('a', 'z', &n23);
	Edge e23 = Edge('A', 'Z', &n23);
	Edge e24 = Edge('a', 'z', &n23);
	Edge e25 = Edge('A', 'Z', &n23);
	Edge e26 = Edge('0', '9', &n23);
	Edge e27 = Edge('0', '9', &n25);
	Edge e28 = Edge('0', '9', &n25);

	n22.addEdge(&e22);
	n22.addEdge(&e23);
	n23.addEdge(&e24);
	n23.addEdge(&e25);
	n23.addEdge(&e26);
	n24.addEdge(&e27);
	n25.addEdge(&e28);

//	n3->setAcceptState(true);
//	n8->setAcceptState(true);
//	n13->setAcceptState(true);
//	n15->setAcceptState(true);
//	n19->setAcceptState(true);
//	n20->setAcceptState(true);
//	n23->setAcceptState(true);
//	n25->setAcceptState(true);

	NfaDfaConverter converter;
	converter.getNonMinimizedDFA(&n16);

//	printf("test\n");
    return 0;
}


void run_tests() {
	test_edge();
	test_node();
	test_grammar_parser();
	test_nfa_builder();
//	test_edge();
//	test_node();
//	test_grammar_parser();

}
