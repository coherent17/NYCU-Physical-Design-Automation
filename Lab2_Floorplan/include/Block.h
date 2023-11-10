#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <bits/stdc++.h>
using namespace std;

class Block{
    public:
        string Name;
        size_t Width;
        size_t Height;

    public:
        // Constructor & Destructor
        Block(string, size_t, size_t);
        ~Block();
};

#endif