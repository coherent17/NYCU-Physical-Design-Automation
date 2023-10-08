#include "FM.h"

FM::FM():
    Num_Cells(0),
    Num_Nets(0),
    Max_Degree(0),
    Balanced_Factor(0),
    Lower_Partition_Bound(0),
    Higher_Partition_Bound(0)
{
    Partition_Size[Left] = 0;
    Partition_Size[Right] = 0;

}

FM::~FM(){
    for(size_t i = 0; i < Cell_Array.size(); i++){
        delete Cell_Array[i];
    }
    for(size_t i = 0; i < Net_Array.size(); i++){
        delete Net_Array[i];
    }
}

void FM::Parser(ifstream &fin){
    // Parse Balanced Factor
    string line;
    getline(fin, line);
    stringstream s(line);
    s >> Balanced_Factor;

    // Construct Net Array
    // A hash table map cell name to the pointer to the cell object
    unordered_map<string, Cell *> Cell_Map;
    while(getline(fin, line)){
        // NET <Net Name> [<Cell Name>]+ ;
        stringstream ss(line);
        string _, Net_Name;
        ss >> _ >> Net_Name;
        Net *net = new Net(Net_Name);
        while(ss){
            string Cell_Name;
            ss >> Cell_Name;
            if(Cell_Name == ";") break;

            // Check if the Cell exists in the Cell_Map
            if (Cell_Map.find(Cell_Name) == Cell_Map.end()) {
                Cell_Map[Cell_Name] = new Cell(Cell_Name);
            }
            Cell_Map[Cell_Name]->Add_Net(net);
            net->Add_Cell(Cell_Map[Cell_Name]);
        }
        Net_Array.emplace_back(net);
    }

    // Construct Cell Array
    for(const auto& pair : Cell_Map){
        Cell_Array.emplace_back(pair.second);
    }
    fin.close();


    for(size_t i = 0; i < Cell_Array.size(); i++){
        cout << *Cell_Array[i] << endl;
    }

    cout << "########################################" << endl;
    for(size_t i = 0; i < Net_Array.size(); i++){
        cout << *Net_Array[i] << endl;
    }
}