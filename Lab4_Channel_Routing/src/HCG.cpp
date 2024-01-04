#include "HCG.h"

// Constructor & Destructor
HCG::HCG(){
    ;
}

HCG::~HCG(){
    ;
}

// Member Function
void HCG::Add_Vertex(const string &Pin_Name){
    if(Undirected_Graph.find(Pin_Name) == Undirected_Graph.end()){
        Undirected_Graph[Pin_Name] = vector<string>();
    }
}

void HCG::Add_Edge(const string &Pin_Name1, const string &Pin_Name2){
    Add_Vertex(Pin_Name1);
    Add_Vertex(Pin_Name2);

    Undirected_Graph[Pin_Name1].emplace_back(Pin_Name2);
    Undirected_Graph[Pin_Name2].emplace_back(Pin_Name2);
}

// Print HCG
ostream& operator<<(ostream &out, const HCG &hcg){
    for(const auto &entry : hcg.Undirected_Graph){
        cout << "Pin Name " << entry.first << ": ";
        for(const string &neighbor : entry.second){
            cout << neighbor << " ";
        }
        cout << endl;
    }
    return out;
}