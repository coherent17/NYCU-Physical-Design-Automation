#ifndef _FINFET_H_
#define _FINFET_H_

#include <bits/stdc++.h>
using namespace std;

enum FinFET_Type{
    N_Type,
    P_Type
};

class FinFET{
    public:
        string Name;
        FinFET_Type Type;
        string Drain;
        string Gate;
        string Source;
        double Width;
        double Length;

    public:
        // Constructor & Destructor
        FinFET(const string &, FinFET_Type, const string &, const string &, const string &, double, double);
        ~FinFET();

        // cout FinFET
        friend ostream &operator<<(ostream &out, const FinFET &finfet);
};

#endif