#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
        unordered_map<string, vector<pair<string, string>>> Adjacency_List;

    public:
        // Constructor & Destructor
        Graph();
        ~Graph();

        // Construct the Graph
        void Add_Edge(const string &, const string &, const string &);

        // Check Euler Graph property
        bool Is_Connected_Graph();
        bool Has_Euler_Path();

        // cout Graph
        friend ostream &operator<<(ostream &, const Graph &);

};

#endif