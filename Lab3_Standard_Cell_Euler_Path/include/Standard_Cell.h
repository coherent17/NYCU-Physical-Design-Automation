#ifndef _STANDARD_CELL_H_
#define _STANDARD_CELL_H_

#include "FinFET.h"
#include "Design_Rule.h"
#include <bits/stdc++.h>
using namespace std;

#define PRINT_FINFET_INFO true

class Standard_Cell{
    public:
        vector<FinFET *> FinFETs;
        vector<FinFET *> N_FinFETs;
        vector<FinFET *> P_FinFETs;
        multimap<string, FinFET *> N_Poly_Map;
        multimap<string, FinFET *> P_Poly_Map;
        size_t Num_FinFETs;
        set<string> Nodes;

        vector<string> Poly_Sequence;
        vector<string> Poly_Sequence_With_Dummy;
        vector<pair<FinFET *, FinFET *>> Layout;


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