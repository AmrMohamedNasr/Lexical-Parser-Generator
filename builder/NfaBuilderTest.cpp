//
// Created by marc on 3/20/18.
//
#include "NfaBuilder.h"
#include "../p1_tests.h"

using namespace std;

static const vector<NfaToken> correctTokens = {
        NfaToken (REGULAR_EXPRESSION, "id", vector<MiniToken> ({
               MiniToken (CHAR_GROUP, "a-z"),
               MiniToken (CHAR_GROUP, "A-Z"),
               MiniToken (OPERATION, "|"),
               MiniToken (CHAR_GROUP, "a-z"),
               MiniToken (CHAR_GROUP, "A-Z"),
               MiniToken (OPERATION, "|"),
               MiniToken (CHAR_GROUP, "0-9"),
               MiniToken (OPERATION, "|"),
               MiniToken (OPERATION, "*"),
               MiniToken (OPERATION, "@")
         })),
        NfaToken (KEYWORD, "boolean", vector<MiniToken> ({MiniToken (WORD, "boolean")})),
        NfaToken (KEYWORD, "int", vector<MiniToken> ({MiniToken (WORD, "int")})),
        NfaToken (KEYWORD, "float", vector<MiniToken> ({MiniToken (WORD, "float")})),
        NfaToken (REGULAR_EXPRESSION, "num", vector<MiniToken> ({
            MiniToken (CHAR_GROUP, "0-9"),
            MiniToken (OPERATION, "+"),
            MiniToken (CHAR_GROUP, "0-9"),
            MiniToken (OPERATION, "+"),
            MiniToken (OPERATION, "|"),
            MiniToken (WORD, "."),
            MiniToken (OPERATION, "@"),
            MiniToken (CHAR_GROUP, "0-9"),
            MiniToken (OPERATION, "+"),
            MiniToken (OPERATION, "@"),
            MiniToken (EPSILON, "\\L"),
            MiniToken (WORD, "E"),
            MiniToken (CHAR_GROUP, "0-9"),
            MiniToken (OPERATION, "+"),
            MiniToken (OPERATION, "@"),
            MiniToken (OPERATION, "|"),
            MiniToken (OPERATION, "@")
                    })),
        NfaToken (REGULAR_EXPRESSION, "relop", vector<MiniToken> ({
              MiniToken (WORD, "=="),
              MiniToken (WORD, "!="),
              MiniToken (OPERATION, "|"),
              MiniToken (WORD, ">"),
              MiniToken (OPERATION, "|"),
              MiniToken (WORD, ">="),
              MiniToken (OPERATION, "|"),
              MiniToken (WORD, "<"),
              MiniToken (OPERATION, "|"),
              MiniToken (WORD, "<="),
              MiniToken (OPERATION, "|")
                                          })),
        NfaToken (REGULAR_EXPRESSION, "assign", vector<MiniToken> ({MiniToken (WORD, "=")})),
        NfaToken (KEYWORD, "if", vector<MiniToken> ({MiniToken (WORD, "if")})),
        NfaToken (KEYWORD, "else", vector<MiniToken> ({MiniToken (WORD, "else")})),
        NfaToken (KEYWORD, "while", vector<MiniToken> ({MiniToken (WORD, "while")})),
        NfaToken (PUNCTUATION, ";", vector<MiniToken> ({MiniToken (WORD, ";")})),
        NfaToken (PUNCTUATION, ",", vector<MiniToken> ({MiniToken (WORD, ",")})),
        NfaToken (PUNCTUATION, "(", vector<MiniToken> ({MiniToken (WORD, "(")})),
        NfaToken (PUNCTUATION, ")", vector<MiniToken> ({MiniToken (WORD, ")")})),
        NfaToken (PUNCTUATION, "{", vector<MiniToken> ({MiniToken (WORD, "{")})),
        NfaToken (PUNCTUATION, "}", vector<MiniToken> ({MiniToken (WORD, "}")})),
        NfaToken (REGULAR_EXPRESSION, "addop", vector<MiniToken> ({
                  MiniToken (WORD, "+"),
                  MiniToken (WORD, "-"),
                  MiniToken (OPERATION, "|"),
          })),
        NfaToken (REGULAR_EXPRESSION, "mulop", vector<MiniToken> ({
                  MiniToken (WORD, "*"),
                  MiniToken (WORD, "/"),
                  MiniToken (OPERATION, "|"),
          }))
};

void test_nfa_builder() {
    vector<NfaToken> nfaTokens;
    // id: a-z | eps
    NfaToken t1(REGULAR_EXPRESSION, "id");
    MiniToken m1(CHAR_GROUP, "a-z");
    MiniToken m2(EPSILON, "eps");
    MiniToken m3(OPERATION, "|");
    t1.tokens.push_back(m1);
    t1.tokens.push_back(m2);
    t1.tokens.push_back(m3);

    nfaTokens.push_back(t1);
//
    NfaBuilder nfaBuilder;
    nfaBuilder.get_separated_nfas(nfaTokens);
}
