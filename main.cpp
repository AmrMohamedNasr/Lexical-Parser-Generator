#include <iostream>
#include "p1_tests.h"

using namespace std;

void run_tests(void);


int main() {
	run_tests();
    return 0;
}


void run_tests() {
	test_edge();
	test_node();
	test_grammar_parser();
	test_nfa_builder();
}
