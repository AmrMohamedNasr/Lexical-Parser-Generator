////
//// Created by programajor on 3/21/18.
////
//
//using namespace std;
//
//#include <algorithm>
//#include "DfaEdge.h"
//
//DfaEdge::DfaEdge(char start, char end, DfaNode* source, DfaNode* target) {
//    this->first_allowed_char = start;
//    this->last_allowed_char = end;
//    this->allowing_range = end - start + 1;
//    this->source_node = source;
//    this->target_node = target;
//}
//
//void DfaEdge::disallow_character(char c) {
//    this->disallowed_chars.push_back(c);
//    if (c >= this->first_allowed_char && c <= this->last_allowed_char) {
//        this->allowing_range = c - this->first_allowed_char + 1;
//        if (c != this->last_allowed_char) {
//            DfaEdge* newEdge = (DfaEdge*) malloc(sizeof (DfaEdge));
//            new (newEdge) DfaEdge(c, this->last_allowed_char, this->source_node, this->target_node);
//            this->source_node->getEdges().push_back(&newEdge);
//        }
//    }
//}
//
//DfaNode* DfaEdge::do_transition(char c) {
//    if (this->valid_transition(c)) {
//        return this->target_node;
//    } else {
//        return nullptr;
//    }
//}
//
//bool DfaEdge::is_eps_transition() {
//    return this->first_allowed_char == '\0' && this->last_allowed_char == '\0';
//}
//
//int DfaEdge::getAllowedRange() {
//    return this->allowing_range;
//}
//
//bool DfaEdge::valid_transition(char c) {
//    if (find(this->disallowed_chars.begin(), this->disallowed_chars.end(), c) != this->disallowed_chars.end()) {
//        return false;
//    } else {
//        return c <= this->last_allowed_char && c >= this->first_allowed_char;
//    }
//}
//
//DfaNode* DfaEdge :: get_target_node() {
//    return this->target_node;
//}
//
//char DfaEdge :: get_first_allowed_char() {
//    return this->first_allowed_char;
//}
//
//char DfaEdge :: get_last_allowed_char() {
//    return this->last_allowed_char;
//}
//
//vector<char> DfaEdge :: get_disallowed_chars() {
//    return this->disallowed_chars;
//}
//
//void DfaEdge :: set_target_node(DfaNode* node) {
//    this->target_node = node;
//}