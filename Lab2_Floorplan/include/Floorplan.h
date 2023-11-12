#ifndef _FLOORPLAN_H_
#define _FLOORPLAN_H_

#define EVALUATE_X 0b00000001
#define EVALUATE_Y 0b00000010

#include <bits/stdc++.h>
#include "Block.h"
#include "Util.h"
#include "Fast_Priority_Queue.h"
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

    public:
        // Constructor & Destructor
        Floorplan();
        ~Floorplan();

        // Parser
        void Parser(ifstream &fin);
        void Dump(ofstream &fout);

        // Main Algorithm
        void Run();

    private:
        void Init_Sequence();
        size_t Evaluate_Sequence(int8_t option);
        void Simulate_Annealing();
};

#endif