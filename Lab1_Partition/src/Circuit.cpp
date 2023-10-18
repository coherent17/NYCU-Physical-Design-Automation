#include "Circuit.h"

// Dummy Cell
Cell::Cell():
    Name(""),
    Gain(0),
    State(Not_Lock),
    Side(Left),
    next(nullptr),
    prev(nullptr)
{
    ;
}

// Normal Cell
Cell::Cell(const string &Name):
    Name(Name),
    Gain(0),
    State(Not_Lock),
    Side(Left),
    next(nullptr),
    prev(nullptr)
{
    ;
}

Cell::~Cell(){
    next = nullptr;
    prev = nullptr;
}

// Print Cell
ostream &operator<<(ostream &out, const Cell &C){
    out << "Cell Name: " << C.Name;
    if(PRINT_DETAIL){
        cout << endl;
        for(size_t i = 0; i < C.Nets.size(); i++){
            out << "\t" << C.Nets[i]->Name << endl;
        }
    }
    return out;
}

Net::Net(const string &Name):
    Name(Name)
{
    Partition_Size[Left] = 0;
    Partition_Size[Right] = 0;
}

Net::~Net(){
    ;
}

// Print net
ostream &operator<<(ostream &out, const Net &N){
    out << "Net Name: " << N.Name;
    if(PRINT_DETAIL){
        cout << endl;
        for(size_t i = 0; i < N.Cells.size(); i++){
            out << "\t" << N.Cells[i]->Name << endl;
        }
    }
    return out;
}