#ifndef _NET_H_
#define _NET_H_

#include <bits/stdc++.h>
#include "Util.h"
#include "Cell.h"
using namespace std;

class Cell;

class Net{
    private:
        string Net_Name;
        vector<Cell *>Cell_List;
        int Partition_Size[NPARTS]; // Represent how many cell in Left/Right

    public:
        // Constructor & Destructor
        Net(string);
        ~Net();
        
        // Setter
        void Add_Cell(Cell *);
        void Increase_Partition_Size(Partition_Side);
        void Decrease_Partition_Size(Partition_Side);

        // Getter
        string Get_Net_Name()const;
        Cell *Get_Cell(size_t)const;
        size_t Get_Cell_List_Size()const;
        int Get_Partition_Size(Partition_Side)const;

        // Print net
        friend ostream &operator<<(ostream &, const Net &);

};

#endif