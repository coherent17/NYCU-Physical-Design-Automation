#ifndef _CHANNEL_ROUTER_H_
#define _CHANNEL_ROUTER_H_

#include <bits/stdc++.h>
#include "Graph.h"
#include "Util.h"
using namespace std;

class Channel_Router{
    private:
        int Max_Pin_Number;
        vector<int> Top_Boundary;
        vector<int> Bottom_Boundary;
        vector<pair<int, int>> Boundary;
        unordered_map<int, pair<int, int>> Intervals;
        vector<pair<int, pair<int, int>>> Sorted_Intervals;
        Graph Vertical_Constraint_Graph;
        vector<set<int>> Routing_Track;

    public:
        // Constructor & Destructor
        Channel_Router();
        ~Channel_Router();

        // Main Algorithm
        void Run();

        // I/O
        void Parser(ifstream &fin);
        void Dump(ofstream &fout);
};

#endif