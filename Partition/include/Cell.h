#ifndef _CELL_H_
#define _CELL_H_

#include <bits/stdc++.h>
#include "Util.h"
#include "Node.h"
#include "Net.h"
using namespace std;

class Node;
class Net;

class Cell{
    private:
        string Cell_Name;
        int Gain;
        Lock_State State;           // (Not_Lock/Lock)
        Partition_Side Side;        // (Left/Right)
        Node *Node_In_BucketList;   
        vector<Net *> Net_List;

    public:
        // Constructor & Destructor
        Cell(string);
        ~Cell();

        // Setter
        void Set_Gain(int);
        void Set_State(Lock_State);
        void Set_Side(Partition_Side);
        void Add_Net(Net *);

        // Getter
        string Get_Cell_Name()const;
        int Get_Gain()const;
        Lock_State Get_State()const;
        Partition_Side Get_Side()const;
        Node *Get_Node()const;
        Net *Get_Net(size_t)const;
        size_t Get_Net_List_Size()const;

        // Print cell
        friend ostream &operator<<(ostream &, const Cell &);
};

#endif