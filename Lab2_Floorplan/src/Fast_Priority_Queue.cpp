#include "Fast_Priority_Queue.h"

// Constructor & Destructor
Fast_PQ::Fast_PQ(int size):
    Universe_Size(size),
    Minimum(UNSET_KEY),
    Maximum(UNSET_KEY)
{
    // Base case
    if(size <= 2){
        Summary = nullptr;
        Clusters = vector<shared_ptr<Fast_PQ>>(0, nullptr);
    }
    else{
        int Num_Clusters = ceil(sqrt(size));
        Summary = make_shared<Fast_PQ>(Num_Clusters);
        Clusters = vector<shared_ptr<Fast_PQ>>(Num_Clusters, nullptr);
        for(int i = 0; i < Num_Clusters; i++){
            Clusters[i] = make_shared<Fast_PQ>(Num_Clusters);
        }
    }
}

// Thanks smart pointer
Fast_PQ::~Fast_PQ(){
    ;
}

inline int Fast_PQ::High(int x){
    return x / int(ceil(sqrt(Universe_Size)));
}

inline int Fast_PQ::Low(int x){
    return x % int(ceil(sqrt(Universe_Size)));
}

inline int Fast_PQ::Generate_Index(int x, int y){
    return x * int(ceil(sqrt(Universe_Size))) + y;
}

void Fast_PQ::Insert(int key){
    // Base case: 
    // No key is present in the tree => set both min and max to the key
    if(Minimum == UNSET_KEY){
        Minimum = key;
        Maximum = key;
    }
    else{
        // Move minimum to its real position through Lazy propagation
        if(key < Minimum){
            swap(Minimum, key);
        }

        // Not base case
        if(Universe_Size > 2){
            int high = High(key);
            int low = Low(key);

            // no key in the cluster, then insert in cluster and summary
            if(Clusters[high]->Minimum == UNSET_KEY){
                Summary->Insert(high);
                Clusters[high]->Minimum = low;
                Clusters[high]->Maximum = low;
            }
            // there are other elements in the tree
            else{
                Clusters[high]->Insert(low);
            }
        }

        if(key > Maximum){
            Maximum = key;
        }
    }
}

void Fast_PQ::Delete(int key){
    // Base case
    if(Maximum == Minimum){
        Minimum = UNSET_KEY;
        Maximum = UNSET_KEY;
        return;
    }

    if(Universe_Size == 2){
        Minimum = (key == 0) ? 1 : 0;
        Maximum = Minimum;
        return;
    }

    if(key == Minimum){
        int first_cluster = Summary->Minimum;
        key = Generate_Index(first_cluster, Clusters[first_cluster]->Minimum);
        Minimum = key;
    }
    Clusters[High(key)]->Delete(Low(key));

    if(Clusters[High(key)]->Minimum == UNSET_KEY){
        Summary->Delete(High(key));
        if(key == Maximum){
            int max_in_summary = Summary->Maximum;
            if(max_in_summary == UNSET_KEY){
                Maximum = Minimum;
            }
            else{
                Maximum = Generate_Index(max_in_summary, Clusters[max_in_summary]->Maximum);
            }
        }
    }
    else if(key == Maximum){
        Maximum = Generate_Index(High(key), Clusters[High(key)]->Maximum);
    }
}

int Fast_PQ::Predecessor(int key){
    // Base Case
    if(Universe_Size == 2){
        return (key == 1 && Minimum == 0) ? 0 : UNSET_KEY;
    }

    // If the key is greater than max
    if(Maximum != UNSET_KEY && key > Maximum) return Maximum;

    // Find the predecessor inside the cluster
    int min_in_cluster = Clusters[High(key)]->Minimum;
    int offset = 0;
    int pred_cluster = 0;

    // Find the predecessor in the cluster
    if(min_in_cluster != UNSET_KEY && Low(key) > min_in_cluster){
        offset = Clusters[High(key)]->Predecessor(Low(key));
        return Generate_Index(High(key), offset);
    }

    // Look for the next cluster with at least 1 key present
    else{
        pred_cluster = Summary->Predecessor(High(key));
        if(pred_cluster == UNSET_KEY){
            return (Minimum != UNSET_KEY && key > Minimum) ? Minimum : UNSET_KEY;
        }
        else{
            offset = Clusters[pred_cluster]->Maximum;
            return Generate_Index(pred_cluster, offset);
        }
    }
}

int Fast_PQ::Successor(int key){
    // Base Case
    if(Universe_Size == 2){
        return (key == 0 && Maximum == 1) ? 1 : UNSET_KEY;
    }

    // If the key is less than min
    if(Minimum != UNSET_KEY && key < Minimum) return Minimum;

    // Find the successor inside the cluster of the key
    int max_in_cluster = Clusters[High(key)]->Maximum;
    int offset = 0;
    int succ_cluster = 0;

    // Find the successor inside the cluster
    if(max_in_cluster != UNSET_KEY && Low(key) < max_in_cluster){
        offset = Clusters[High(key)]->Successor(Low(key));
        return Generate_Index(High(key), offset);
    }
    // Look for the next cluster with at least 1 key present
    else{
        succ_cluster = Summary->Successor(High(key));
        if(succ_cluster == UNSET_KEY) return UNSET_KEY;
        else{
            offset = Clusters[succ_cluster]->Minimum;
            return Generate_Index(succ_cluster, offset);
        }
    }
}

bool Fast_PQ::Is_Member(int key){
    // Not in the range
    if(Universe_Size < key) return false;
    
    // If any traversal of the tree if the min and max == key
    if(Minimum == key || Maximum == key) return true;

    // Not min and max then not presents
    if(Universe_Size == 2) return false;

    // Recursive find over the cluster
    return Clusters[High(key)]->Is_Member(Low(key));
}