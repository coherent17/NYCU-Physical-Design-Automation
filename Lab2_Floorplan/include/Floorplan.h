#ifndef _FLOORPLAN_H_
#define _FLOORPLAN_H_

#include <bits/stdc++.h>
#include "Block.h"
#include "Util.h"
#include "Fast_Priority_Queue.h"
#include "Random_Number_Generator.h"
using namespace std;

class Floorplan{
    public:
        double Aspect_Ratio_Lower_Bound;
        double Aspect_Ratio_Higher_Bound;
        size_t Num_Blocks;
        vector<shared_ptr<Block>> Blocks;
        unordered_map<string, shared_ptr<Block>> Block_Map;
        vector<size_t> Positive_Sequence;
        vector<size_t> Negative_Sequence;
        size_t Width;
        size_t Height;
        size_t Area;
        Random_Number_Generator *rng;

        // SA Parameter
        double Temperature;

    public:
        // Constructor & Destructor
        Floorplan();
        ~Floorplan();

        // Input & Output
        void Parser(ifstream &fin);
        void Dump(ofstream &fout);

        // Main Algorithm
        void Run();

    private:
        void Init_Sequence();
        size_t Calculate_X_Coordinate();    // return width
        size_t Calculate_Y_Coordinate();    // return height
        void Simulated_Annealing();

        // Three operations for simulated annealing
        bool Operation1();  // Swap 2 modules in Positive Sequence
        bool Operation2();  // Swap 2 modules in Negative Sequence
        bool Operation3();  // Swap 2 modules in both Positive & Negative sequences
        bool Operation4();  // Rotate a block
};

#endif