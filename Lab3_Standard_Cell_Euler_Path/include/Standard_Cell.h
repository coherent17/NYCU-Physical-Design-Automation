#ifndef _STANDARD_CELL_H_
#define _STANDARD_CELL_H_

#include <bits/stdc++.h>
#include "FinFET.h"
#include "Design_Rule.h"
#include "Random_Number_Generator.h"
#include "Util.h"
using namespace std;

class Standard_Cell{
    public:
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
        Random_Number_Generator *rng;

        // SA Parameter
        double Temperature;
        double HPWL;

        // Timing
        chrono::steady_clock::time_point StartTime;

        // Constructor & Destructor
        Standard_Cell();
        ~Standard_Cell();

        // Parser
        void Spice_Parser(ifstream &);
        void Dump(ofstream &);

        // Main Algorithm
        void Run();

    private:
        // Helper Method
        void Init_Poly_Sequence();
        double Calculate_HPWL();
        void Simulated_Annealing();

        //Operations for simulated annealing
        bool SA_Operation1();  // Swap DS in PMOS
        bool SA_Operation2();  // Swap DS in NMOS
        bool SA_Operation3();  // Swap 2 pair in both PMOS & NMOS

        void Remove_Dummy();

        // Final Fine Tune with Greedy
        void Greedy_Optimize();
};

#endif