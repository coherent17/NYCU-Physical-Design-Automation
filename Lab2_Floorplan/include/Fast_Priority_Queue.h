#ifndef _FAST_PRIORITY_QUEUE_
#define _FAST_PRIORITY_QUEUE_

#include <bits/stdc++.h>
using namespace std;

#define UNSET_KEY -1

// Implement the fast pq in VanEmdeBoas tree
// Ref: [https://www.geeksforgeeks.org/van-emde-boas-tree-set-4-deletion/?ref=lbp]
struct Fast_PQ{
    int Universe_Size;
    int Minimum;
    int Maximum;
    shared_ptr<Fast_PQ> Summary;
    vector<shared_ptr<Fast_PQ>> Clusters;


    // Constructor & Destructor
    Fast_PQ(int size);
    ~Fast_PQ();

    // Helper function
    inline int High(int x);
    inline int Low(int x);
    inline int Generate_Index(int x, int y);

    // Operation
    void Insert(int key);
    void Delete(int key);
    int Predecessor(int key);
    int Successor(int key);
    bool Is_Member(int key);
};

#endif