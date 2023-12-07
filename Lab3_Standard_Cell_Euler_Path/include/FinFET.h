#ifndef _FINFET_H_
#define _FINFET_H_

#include <bits/stdc++.h>
using namespace std;

enum FinFET_Type{
    N_Type,
    P_Type,
    Dummy_Type
};

// Default layout order from left to right: DGS
// if Swap_Drain_Source, the layout order become SGD
class FinFET{
    public:
        string Name;
        string Drain;
        string Gate;
        string Source;
        FinFET_Type Type;
        double Width;
        double Length;
        bool Swap_Drain_Source;
        bool Is_Dummy;

    public:
        // Constructor & Destructor
        // 1. For normal finfet
        FinFET(const string &, const string &, const string &, const string &, FinFET_Type, double, double);
        // 2. For dummy finfet
        FinFET(bool);
        ~FinFET();

        //Swap the drain and source pin for diffusion sharing
        void Swap_DS();

        // cout FinFET
        friend ostream &operator<<(ostream &out, const FinFET &finfet);
};

#endif