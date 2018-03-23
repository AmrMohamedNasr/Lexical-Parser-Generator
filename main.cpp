
#include <iostream>
#include "p1_tests.h"
#include "models/Node.h"
#include "converter/NfaDfaConverter.h"

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
	test_minimizer();
	test_nfa_builder();
    test_nfa_dfa_converter();
	test_transition_table_builder();
    test_transition_table_writer_human_form();
    test_transition_table_writer_readable_form();
}
