#include "Cell.h"

// Constructor & Destructor
Cell::Cell(string Cell_Name):
    Cell_Name(Cell_Name),
    Gain(0),
    State(Not_Lock),
    Side(Left)
{
    Node_In_BucketList = new Node(this);
}

Cell::~Cell(){
    delete Node_In_BucketList;
}

// Setter
void Cell::Set_Gain(int Gain){
    this->Gain = Gain;
}

void Cell::Set_State(Lock_State State){
    this->State = State;
}

void Cell::Set_Side(Partition_Side Side){
    this->Side = Side;
}

void Cell::Add_Net(Net *net){
    this->Net_List.emplace_back(net);
}

// Getter
string Cell::Get_Cell_Name()const{
    return Cell_Name;
}

int Cell::Get_Gain()const{
    return Gain;
}

Lock_State Cell::Get_State()const{
    return State;
}

Partition_Side Cell::Get_Side()const{
    return Side;
}

Node *Cell::Get_Node()const{
    return Node_In_BucketList;
}

Net *Cell::Get_Net(size_t index)const{
    assert(index >= 0 && index < Net_List.size());
    return Net_List[index];
}

size_t Cell::Get_Net_List_Size()const{
    return Net_List.size();
}

// Print cell
ostream &operator<<(ostream &out, const Cell &C){
    out << C.Cell_Name << endl;
    for(size_t i = 0; i < C.Net_List.size(); i++){
        out << "\t" << C.Net_List[i]->Get_Net_Name() << endl;
    }
    return out;
}