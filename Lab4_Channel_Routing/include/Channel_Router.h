#ifndef _CHANNEL_ROUTER_H_
#define _CHANNEL_ROUTER_H_

#include <bits/stdc++.h>
#include "HCG.h"
using namespace std;

class Channel_Router{
    private:
        vector<string> Top_Boundary;
        vector<string> Bottom_Boundary;
        unordered_map<string, pair<int, int>> Intervals;
        HCG hcg;

    public:
        // Constructor & Destructor
        Channel_Router();
        ~Channel_Router();

        // I/O
        void Parser(ifstream &fin);
        void Dump(ofstream &fout);
};

#endif