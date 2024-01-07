#ifndef _GRAPH_H_
#define _GTAPH_H_

#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:
        unordered_map<int, set<int>> Adjacency_List;

    public:
        // Constructor & Destructor
        Graph();
        ~Graph();

        // Graph Operation
        void Init_Graph(int n);
        void Add_Edge(int src, int dest);
        void Delete_Node(int node);
        size_t Get_Node_InDegree(int node);

        // Print Adjacency List
        friend ostream &operator<<(ostream &out, const Graph &graph);

};

#endif