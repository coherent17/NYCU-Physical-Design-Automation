#include "Floorplan.h"

// Constructor & Destructor
Floorplan::Floorplan(){
    rng = new Random_Number_Generator();
}

Floorplan::~Floorplan(){
    ;
}

// Parser
void Floorplan::Parser(ifstream &fin){
    fin >> Aspect_Ratio_Lower_Bound >> Aspect_Ratio_Higher_Bound;
    string Block_Name;
    size_t Block_Width;
    size_t Block_Height;
    while(fin >> Block_Name >> Block_Width >> Block_Height){
        shared_ptr<Block> block = make_shared<Block>(Block_Name, Block_Width, Block_Height);
        Block_Map[Block_Name] = block;
        Blocks.emplace_back(block);
    }
    Num_Blocks = Blocks.size();
}

void Floorplan::Dump(ofstream &fout){
    fout.close();
}

void Floorplan::Run(){
    Init_Sequence();

    ofstream fout("out");

    Simulate_Annealing();
    fout << Evaluate_Sequence(EVALUATE_X) << " " << Evaluate_Sequence(EVALUATE_Y) << endl;
    for(size_t i = 0; i < Blocks.size(); i++){
        fout << Blocks[i]->Name << " " << Blocks[i]->X_Coordinate << " " << Blocks[i]->Y_Coordinate << " " << Blocks[i]->X_Coordinate + Blocks[i]->Width << " " << Blocks[i]->Y_Coordinate + Blocks[i]->Height << endl;
    }
}

void Floorplan::Init_Sequence(){
    for(size_t i = 0; i < Blocks.size(); i++){
        Positive_Sequence.emplace_back(i);
        Negative_Sequence.emplace_back(i);
    }
    random_device rd;
    random_shuffle(Positive_Sequence.begin(), Positive_Sequence.end());
    random_shuffle(Negative_Sequence.begin(), Negative_Sequence.end());

    for(size_t i = 0; i < Blocks.size(); i++){
        cout << Positive_Sequence[i] << " ";
    }
    cout << endl;
    for(size_t i = 0; i < Blocks.size(); i++){
        cout << Negative_Sequence[i] << " ";
    }
    cout << endl;
}

/*
Compute X, Y coordinate by longest common subsequence(lcs) in O(nlglgn)
Get X coordinate by evaluate(X, Y)
Get Y coordinate by evaluate(X^R, Y)
Algorithm Eval-Seq(X,Y)
    Initialize_Match_Array MATCH
    Initialize H, insert the inittial index 0
    Initialize BUCKL with BUCKL[0] = 0
    FOR i = 1 TO n DO
        b = X[i]
        p = MATCH[b].y
        insert p to H and BUCKL
        POS[p] = BUCKL[predecessor(p)]
        BUCKL[p] = POS[p] + w(b)
        discard the successors of p from H and BUCKL whose value <= BUCKS[p]
    RETURN BUCKL[index_max]
*/

// expand the function to support both Positive Sequence and Negative Sequence
size_t Floorplan::Evaluate_Sequence(int8_t option){
    // Generate X^R
    if(option & EVALUATE_Y){
        reverse(Positive_Sequence.begin(), Positive_Sequence.end());
    }

    Match *match = new Match[Num_Blocks];
    for(size_t i = 0; i < Num_Blocks; i++){
        match[Positive_Sequence[i]].X = i;
        match[Negative_Sequence[i]].Y = i;
    }

    Fast_PQ *PQ = new Fast_PQ(Blocks.size() + 1);
    PQ->Insert(0);
    vector<int> BUCKL(Blocks.size() + 1, 0);
    for (size_t i = 0; i < Blocks.size(); ++i) {
        int b = Positive_Sequence[i];
        int p = match[b].Y;
        PQ->Insert(p);

        
        if (option & EVALUATE_X) {
            // x coordinates
            int pos = BUCKL[PQ->Predecessor(p)];
            BUCKL[p] = pos + Blocks[b]->Width;
            Blocks[b]->X_Coordinate = pos;
        } 
        else if(option & EVALUATE_Y){
            // y coordinates
            int pos = BUCKL[PQ->Predecessor(p)];
            BUCKL[p] = pos + Blocks[b]->Height;
            Blocks[b]->Y_Coordinate = pos;
        }
        else abort();
        int k = p;
        while (PQ->Successor(k) != -1) {
            k = PQ->Successor(k);
            if (BUCKL[k] <= BUCKL[p])
                PQ->Delete(k);            
        }
    }

    if(option & EVALUATE_Y){
        reverse(Positive_Sequence.begin(), Positive_Sequence.end());
    }
    delete []match;
    return BUCKL[PQ->Maximum];
}

// Two operations for simulated annealing
// Swap 2 modules in only 1 sequences
void Floorplan::Operation1(){
    //cout << "Op1" << endl;
    int index1 = rng->Generate_Random_Integer(Num_Blocks - 1);
    int index2 = rng->Generate_Random_Integer(Num_Blocks - 1);

    assert(index1 < Num_Blocks && index1 >= 0 && index2 < Num_Blocks && index2 >= 0);
    
    int Swap_Which_Sequence = rng->Generate_Random_Integer(1);
    if(Swap_Which_Sequence == 0){
        //cout << "Swap Positive: " << Positive_Sequence[index1] << " " << Positive_Sequence[index2] << endl;
        int old_width = Evaluate_Sequence(EVALUATE_X);
        int old_height = Evaluate_Sequence(EVALUATE_Y);
        swap(Positive_Sequence[index1], Positive_Sequence[index2]);
        int new_width = Evaluate_Sequence(EVALUATE_X);
        int new_height = Evaluate_Sequence(EVALUATE_Y);
        if(new_width * new_height > old_width * old_height){
            swap(Positive_Sequence[index1], Positive_Sequence[index2]);
            Evaluate_Sequence(EVALUATE_X);
            Evaluate_Sequence(EVALUATE_Y);
        }
    }
    else{
        //cout << "Swap Negative: " << Negative_Sequence[index1] << " " << Negative_Sequence[index2] << endl;
        int old_width = Evaluate_Sequence(EVALUATE_X);
        int old_height = Evaluate_Sequence(EVALUATE_Y);
        swap(Negative_Sequence[index1], Negative_Sequence[index2]);
        int new_width = Evaluate_Sequence(EVALUATE_X);
        int new_height = Evaluate_Sequence(EVALUATE_Y);
        if(new_width * new_height > old_width * old_height){
            swap(Negative_Sequence[index1], Negative_Sequence[index2]);
            Evaluate_Sequence(EVALUATE_X);
            Evaluate_Sequence(EVALUATE_Y);
        }
    }
    
}

// Swap 2 modules in both sequences
void Floorplan::Operation2(){
    //cout << "Op2" << endl;
    int index1 = rng->Generate_Random_Integer(Num_Blocks - 1);
    int index2 = rng->Generate_Random_Integer(Num_Blocks - 1);

    int old_width = Evaluate_Sequence(EVALUATE_X);
    int old_height = Evaluate_Sequence(EVALUATE_Y);
    

    int index3 = 0;
    int index4 = 0;
    for(size_t i = 0; i < Num_Blocks; i++){
        if(Negative_Sequence[i] == Positive_Sequence[index1]){
            index3 = i;
            break;
        }
    }

    for(size_t i = 0; i < Num_Blocks; i++){
        if(Negative_Sequence[i] == Positive_Sequence[index2]){
            index4 = i;
            break;
        }
    }
    swap(Positive_Sequence[index1], Positive_Sequence[index2]);
    swap(Negative_Sequence[index3], Negative_Sequence[index4]);
    int new_width = Evaluate_Sequence(EVALUATE_X);
    int new_height = Evaluate_Sequence(EVALUATE_Y);

    if(new_width * new_height > old_width * old_height){
        swap(Positive_Sequence[index1], Positive_Sequence[index2]);
        swap(Negative_Sequence[index3], Negative_Sequence[index4]);
        Evaluate_Sequence(EVALUATE_X);
        Evaluate_Sequence(EVALUATE_Y);
    }
}

void Floorplan::Simulate_Annealing(){
    double Temperature = ANNEALING_TEMPERATURE;
    while(Temperature > TERMINATE_TEMPERATURE){
        for(size_t i = 0; i < STEPS_PER_TEMPERATURE; i++){
            // for(size_t i = 0; i < Num_Blocks; i++){
            //     cout << Positive_Sequence[i] << " ";
            // }
            // cout << endl;
            // for(size_t i = 0; i < Num_Blocks; i++){
            //     cout << Negative_Sequence[i] << " ";
            // }
            // cout << endl; 
            int Number_Operations = 1;
            int n = rng->Generate_Random_Integer(Number_Operations);
            if(n == 0){
                Operation1();
            }
            else{
                Operation2();
            }
            //cout << "Current Area: " << Evaluate_Sequence(EVALUATE_X) << " " << Evaluate_Sequence(EVALUATE_Y) << " " << Evaluate_Sequence(EVALUATE_X) * Evaluate_Sequence(EVALUATE_Y) << endl;
        }
        Temperature *= TEMPERATURE_DECREASING_RATE;
    }
    delete rng;
}