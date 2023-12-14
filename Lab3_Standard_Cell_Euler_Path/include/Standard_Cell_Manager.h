#ifndef _STANDARD_CELL_MANAGER_H_
#define _STANDARD_CELL_MANAGER_H_

#include "Standard_Cell.h"
#include <bits/stdc++.h>
using namespace std;

class Standard_Cell_Manager{
    private:
        const char *input_filename;
        const char *output_filename;
        ifstream fin1;
        ifstream fin2;
        ifstream fin3;
        ifstream fin4;
        ifstream fin5;
        ifstream fin6;
        ifstream fin7;
        ifstream fin8;
        ifstream fin9;
        ifstream fin10;
        ofstream fout;

    public:
        // Constructor & Destructor
        Standard_Cell_Manager(const char *, const char *);
        ~Standard_Cell_Manager();

        // Run thread and wait for all thread finish
        void Run_Thread();

};

#endif