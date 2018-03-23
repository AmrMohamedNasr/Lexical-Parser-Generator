//
// Created by programajor on 3/23/18.
//

#include <iostream>
#include "TableReader.h"

TransitionTable* TableReader::readTransitionTable(ifstream *stream) {
    vector<DfaNode * > nodes;
    vector<string> input;
    vector<vector<DfaNode * >> transitions;

    string line;
    if (stream->is_open()) {
        if (!getline(*stream, line)) {
            cout << "ERROR: In Line 1" << endl;
            return nullptr;
        }
        int nodesCount = readInt(line);
        if (nodesCount == -1) {
            cout << "ERROR: In Line 1" << endl;
            return nullptr;
        }

        for (int i = 0; i < nodesCount; ++i) {
            vector<DfaNode*> vec;
            transitions.push_back(vec);
            DfaNode* node = new DfaNode("", false);
            node->sePrintingtName("n" + std::to_string(i + 1));
            nodes.push_back(node);
        }
        nodes[nodes.size() - 1]->sePrintingtName("phi");

        if (!getline(*stream, line)) {
            cout << "ERROR: In Line 2" << endl;
            return nullptr;
        }

        for (int i = 0; i < nodes.size(); i++) {
            if (i < line.length()) {
                if (line[i] == '0') nodes[i]->setAcceptState(false);
                else if (line[i] == '1') nodes[i]->setAcceptState(true);
            } else {
                cout << "ERROR: In Line 2" << endl;
                return nullptr;
            }
        }

        if (!getline(*stream, line)) {
            cout << "ERROR: In Line 3" << endl;
            return nullptr;
        }

        for (int i = 0; i < nodes.size(); i++) {
            if (i < line.length()) {
                if (line[i] == '0') nodes[i]->setStart(false);
                else if (line[i] == '1') nodes[i]->setStart(true);
            } else {
                cout << "ERROR: In Line 3" << endl;
                return nullptr;
            }
        }

        for (int i = 0; i < nodesCount; ++i) {
            if (!getline(*stream, line)) {
                cout << "ERROR: In Line " << (i + 4) << endl;
                return nullptr;
            }
            string name = getName(line);
            if (name == "") {
                cout << "ERROR: In Line " << (i + 4) << endl;
                return nullptr;
            }
            nodes[i]->setName(name);
        }

        if (!getline(*stream, line)) {
            cout << "ERROR: In Line " << (4 + nodesCount) << endl;
            return nullptr;
        }

        int inputCount = readInt(line);
        if (inputCount == -1) {
            cout << "ERROR: In Line " << (4 + nodesCount) << endl;
            return nullptr;
        }

        for (int i = 0; i < inputCount; ++i) {
            if (!getline(*stream, line)) {
                cout << "ERROR: In Line " << (4 + nodesCount) << endl;
                return nullptr;
            }
            string singleInput = getInput(line);
            if (singleInput.size() % 3 != 0) {
                cout << "ERROR: In Line " << (4 + nodesCount) << endl;
                return nullptr;
            }
            input.push_back(singleInput);
        }

        for (int i = 0; i < nodes.size(); ++i) {
            for (int j = 0; j < input.size(); ++j) {
                if (!getline(*stream, line)) {
                    cout << "ERROR: In Transitions" << endl;
                    return nullptr;
                }
                string name = getName(line);
                if (name == "") {
                    cout << "ERROR: In Transitions" << endl;
                    return nullptr;
                }
                DfaNode* nextNode = getNodeFromPrintingName(name, nodes);
                if (nextNode == nullptr) {
                    cout << "ERROR: In Transitions" << endl;
                    return nullptr;
                }
                transitions[i].push_back(nextNode);
            }
        }
    }

    return new TransitionTable(nodes, input, transitions);
}

int TableReader::readInt(string line) {
    string num = "";
    int i = 0;
    while (i < line.length() && line[i] != ' ') {
        if (line[i] >= '0' && line[i] <= '9') num += line[i];
        else return -1;
        i++;
    }
    return stoi(num);
}

string TableReader::getName(string line) {
    string name = "";
    int i = 0;
    while (i < line.length() && line[i] != ' ') {
        if ((line[i] >= '0' && line[i] <= '9') ||
            (line[i] >= 'a' && line[i] <= 'z') ||
            (line[i] >= 'A' && line[i] <= 'Z')) {
            name += line[i];
        } else {
            return nullptr;
        }
        i++;
    }
    return name;
}

string TableReader::getInput(string line) {
    string input = "";
    int i = 0;
    while (i < line.length() && line[i] != ' ') {
        input += line[i];
        i++;
    }
    return input;
}

DfaNode *TableReader::getNodeFromPrintingName(string name, vector<DfaNode *> nodes) {
    for (int i = 0; i < nodes.size(); ++i) {
        DfaNode* curr = nodes[i];
        if (curr->getPrintingName() == name) {
            return curr;
        }
    }
    return nullptr;
}
