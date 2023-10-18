#ifndef _BUCKETLIST_H_
#define _BUCKETLIST_H_

#include <bits/stdc++.h>
#include "Circuit.h"
using namespace std;

struct BucketList{
    unordered_map<int, Cell *> List_Entries;
    int Max_Degree;
    int Current_Max_Gain;

    //Constructor & Destructor
    BucketList(int);
    ~BucketList();

    // BucketList Operation
    void Insert(int, Cell *);
    void Delete(Cell *);
    Cell *Get_Max_Gain_Cell();
    void Clear();
    
    // Print BucketList
    friend ostream &operator<<(ostream &, BucketList &);

};

#endif