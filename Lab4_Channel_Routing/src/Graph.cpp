#include "Graph.h"

// Constructor & Destructor
Graph::Graph(){
    ;
}

Graph::~Graph(){
    ;
}

// Graph Operation
void Graph::Init_Graph(int n){
    for(int i = 1; i <= n; i++){
        Adjacency_List[i] = set<int>();
    }
}

void Graph::Add_Edge(int src, int dest){
    Adjacency_List[src].insert(dest);
}

void Graph::Delete_Node(int node){
    for (auto& pair : Adjacency_List) {
        pair.second.erase(node);
    }
    Adjacency_List.erase(node);
}

size_t Graph::Get_Node_InDegree(int node){
    return Adjacency_List[node].size();
}

// Print Adjacency List
ostream &operator<<(ostream &out, const Graph &graph){
    for(const auto &pair : graph.Adjacency_List){
        out << pair.first << ": ";
        for(const auto &neighbor : pair.second){
            out << neighbor << " ";
        }
        out << endl;
    }
    out << endl;
    return out;
}