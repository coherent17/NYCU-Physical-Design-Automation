#ifndef _STANDARD_CELL_H_
#define _STANDARD_CELL_H_

#include "FinFET.h"
#include <bits/stdc++.h>
using namespace std;

#define PRINT_FINFET_INFO true

class Standard_Cell{
    public:
        vector<FinFET *> FinFETs;
        vector<FinFET *> N_FinFETs;
        vector<FinFET *> P_FinFETs;
        size_t Num_FinFETs;

        vector<string> Poly_Sequence;
        vector<string> Poly_Sequence_With_Dummy;

    public:
        // Constructor & Destructor
        Standard_Cell();
        ~Standard_Cell();

        // Parser
        void Parse_Spice(ifstream &fin);

        // Init the sequence
        void Init_Sequence();
};

#endif