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

void Graph::Delete_Edge(int src, int dest){
    auto it = Adjacency_List.find(src);
    assert(it != Adjacency_List.end() && "Key not found");
    auto neighborIt = it->second.find(dest);
    assert(neighborIt != it->second.end() && "Dest pin not found");
    it->second.erase(neighborIt);
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