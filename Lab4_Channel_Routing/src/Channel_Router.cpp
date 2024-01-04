#include "Channel_Router.h"

// Constructor & Destructor
Channel_Router::Channel_Router(){
    ;
}

Channel_Router::~Channel_Router(){
    ;
}

// I/O
void Channel_Router::Parser(ifstream &fin){
    string line;
    while(getline(fin, line)){
        if(line[0] != 'T' && line[0] != 'B'){
            break;
        }
    }
    stringstream ss1(line);
    while(ss1){
        string Pin_Name;
        ss1 >> Pin_Name;
        Top_Boundary.emplace_back(Pin_Name);
    }

    getline(fin, line);
    stringstream ss2(line);
        while(ss2){
        string Pin_Name;
        ss2 >> Pin_Name;
        Bottom_Boundary.emplace_back(Pin_Name);
    }
    fin.close();

    // Calculate the interval
    assert(Top_Boundary.size() == Bottom_Boundary.size());
    for(size_t i = 0; i < Top_Boundary.size(); i++){
        if(Top_Boundary[i] == "0") continue;
        if(Intervals.find(Top_Boundary[i]) == Intervals.end()){
            Intervals[Top_Boundary[i]] = make_pair(INT_MAX, INT_MIN);
        }
    }

    for(size_t i = 0; i < Bottom_Boundary.size(); i++){
        if(Bottom_Boundary[i] == "0") continue;
        if(Intervals.find(Bottom_Boundary[i]) == Intervals.end()){
            Intervals[Bottom_Boundary[i]] = make_pair(INT_MAX, INT_MIN);
        }
    }

    for(size_t i = 0; i < Top_Boundary.size(); i++){
        if(Top_Boundary[i] == "0") continue;
        Intervals[Top_Boundary[i]].first = min(int(i + 1), Intervals[Top_Boundary[i]].first);
        Intervals[Top_Boundary[i]].second = max(int(i + 1), Intervals[Top_Boundary[i]].second);
    }

    for(size_t i = 0; i < Bottom_Boundary.size(); i++){
        if(Bottom_Boundary[i] == "0") continue;
        Intervals[Bottom_Boundary[i]].first = min(int(i + 1), Intervals[Bottom_Boundary[i]].first);
        Intervals[Bottom_Boundary[i]].second = max(int(i + 1), Intervals[Bottom_Boundary[i]].second);
    }

    for (const auto &entry : Intervals) {
        cout << entry.first << ": " << entry.second.first << " " << entry.second.second << endl;
    }
}

void Channel_Router::Dump(ofstream &fout){

    fout.close();
}