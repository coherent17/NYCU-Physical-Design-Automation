#ifndef _FINFET_H_
#define _FINFET_H_

#include <bits/stdc++.h>
using namespace std;

enum FinFET_Type{
    N_Type,
    P_Type,
    Dummy
};

struct FinFET{
    string Name;
    string Drain;
    string Gate;
    string Source;
    FinFET_Type Type;
    double Width;
    double Length;
    double Gate_X_Coordinate;
    bool Is_Dummy;
    string Left_Diffusion_Pin;
    string Right_Diffusion_Pin;

    // Constructor & Destructor
    FinFET(const string &, const string &, const string &, const string &, FinFET_Type, double, double);
    FinFET();   // For Dummy FinFET
    ~FinFET();

    friend ostream &operator<<(ostream &out, const FinFET &finfet);
};

#endif