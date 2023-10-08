#include "Net.h"

// Constructor & Destructor
Net::Net(string Net_Name)
    :Net_Name(Net_Name)
{
    Partition_Size[Left] = 0;
    Partition_Size[Right] = 0;
}

Net::~Net(){
    ;
}

// Setter
void Net::Add_Cell(Cell *cell){
    Cell_List.emplace_back(cell);
}

void Net::Increase_Partition_Size(Partition_Side Side){
    assert(Side == Left || Side == Right);
    Partition_Size[Side]++;
}

void Net::Decrease_Partition_Size(Partition_Side Side){
    assert(Side == Left || Side == Right);
    Partition_Size[Side]--;
}

// Getter
string Net::Get_Net_Name()const{
    return Net_Name;
}

Cell *Net::Get_Cell(size_t index)const{
    assert(index >= 0 && index < Cell_List.size());
    return Cell_List[index];
}

size_t Net::Get_Cell_List_Size()const{
    return Cell_List.size();
}

int Net::Get_Partition_Size(Partition_Side Side)const{
    return Partition_Size[Side];
}

// Print net
ostream &operator<<(ostream &out, const Net &N){
    out << "Net Name: " << N.Net_Name << endl;
    for(size_t i = 0; i < N.Cell_List.size(); i++){
        out << "\t" << N.Cell_List[i]->Get_Cell_Name() << endl;
    }
    return out;
}