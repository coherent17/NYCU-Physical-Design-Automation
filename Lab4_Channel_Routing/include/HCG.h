#ifndef _HCG_H_
#define _HCG_H_

#include <bits/stdc++.h>
using namespace std;

class HCG{
    private:
        unordered_map<string, vector<string>> Undirected_Graph;

    public:
        // Constructor & Destructor
        HCG();
        ~HCG();

        // Member Function
        void Add_Vertex(const string &Pin_Name);
        void Add_Edge(const string &Pin_Name1, const string &Pin_Name2);
        
        // Print HCG
        friend ostream& operator<<(ostream &out, const HCG &hcg);
};

#endif