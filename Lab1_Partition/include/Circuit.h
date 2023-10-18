#ifndef _CIRCUIT_H_
#define _CIRCUIT_H_

#include <bits/stdc++.h>
#include "Util.h"
using namespace std;

struct Net;

struct Cell{
    string Name;
    int Gain;
    Lock_State State;
    Partition_Side Side;
    vector<Net *> Nets;
    Cell *next;
    Cell *prev;

    // Constructor & Destructor
    Cell();
    Cell(const string &);
    ~Cell();

    // Print Cell
    friend ostream &operator<<(ostream &, const Cell &);
};

struct Net{
    string Name;
    vector<Cell *> Cells;
    size_t Partition_Size[NPARTS];

    // Constructor & Destructor
    Net(const string &);
    ~Net();

    // Print Net
    friend ostream &operator<<(ostream &, const Net &);
};

#endif