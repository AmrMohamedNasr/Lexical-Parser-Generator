/* 
 * GrammarTable.cpp
 * Created on: 4/20/18
 *     Author: marc
 */

#include "GrammarTable.h"

bool GrammarTable::add_entry(string non_terminal, string terminal, vector<string> rules) {
    bool exist = has_entry(non_terminal, terminal);
    pair<string, string> nt_t_pair = make_pair(non_terminal, terminal);
    if (!exist) {
        table.insert(make_pair(nt_t_pair, rules));
        non_terminals.insert(non_terminal);
        terminals.insert(terminal);
    }

    return !exist;
}

bool GrammarTable::has_entry(string non_terminal, string terminal) {
    bool exist = false;
    pair<string, string> nt_t_pair = make_pair(non_terminal, terminal);
    if (table.find(nt_t_pair) != table.end()) {
        exist = true;
    }

    return exist;
}

vector<string> GrammarTable::get_entry(string non_terminal, string terminal) {
    if (!has_entry(non_terminal, terminal)) {
        return {};
    }

    auto got = table.find(make_pair(non_terminal, terminal));
    return  got.operator->()->second;
}

void GrammarTable::add_synch(string non_terminal, string terminal) {
    synchronizing.insert(make_pair(non_terminal, terminal));
}

bool GrammarTable::is_synch(string non_terminal, string terminal) {
    return synchronizing.find(make_pair(non_terminal, terminal)) != synchronizing.end();
}

vector<string> GrammarTable::get_terminals() {
    auto ret = new vector<string>();
    ret->insert(ret->end(), terminals.begin(), terminals.end());
    return *ret;
}

vector<string> GrammarTable::get_non_terminals() {
    auto ret = new vector<string>();
    ret->insert(ret->end(), non_terminals.begin(), non_terminals.end());
    return *ret;
}

void GrammarTable::set_terminals(vector<string> term) {
    terminals = unordered_set<string>(term.begin(), term.end());
}

void GrammarTable::set_non_terminals(vector<string> non_term) {
    non_terminals = unordered_set<string>(non_term.begin(), non_term.end());
}

bool GrammarTable::is_terminal(string str) {
    return terminals.find(str) != terminals.end();
}

bool GrammarTable::is_non_terminal(string str) {
    return non_terminals.find(str) != non_terminals.end();
}

string GrammarTable::get_start() {
    return start_rule;
}

void GrammarTable::set_start(string str) {
    start_rule = str;
}

unsigned long GrammarTable::get_sync_elements_count() {
    return synchronizing.size();
}

unsigned long GrammarTable::get_table_elements_count() {
    return table.size();
}

bool GrammarTable::compare_table(GrammarTable *grammarTable) {
    auto t1 = this->table;
    auto t2 = grammarTable->table;
    if (t1.size() != t2.size()) {
        return false;
    }

    return std::equal(t1.begin(), t1.end(), t2.begin());
}

bool GrammarTable::compare_sync(GrammarTable *grammarTable) {
    auto s1 = this->synchronizing;
    auto s2 = grammarTable->synchronizing;
    if (s1.size() != s2.size()) {
        return false;
    }

    return std::equal(s1.begin(), s1.end(), s2.begin());
}

