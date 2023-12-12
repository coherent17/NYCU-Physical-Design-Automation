#ifndef _STANDARD_CELL_H_
#define _STANDARD_CELL_H_

#include <bits/stdc++.h>
#include "FinFET.h"
#include "Design_Rule.h"
using namespace std;

struct Standard_Cell{
    size_t Num_FinFETs;
    vector<FinFET *> FinFETs;
    vector<FinFET *> N_FinFETs;
    vector<FinFET *> P_FinFETs;
    set<string> Pin_Names;  // Store the drain & source name
    unordered_map<string, vector<FinFET *>> FinFET_Pin_Map;
    unordered_map<string, vector<FinFET *>> N_FinFET_Poly_Map;
    unordered_map<string, vector<FinFET *>> P_FinFET_Poly_Map;
    list<pair<FinFET *, FinFET *>> Layout;
    double P_Active_Width;
    double N_Active_Width;
    double P_Active_Center_Height;
    double N_Active_Center_Height;


    // Constructor & Destructor
    Standard_Cell();
    ~Standard_Cell();

    // Parser
    void Spice_Parser(ifstream &);
    void Dump(ofstream &);

    // Main Algorithm
    void Run();

    // Helper Method
    void Init_Poly_Sequence();
    double Calculate_HPWL();
};

#endif