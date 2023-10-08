#ifndef _BUCKETLIST_H_
#define _BUCKETLIST_H_

#include "Node.h"
#include "Cell.h"
#include <bits/stdc++.h>
using namespace std;

class BucketList{
    private:
        map<int, Node *> List_Entries;
        int Max_Degree;
        int Current_Max_Gain;

    public:
        //Constructor & Destructor
        BucketList(int);
        ~BucketList();

        //Getter
        int Get_Current_Max_Gain()const;

        //BucketList Operation
        void Insert_Node(Node *, int);
        void Delete_Node(Node *);
        Node *Get_Max_Gain_Node();
        void Clear();

        friend ostream &operator<<(ostream &, BucketList &);
};

#endif