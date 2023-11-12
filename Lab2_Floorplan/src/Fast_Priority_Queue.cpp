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
        return;
    }
    int Num_Clusters = ceil(sqrt(size));
    Summary = make_shared<Fast_PQ>(Num_Clusters);
    Clusters = vector<shared_ptr<Fast_PQ>>(Num_Clusters, nullptr);
    for(int i = 0; i < Num_Clusters; i++){
        Clusters[i] = make_shared<Fast_PQ>(Num_Clusters);
    }
}

// Thanks smart pointer
Fast_PQ::~Fast_PQ(){
    ;
}

// Return cluster numbers where key is present
inline int Fast_PQ::Which_Cluster(int x){
    return x / int(ceil(sqrt(Universe_Size)));
}

// Return position of x in cluster
inline int Fast_PQ::Which_Position(int x){
    return x % int(ceil(sqrt(Universe_Size)));
}

// Return index from the cluster number and position
inline int Fast_PQ::Which_Index(int x, int y){
    return x * int(ceil(sqrt(Universe_Size))) + y;
}

void Fast_PQ::Insert(int key){
    // Base case: 
    // No key is present in the tree => set both min and max to the key
    if(Minimum == UNSET_KEY){
        Minimum = key;
        Maximum = key;
        return;
    }

    // Move minimum to its real position through Lazy propagation
    if(key < Minimum){
        swap(Minimum, key);
    }

    // Not base case
    if(Universe_Size > 2){
        // no key in the cluster, then insert in cluster and summary
        if(Clusters[Which_Cluster(key)]->Minimum == UNSET_KEY){
            Summary->Insert(Which_Cluster(key));
            Clusters[Which_Cluster(key)]->Minimum = Which_Position(key);
            Clusters[Which_Cluster(key)]->Maximum = Which_Position(key);
        }
        // there are other elements in the tree
        else{
            Clusters[Which_Cluster(key)]->Insert(Which_Position(key));
        }
    }

    if(key > Maximum){
        Maximum = key;
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

    // Find next bigger key and assign it as minimum
    if(key == Minimum){
        int first_cluster = Summary->Minimum;
        key = Which_Index(first_cluster, Clusters[first_cluster]->Minimum);
        Minimum = key;
    }
    // Delete the key
    Clusters[Which_Cluster(key)]->Delete(Which_Position(key));

    // If the minimum in the clusters of the key is UNSET
    // Delete it from the summary to eliminate the key completely
    if(Clusters[Which_Cluster(key)]->Minimum == UNSET_KEY){
        Summary->Delete(Which_Cluster(key));
        if(key == Maximum){
            int max_in_summary = Summary->Maximum;
            Maximum = (max_in_summary == UNSET_KEY) ? Minimum : Which_Index(max_in_summary, Clusters[max_in_summary]->Maximum);
        }
    }

    // Find the new maximum key
    else if(key == Maximum){
        Maximum = Which_Index(Which_Cluster(key), Clusters[Which_Cluster(key)]->Maximum);
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
    int min_in_cluster = Clusters[Which_Cluster(key)]->Minimum;
    int offset = 0;
    int pred_cluster = 0;

    // Find the predecessor in the cluster
    if(min_in_cluster != UNSET_KEY && Which_Position(key) > min_in_cluster){
        offset = Clusters[Which_Cluster(key)]->Predecessor(Which_Position(key));
        return Which_Index(Which_Cluster(key), offset);
    }

    // Look for the next cluster with at least 1 key present
    else{
        pred_cluster = Summary->Predecessor(Which_Cluster(key));
        if(pred_cluster == UNSET_KEY){
            return (Minimum != UNSET_KEY && key > Minimum) ? Minimum : UNSET_KEY;
        }
        else{
            offset = Clusters[pred_cluster]->Maximum;
            return Which_Index(pred_cluster, offset);
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
    int max_in_cluster = Clusters[Which_Cluster(key)]->Maximum;
    int offset = 0;
    int succ_cluster = 0;

    // Find the successor inside the cluster
    if(max_in_cluster != UNSET_KEY && Which_Position(key) < max_in_cluster){
        offset = Clusters[Which_Cluster(key)]->Successor(Which_Position(key));
        return Which_Index(Which_Cluster(key), offset);
    }
    // Look for the next cluster with at least 1 key present
    else{
        succ_cluster = Summary->Successor(Which_Cluster(key));
        if(succ_cluster == UNSET_KEY) return UNSET_KEY;
        else{
            offset = Clusters[succ_cluster]->Minimum;
            return Which_Index(succ_cluster, offset);
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
    return Clusters[Which_Cluster(key)]->Is_Member(Which_Position(key));
}