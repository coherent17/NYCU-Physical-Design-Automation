#ifndef _FM_H_
#define _FM_H_

#include "Cell.h"
#include "Net.h"
#include "BucketList.h"
#include "Util.h"
#include <bits/stdc++.h>
#include <chrono>
using namespace std;

class FM{
    private:
        int Num_Cells;
        int Num_Nets;
        int Max_Degree;
        double Balanced_Factor;
        double Lower_Partition_Bound;
        double Higher_Partition_Bound;
        vector<Cell *> Cell_Array;
        vector<Net *> Net_Array;
        int Partition_Size[NPARTS];
        

    public:
        // Constructor & Destructor
        FM();
        ~FM();

        void Parser(ifstream &);
};

#endif