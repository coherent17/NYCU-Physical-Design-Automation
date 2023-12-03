#include "Graph.h"

// Constructor & Destructor
Graph::Graph(){
    ;
}

Graph::~Graph(){
    ;
}

// Construct the Graph
void Graph::Add_Edge(const string &u, const string &v, const string &Edge_Name){
    Adjacency_List[u].emplace_back(make_pair(v, Edge_Name));
    Adjacency_List[v].emplace_back(make_pair(u, Edge_Name));
}

// Check Euler Graph property
bool Graph::Is_Connected_Graph(){
    set<string> visited;
    queue<string> q;
    q.push(Adjacency_List.begin()->first);

    while(!q.empty()){
        string current = q.front();
        q.pop();
        visited.insert(current);

        for(const auto &neighbor : Adjacency_List[current]){
            if(visited.find(neighbor.first) == visited.end()){
                q.push(neighbor.first);
            }
        }
    }

    return (visited.size() == Adjacency_List.size());
}

bool Graph::Has_Euler_Path(){
    // Check if the graph is connected
    if(!Is_Connected_Graph()){
        return false;
    }

    // Check node degree
    int Num_Odd_Degree = 0;
    for(const auto &entry : Adjacency_List){
        if(entry.second.size() % 2 != 0){
            Num_Odd_Degree++;
        }
    }

    return (Num_Odd_Degree == 0) || (Num_Odd_Degree == 2);
}

ostream &operator<<(ostream &out, const Graph &graph){
    for(const auto &entry : graph.Adjacency_List){
        out << entry.first << " -> ";
        for(const auto &neighbor : entry.second){
            out << "(" << neighbor.first << ", " << neighbor.second << ")";
        }
        out << endl;
    }
    return out;
}