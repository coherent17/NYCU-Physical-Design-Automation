#ifndef _STANDARD_CELL_H_
#define _STANDARD_CELL_H_

#include "FinFET.h"
#include <bits/stdc++.h>
using namespace std;

class Standard_Cell{
    public:
        vector<FinFET *> FinFETs;
        size_t Num_FinFETs;

    public:
        // Constructor & Destructor
        Standard_Cell();
        ~Standard_Cell();

        // Parser
        void Parse_Spice(ifstream &fin);
};

#endif