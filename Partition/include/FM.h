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
        BucketList *BucketLists[NPARTS];
        int Partition_Size[NPARTS];
        int Current_Best_Cut = INT_MAX;
        vector<Partition_Side> Current_Best_Partition;
        chrono::steady_clock::time_point StartTime;

    public:
        // Constructor & Destructor
        FM();
        ~FM();

        void Parser(ifstream &);
        void Dump(ofstream &);

        // Main algorithm
        void Run();

    private:
        void Initialize_Partition();
        void Construct_BucketList();
        Cell *Find_Base_Cell();
        void Update_Neighbor_Gain(Cell *);
        void Update_Base_Cell(Cell *);
        void Unlock_Cell_State();
        int Get_Cut()const;
};

#endif