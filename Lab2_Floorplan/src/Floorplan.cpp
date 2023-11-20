#include "Floorplan.h"

// Constructor & Destructor
Floorplan::Floorplan():
    Aspect_Ratio_Lower_Bound(0),
    Aspect_Ratio_Higher_Bound(0),
    Num_Blocks(0),
    Width(0),
    Height(0),
    Temperature(ANNEALING_TEMPERATURE)
{
    rng = new Random_Number_Generator();
}

Floorplan::~Floorplan(){
    delete rng;
}

// Input & Output
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
    Width = Calculate_X_Coordinate();
    Height = Calculate_Y_Coordinate();
    Area = Width * Height;
    fout << "A = " << Width * Height << endl;
    fout << "R = " << double(Width) / double(Height) << endl;
    cout << "W/H" << Width << " " << Height << endl;
    for(size_t i = 0; i < Blocks.size(); i++){
        fout << Blocks[i]->Name << " " << Blocks[i]->X_Coordinate << " " << Blocks[i]->Y_Coordinate;
        if(Blocks[i]->Is_Rotate){
            fout <<  " R";
        }
        fout << endl;
    }
    fout.close();
}

void Floorplan::Run(){
    Init_Sequence();
    Simulated_Annealing();
   
    ofstream fout("out");

    // output for plot the module
    fout << Calculate_X_Coordinate() << " " <<  Calculate_Y_Coordinate() << endl;
    for(size_t i = 0; i < Blocks.size(); i++){
        fout << Blocks[i]->Name << " " << Blocks[i]->X_Coordinate << " " << Blocks[i]->Y_Coordinate << " " << Blocks[i]->X_Coordinate + Blocks[i]->Width << " " << Blocks[i]->Y_Coordinate + Blocks[i]->Height << endl;
    }
}

void Floorplan::Init_Sequence(){
    for(size_t i = 0; i < Blocks.size(); i++){
        Positive_Sequence.emplace_back(i);
        Negative_Sequence.emplace_back(i);
    }
    
    // Change to srand(time(NULL)) before released
    srand(123);
    double R;
    do{
        random_shuffle(Positive_Sequence.begin(), Positive_Sequence.end());
        random_shuffle(Negative_Sequence.begin(), Negative_Sequence.end());
        Width = Calculate_X_Coordinate();
        Height = Calculate_Y_Coordinate();
        Area = Width * Height;
        R = double(Width) / double(Height);
        cout << R << endl;
    }while(R > Aspect_Ratio_Higher_Bound || R < Aspect_Ratio_Lower_Bound);
    

    if(PRINT_INITIAL_SEQUENCE_PAIR){
        cout << "Positive Sequence: ";
        for(size_t i = 0; i < Blocks.size(); i++){
            cout << Positive_Sequence[i] << " ";
        }
        cout << endl << "Negative Sequence: ";
        for(size_t i = 0; i < Blocks.size(); i++){
            cout << Negative_Sequence[i] << " ";
        }
        cout << endl;
    }
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


// Evaluate X to return the width
size_t Floorplan::Calculate_X_Coordinate(){
    vector<Match> match(Num_Blocks);
    vector<int> BUCKL(Num_Blocks + 1, 0);
    for(size_t i = 0; i < Num_Blocks; i++){
        match[Positive_Sequence[i]].X = i;
        match[Negative_Sequence[i]].Y = i;
    }
    Fast_PQ PQ(Num_Blocks + 1);
    PQ.Insert(0);
    for (size_t i = 0; i < Num_Blocks; ++i) {
        int b = Positive_Sequence[i];
        int p = match[b].Y;
        PQ.Insert(p);
        int pos = BUCKL[PQ.Predecessor(p)];
        BUCKL[p] = pos + Blocks[b]->Width;
        Blocks[b]->X_Coordinate = pos;
        for(int k = PQ.Successor(p); k != UNSET_KEY; k = PQ.Successor(k)){
            if (BUCKL[k] <= BUCKL[p]) PQ.Delete(k);  
        }
    }
    return BUCKL[PQ.Maximum];
}

// Evaluate Y to return the height
size_t Floorplan::Calculate_Y_Coordinate(){
    // Generate X^R
    reverse(Positive_Sequence.begin(), Positive_Sequence.end());

    vector<Match> match(Num_Blocks);
    vector<int> BUCKL(Num_Blocks + 1, 0);
    for(size_t i = 0; i < Num_Blocks; i++){
        match[Positive_Sequence[i]].X = i;
        match[Negative_Sequence[i]].Y = i;
    }
    Fast_PQ PQ(Num_Blocks + 1);
    PQ.Insert(0);
    for (size_t i = 0; i < Num_Blocks; ++i) {
        int b = Positive_Sequence[i];
        int p = match[b].Y;
        PQ.Insert(p);
        int pos = BUCKL[PQ.Predecessor(p)];
        BUCKL[p] = pos + Blocks[b]->Height;
        Blocks[b]->Y_Coordinate = pos;
        for(int k = PQ.Successor(p); k != UNSET_KEY; k = PQ.Successor(k)){
            if (BUCKL[k] <= BUCKL[p]) PQ.Delete(k);  
        }
    }
    reverse(Positive_Sequence.begin(), Positive_Sequence.end());
    return BUCKL[PQ.Maximum];
}

void Floorplan::Simulated_Annealing(){
    bool Convergence_Flag = false;
    size_t Previous_Area = Area;
    int Num_Consecutive_Temperature_Unchanged = 0;
    while(Temperature > TERMINATE_TEMPERATURE && !Convergence_Flag){
        for(size_t i = 0; i < STEPS_PER_TEMPERATURE; i++){
            int Which_Operation = rng->Generate_Random_Integer(2);
            assert(Which_Operation <= 3 && Which_Operation >= 0);
            bool SA_Result;
            switch(Which_Operation){
                case OPERATION1:
                    SA_Result = Operation1();
                    break;
                case OPERATION2:
                    SA_Result = Operation2();
                    break;
                case OPERATION3:
                    SA_Result = Operation3();
                    break;
                case OPERATION4:
                    //SA_Result = Operation4();
                    break;
                default:
                    abort();
            }
            cout << SA_Result << endl;
            cout << "Area: " << Area << endl;
        }
        if(Area == Previous_Area){
            Num_Consecutive_Temperature_Unchanged++;
            if(Num_Consecutive_Temperature_Unchanged >= MAX_CONSECUTIVE_TEMPERATURN_UNCHANGE){
                Convergence_Flag = true;
            }
        }
        else{
            Num_Consecutive_Temperature_Unchanged = 0;
            Previous_Area = Area;
        }
        Temperature = (Temperature > CRITICAL_TEMPERATURE) ? Temperature * TEMPERATURE_DECREASING_FAST_RATE : Temperature * TEMPERATURE_DECREASING_SLOW_RATE;
    }
}

// Four operations for simulated annealing
// Swap 2 modules in Positive Sequence
bool Floorplan::Operation1(){
    cout << "OP1" << endl;
    size_t index1 = rng->Generate_Random_Integer(Num_Blocks - 1);
    size_t index2 = rng->Generate_Random_Integer(Num_Blocks - 1);
    assert(index1 < Num_Blocks && index1 >= 0);
    assert(index2 < Num_Blocks && index2 >= 0);

    size_t New_Width = 0;
    size_t New_Height = 0;
    double New_Aspect_Ratio;
    size_t New_Area = 0;

    swap(Positive_Sequence[index1], Positive_Sequence[index2]);
    New_Width = Calculate_X_Coordinate();
    New_Height = Calculate_Y_Coordinate();
    New_Area = New_Width * New_Height;
    New_Aspect_Ratio = double(New_Width) / double(New_Height);

    // Illegal Move
    if(New_Aspect_Ratio > Aspect_Ratio_Higher_Bound || New_Aspect_Ratio < Aspect_Ratio_Lower_Bound){
        swap(Positive_Sequence[index1], Positive_Sequence[index2]);
        Width = Calculate_X_Coordinate();
        Height = Calculate_Y_Coordinate();
        Area = Width * Height;
        return REJECT;
    }

    // Better Move
    if(New_Area < Area){
        Width = New_Width;
        Height = New_Height;
        Area = New_Area;
        return ACCEPT;
    }

    // Worse but legal move
    else{
        double Delta_Area = New_Area - Area;
        double r = rng->Generate_Random_Float();

        // Accept
        if(r < exp(-1 * Delta_Area / Temperature)){
            Width = New_Width;
            Height = New_Height;
            Area = New_Area;
            return ACCEPT;
        }

        // Reject
        else{
            swap(Positive_Sequence[index1], Positive_Sequence[index2]);
            Width = Calculate_X_Coordinate();
            Height = Calculate_Y_Coordinate();
            Area = Width * Height;
            return REJECT;
        }
    }
}

// Swap 2 modules in Negative Sequence
bool Floorplan::Operation2(){
    cout << "OP2" << endl;
    size_t index1 = rng->Generate_Random_Integer(Num_Blocks - 1);
    size_t index2 = rng->Generate_Random_Integer(Num_Blocks - 1);
    assert(index1 < Num_Blocks && index1 >= 0);
    assert(index2 < Num_Blocks && index2 >= 0);

    size_t New_Width = 0;
    size_t New_Height = 0;
    double New_Aspect_Ratio;
    size_t New_Area = 0;

    swap(Negative_Sequence[index1], Negative_Sequence[index2]);
    New_Width = Calculate_X_Coordinate();
    New_Height = Calculate_Y_Coordinate();
    New_Area = New_Width * New_Height;
    New_Aspect_Ratio = double(New_Width) / double(New_Height);

    // Illegal Move
    if(New_Aspect_Ratio > Aspect_Ratio_Higher_Bound || New_Aspect_Ratio < Aspect_Ratio_Lower_Bound){
        swap(Negative_Sequence[index1], Negative_Sequence[index2]);
        Width = Calculate_X_Coordinate();
        Height = Calculate_Y_Coordinate();
        Area = Width * Height;
        return REJECT;
    }

    // Better Move
    if(New_Area < Area){
        Width = New_Width;
        Height = New_Height;
        Area = New_Area;
        return ACCEPT;
    }

    // Worse but legal move
    else{
        double Delta_Area = New_Area - Area;
        double r = rng->Generate_Random_Float();

        // Accept
        if(r < exp(-1 * Delta_Area / Temperature)){
            Width = New_Width;
            Height = New_Height;
            Area = New_Area;
            return ACCEPT;
        }

        // Reject
        else{
            swap(Negative_Sequence[index1], Negative_Sequence[index2]);
            Width = Calculate_X_Coordinate();
            Height = Calculate_Y_Coordinate();
            Area = Width * Height;
            return REJECT;
        }
    }
}

// Swap 2 modules in both Positive & Negative sequences
bool Floorplan::Operation3(){
    cout << "OP3" << endl;
    size_t index1 = rng->Generate_Random_Integer(Num_Blocks - 1);
    size_t index2 = rng->Generate_Random_Integer(Num_Blocks - 1);
    size_t index3 = 0;
    size_t index4 = 0;

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
    assert(index1 < Num_Blocks && index1 >= 0);
    assert(index2 < Num_Blocks && index2 >= 0);
    assert(index3 < Num_Blocks && index3 >= 0);
    assert(index4 < Num_Blocks && index4 >= 0);
    swap(Positive_Sequence[index1], Positive_Sequence[index2]);
    swap(Negative_Sequence[index3], Negative_Sequence[index4]);
    size_t New_Width =  Calculate_X_Coordinate();
    size_t New_Height = Calculate_Y_Coordinate();
    double New_Aspect_Ratio = double(New_Width) / double(New_Height);
    size_t New_Area = New_Width * New_Height;

    // Illegal Move
    if(New_Aspect_Ratio > Aspect_Ratio_Higher_Bound || New_Aspect_Ratio < Aspect_Ratio_Lower_Bound){
        swap(Positive_Sequence[index1], Positive_Sequence[index2]);
        swap(Negative_Sequence[index3], Negative_Sequence[index4]);
        Width = Calculate_X_Coordinate();
        Height = Calculate_Y_Coordinate();
        Area = Width * Height;
        return REJECT;
    }

    // Better Move
    if(New_Area < Area){
        Width = New_Width;
        Height = New_Height;
        Area = New_Area;
        return ACCEPT;
    }

    // Worse but legal move
    else{
        double Delta_Area = New_Area - Area;
        double r = rng->Generate_Random_Float();

        // Accept
        if(r < exp(-1 * Delta_Area / Temperature)){
            Width = New_Width;
            Height = New_Height;
            Area = New_Area;
            return ACCEPT;
        }

        // Reject
        else{
            swap(Positive_Sequence[index1], Positive_Sequence[index2]);
            swap(Negative_Sequence[index3], Negative_Sequence[index4]);
            Width = Calculate_X_Coordinate();
            Height = Calculate_Y_Coordinate();
            Area = Width * Height;
            return REJECT;
        }
    }
}

// Rotate a block
bool Floorplan::Operation4(){
    cout << "OP4" << endl;
    size_t index = rng->Generate_Random_Integer(Num_Blocks - 1);
    assert(index < Num_Blocks && index >= 0);
    Blocks[index]->Rotate();
    size_t New_Width =  Calculate_X_Coordinate();
    size_t New_Height = Calculate_Y_Coordinate();
    double New_Aspect_Ratio = double(New_Width) / double(New_Height);
    size_t New_Area = New_Width * New_Height;

    // Illegal Move
    if(New_Aspect_Ratio > Aspect_Ratio_Higher_Bound || New_Aspect_Ratio < Aspect_Ratio_Lower_Bound){
        Blocks[index]->Rotate();
        Width = Calculate_X_Coordinate();
        Height = Calculate_Y_Coordinate();
        Area = Width * Height;
        return REJECT;
    }

    // Better Move
    if(New_Area < Area){
        Width = New_Width;
        Height = New_Height;
        Area = New_Area;
        return ACCEPT;
    }

    // Worse but legal move
    else{
        double Delta_Area = New_Area - Area;
        double r = rng->Generate_Random_Float();

        // Accept
        if(r < exp(-1 * Delta_Area / Temperature)){
            Width = New_Width;
            Height = New_Height;
            Area = New_Area;
            return ACCEPT;
        }

        // Reject
        else{
            Blocks[index]->Rotate();
            Width = Calculate_X_Coordinate();
            Height = Calculate_Y_Coordinate();
            Area = Width * Height;
            return REJECT;
        }
    }
}