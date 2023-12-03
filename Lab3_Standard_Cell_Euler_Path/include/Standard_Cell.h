#ifndef _STANDARD_CELL_H_
#define _STANDARD_CELL_H_

#include "FinFET.h"
#include "Graph.h"
#include <bits/stdc++.h>
using namespace std;

#define PRINT_FINFET_INFO 0

class Standard_Cell{
    public:
        vector<FinFET *> FinFETs;
        size_t Num_FinFETs;
        Graph Pmos_Graph;
        Graph Nmos_Graph;

    public:
        // Constructor & Destructor
        Standard_Cell();
        ~Standard_Cell();

        // Parser
        void Parse_Spice(ifstream &fin);

        // Construct undirected graph
        void Construct_Graph();
        bool Check_Connected_Graph();
};

#endif