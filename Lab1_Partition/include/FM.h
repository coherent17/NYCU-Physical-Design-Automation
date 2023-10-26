#ifndef _FM_H_
#define _FM_H_

#include <bits/stdc++.h>
#include <chrono>
#include "Circuit.h"
#include "BucketList.h"
using namespace std;

class FM{
    private:
        size_t Num_Cells;
        size_t Num_Nets;
        size_t Max_Degree;
        double Balanced_Factor;
        double Lower_Bound;
        double Higher_Bound;
        vector<Cell *> Cell_Array;
        vector<Net *> Net_Array;
        BucketList *BucketLists[NPARTS];
        size_t Partition_Size[NPARTS];
        int Best_Cut;
        int Best_Cut_Pass;
        vector<Partition_Side> Best_Partition;
        chrono::steady_clock::time_point StartTime;
        Partition_Mode Mode;
        bool Is_Corner_Case;

    public:
        // Constructor & Destructor
        FM(Partition_Mode);
        ~FM();

        // I/O
        void Parser(ifstream &);
        void Dump(ofstream &);

        // Main algorithm
        void Run();
        int Get_Best_Cut()const;
        

    private:
        void Initialize_Partition();
        void Construct_BucketList();
        Cell *Find_Base_Cell();
        void Update_Neighbor_Gain(Cell *);
        void Update_Base_Cell(Cell *);
        void Unlock_Cells();
        int Get_Cut()const;
};

#endif