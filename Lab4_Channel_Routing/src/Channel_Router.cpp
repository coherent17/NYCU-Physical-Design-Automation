#include "Channel_Router.h"

// Constructor & Destructor
Channel_Router::Channel_Router():Max_Pin_Number(0){
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
    int Pin_Name;
    stringstream ss1(line);
    while(ss1 >> Pin_Name){
        Top_Boundary.emplace_back(Pin_Name);
        Max_Pin_Number = max(Max_Pin_Number, Pin_Name);
    }

    getline(fin, line);
    stringstream ss2(line);
    while(ss2 >> Pin_Name){
        Bottom_Boundary.emplace_back(Pin_Name);
        Max_Pin_Number = max(Max_Pin_Number, Pin_Name);
    }
    fin.close();


    // Calculate the interval
    assert(Top_Boundary.size() == Bottom_Boundary.size());
    size_t vertical_tracks = Top_Boundary.size();
    cout << vertical_tracks << endl;

    for(size_t i = 0; i < vertical_tracks; i++){
        int current_top_pin = Top_Boundary[i];
        int current_bottom_pin = Bottom_Boundary[i];
        int current_column = i + 1;

        if(current_top_pin != DUMMY_PIN){
            if(Intervals.count(current_top_pin)){
                if(current_column > Intervals[current_top_pin].second){
                    Intervals[current_top_pin].second = current_column;
                }
            }
            else{
                Intervals[current_top_pin] = make_pair(current_column, INT_MIN);
            }
        }

        if(current_bottom_pin != DUMMY_PIN){
            if(Intervals.count(current_bottom_pin)){
                if(current_column > Intervals[current_bottom_pin].second){
                    Intervals[current_bottom_pin].second = current_column;
                }
            }
            else{
                Intervals[current_bottom_pin] = make_pair(current_column, INT_MIN);
            }
        }
    }

    // Sort the intervals

    auto interval_cmp = [](const pair<int, pair<int, int>> &interval1, const pair<int, pair<int, int>> &interval2){
        
        int interval1_start = interval1.second.first;
        int interval1_end = interval1.second.second;
        int interval2_start = interval2.second.first;
        int interval2_end = interval2.second.second;
        
        if(interval1_start < interval2_start) return true;
        else if(interval1_start > interval2_start) return false;
        else{
            return interval1_end < interval2_end;
        }
    };

    for(const auto &pair : Intervals){
        Sorted_Intervals.emplace_back(pair);
    }
    sort(Sorted_Intervals.begin(), Sorted_Intervals.end(), interval_cmp);

    for(const auto &pair : Sorted_Intervals){
        cout << "I" << pair.first << ": " << pair.second.first << " " << pair.second.second << endl;
    }

    // Build the VCG
    Vertical_Constraint_Graph.Init_Graph(Max_Pin_Number);
    for(size_t i = 0; i < Top_Boundary.size(); i++){
        if(Top_Boundary[i] != 0 && Bottom_Boundary[i] != 0){
            Vertical_Constraint_Graph.Add_Edge(Top_Boundary[i], Bottom_Boundary[i]);
        }
    }

    cout << Vertical_Constraint_Graph << endl;
}

void Channel_Router::Dump(ofstream &fout){

    fout.close();
}