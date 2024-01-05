#ifndef _CHANNEL_ROUTER_H_
#define _CHANNEL_ROUTER_H_

#include <bits/stdc++.h>
#include "Util.h"
using namespace std;

class Channel_Router{
    private:
        int Max_Pin_Number;
        vector<int> Top_Boundary;
        vector<int> Bottom_Boundary;
        vector<pair<int, int>> Boundary;
        unordered_map<int, pair<int, int>> Intervals;

    public:
        // Constructor & Destructor
        Channel_Router();
        ~Channel_Router();

        // I/O
        void Parser(ifstream &fin);
        void Dump(ofstream &fout);
};

#endif