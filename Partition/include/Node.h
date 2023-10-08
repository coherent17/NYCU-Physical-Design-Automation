#ifndef _NODE_H_
#define _NODE_H_

#include "Cell.h"
#include <bits/stdc++.h>
using namespace std;

class Cell;

// The doubly linkedlist node class that used in the bucketlist data structure
class Node{
    public:
        Cell *cell;
        Node *next;
        Node *prev;

    public:
        Node();
        Node(Cell *);
        ~Node();

};

#endif