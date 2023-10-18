#include "BucketList.h"

//Constructor & Destructor
BucketList::BucketList(int Max_Degree):
    Max_Degree(Max_Degree),
    Current_Max_Gain(-Max_Degree)
{
    for(int i = -Max_Degree; i <= Max_Degree; i++){
        // Dummy head node
        List_Entries[i] = new Cell();
    }
}

BucketList::~BucketList(){
    for(int i = -Max_Degree; i <= Max_Degree; i++){
        // Only delete dummy cell
        // Rest of the cell will free in FM class
        delete List_Entries[i];
    }
}

// BucketList Operation
void BucketList::Insert(int Gain, Cell *cell){
    assert(cell != nullptr);
    assert(Gain <= Max_Degree && Gain >= -Max_Degree);
    Current_Max_Gain = Current_Max_Gain > Gain ? Current_Max_Gain : Gain;
    cell->prev = List_Entries[Gain];
    cell->next = List_Entries[Gain]->next;
    if(List_Entries[Gain]->next != nullptr){
        List_Entries[Gain]->next->prev = cell;
    }
    List_Entries[Gain]->next = cell;
}

void BucketList::Delete(Cell *cell){
    assert(cell != nullptr);
    cell->prev->next = cell->next;
    if(cell->next != nullptr){
        cell->next->prev = cell->prev;
    }

    // Update Current_Max_Gain
    for(int i = Max_Degree; i >= -Max_Degree; i--){
        if(List_Entries[i]->next != nullptr){
            Current_Max_Gain = i;
            return;
        }
    }
    Current_Max_Gain = -Max_Degree;
}

Cell *BucketList::Get_Max_Gain_Cell(){
    //if the whole bucketlist are empty
    if(List_Entries[Current_Max_Gain]->next == nullptr){
        return nullptr;
    }
    return List_Entries[Current_Max_Gain]->next;
}

void BucketList::Clear(){
    for(int i = -Max_Degree; i <= Max_Degree; i++){
        List_Entries[i]->next = nullptr;
    }
}


// Print BucketList
ostream &operator<<(ostream &out, BucketList & B){
    cout << "Current Max Gain: " << B.Current_Max_Gain << endl;
    for(int i = B.Max_Degree; i >= -B.Max_Degree; i--){
        out << setw(2) << i << ": ";
        Cell *c = B.List_Entries[i]->next;
        while(c != nullptr){
            out << c->Name;
            if(c->next != nullptr){
                out << " -> ";
            }
            c = c->next;
        }
        out << endl;
    }
    out << endl;
    return out;
}