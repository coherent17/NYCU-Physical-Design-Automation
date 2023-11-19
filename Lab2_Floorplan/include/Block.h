#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <bits/stdc++.h>
using namespace std;

class Block{
    public:
        string Name;
        size_t Width;
        size_t Height;
        size_t X_Coordinate;
        size_t Y_Coordinate;
        bool Is_Rotate;

    public:
        // Constructor & Destructor
        Block(string, size_t, size_t);
        ~Block();

        // Rotate method
        void Rotate();

        friend ostream &operator<<(ostream &, const Block &);
};

#endif