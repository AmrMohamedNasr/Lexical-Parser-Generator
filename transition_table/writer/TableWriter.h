//
// Created by programajor on 3/23/18.
//

#ifndef COMPILERS_TABLEWRITER_H
#define COMPILERS_TABLEWRITER_H


#include <fstream>
#include "../model/TransitionTable.h"

class TableWriter {
public:
    void writeTransitionTable(TransitionTable table, ostream stream);
};


#endif //COMPILERS_TABLEWRITER_H
