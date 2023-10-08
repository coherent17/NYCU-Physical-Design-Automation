#include "BucketList.h"

//Constructor & Destructor
BucketList::BucketList(int Max_Degree){
    this->Max_Degree = Max_Degree;
    this->Current_Max_Gain = -Max_Degree;
    for(int i = -Max_Degree; i <= Max_Degree; i++){
        // Insert the Dummy Head Node
        Node *Dummy_Head = new Node();
        List_Entries[i] = Dummy_Head;
    }
}

BucketList::~BucketList(){
    for(int i = -Max_Degree; i <= Max_Degree; i++){
        // Only delete the Dummy Head Node
        // Rest of the Node will be delete in Cell class destructor
        delete List_Entries[i];
    }
}

//Getter
int BucketList::Get_Current_Max_Gain()const{
    return Current_Max_Gain;
}

//BucketList Operation
void BucketList::Insert_Node(Node *Node_To_Insert, int Gain){
    Current_Max_Gain = Current_Max_Gain > Gain ? Current_Max_Gain : Gain;
    Node_To_Insert->prev = List_Entries[Gain];
    Node_To_Insert->next = List_Entries[Gain]->next;
    if(List_Entries[Gain]->next != nullptr){
        List_Entries[Gain]->next->prev = Node_To_Insert;
    }
    List_Entries[Gain]->next = Node_To_Insert;
}

void BucketList::Delete_Node(Node *Node_To_Delete){
    if(Node_To_Delete == nullptr || Node_To_Delete->cell == nullptr){
        return;
    }
    Node_To_Delete->prev->next = Node_To_Delete->next;
    if(Node_To_Delete->next != nullptr){
        Node_To_Delete->next->prev = Node_To_Delete->prev;
    }

    // Update Current_Max_Gain if needed
    for(int i = Max_Degree; i >= -Max_Degree; i--){
        if(List_Entries[i]->next != nullptr){
            Current_Max_Gain = i;
            return;
        }
    }
    Current_Max_Gain = -Max_Degree;
}

Node *BucketList::Get_Max_Gain_Node(){
    //if the whole bucketlist are empty
    if(List_Entries[Current_Max_Gain]->next == nullptr){
        return nullptr;
    }
    assert(List_Entries[Current_Max_Gain]->next != nullptr);
    return List_Entries[Current_Max_Gain]->next;
}

void BucketList::Clear(){
    for(int i = Max_Degree; i >= -Max_Degree; i--){
        List_Entries[i]->next = nullptr;
    }
}

ostream &operator<<(ostream &out, BucketList &B){
    cout << "Current Max Gain: " << B.Current_Max_Gain << endl;
    for(int i = B.Max_Degree; i >= -B.Max_Degree; i--){
        out << setw(2) << i << ": ";
        Node *current = B.List_Entries[i]->next;
        while(current != nullptr){
            out << current->cell->Get_Cell_Name();
            if(current->next != nullptr){
                out << " -> ";
            }
            current = current->next;
        }
        out << endl;
    }
    out << endl;
    return out;
}