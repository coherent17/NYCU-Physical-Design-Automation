#include "FM.h"

FM::FM():
    Num_Cells(0),
    Num_Nets(0),
    Max_Degree(0),
    Balanced_Factor(0),
    Lower_Partition_Bound(0),
    Higher_Partition_Bound(0),
    Current_Best_Cut(INT_MAX),
    Current_Pass(0)
{
    Partition_Size[Left] = 0;
    Partition_Size[Right] = 0;
    BucketLists[Left] = nullptr;
    BucketLists[Right] = nullptr;
    StartTime = chrono::steady_clock::now();
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

    Num_Cells = Cell_Array.size();
    Num_Nets = Net_Array.size();
    Current_Best_Partition.resize(Num_Cells, Left);
    // find max gain
    for(int i = 0; i < Num_Cells; i++){
        Max_Degree = Max_Degree > (int)Cell_Array[i]->Get_Net_List_Size() ? Max_Degree : Cell_Array[i]->Get_Net_List_Size();
    }

    Lower_Partition_Bound = (1 - Balanced_Factor) * Num_Cells / 2.0;
    Higher_Partition_Bound = (1 + Balanced_Factor) * Num_Cells / 2.0;

    // Parser Summary
    cout << endl;
    cout << "==================== Parser Summary ====================" << endl;
    cout << "Num Cell: " << Num_Cells << endl;
    cout << "Num Net: " << Num_Nets << endl;
    cout << "Max Degree: " << Max_Degree << endl;
    cout << "Lower Bound: " << Lower_Partition_Bound << endl;
    cout << "Higher Bound: " << Higher_Partition_Bound << endl;
}

void FM::Dump(ofstream &fout){
    fout << "Cutsize = " << Current_Best_Cut << endl;
    int Best_Left_Partition_Size = 0;
    int Best_Right_Partition_Size = 0;

    for(size_t i = 0; i < Current_Best_Partition.size(); i++){
        if(Current_Best_Partition[i] == Left){
            Best_Left_Partition_Size++;
        }
        else{
            Best_Right_Partition_Size++;
        }
    }

    fout << "G1 " << Best_Left_Partition_Size << endl;
    for(size_t i = 0; i < Current_Best_Partition.size(); i++){
        if(Current_Best_Partition[i] == Left){
            fout << Cell_Array[i]->Get_Cell_Name() << " ";
        }
    }
    fout << ";" << endl;
    fout << "G2 " << Best_Right_Partition_Size << endl;
    for(size_t i = 0; i < Current_Best_Partition.size(); i++){
        if(Current_Best_Partition[i] == Right){
            fout << Cell_Array[i]->Get_Cell_Name() << " ";
        }
    }
    fout << ";" << endl;
    fout.close();
}

void FM::Run(){
    random_device rd; 
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(-1, 0);

    Initialize_Partition();
    Construct_BucketList();
    cout << "Initial State: " << Get_Cut() << endl;

    Cell *Base_Cell;
    Partition_Side Side;
    int Best_Cut_Repeat = 0;
    long long ElapsedTimeSeconds;
    int Pass = 0;

    do{
        Unlock_Cell_State();
        Construct_BucketList();
        int Left_Gain_Boundary = dist(gen);
        int Right_Gain_Boundary = dist(gen);
        while(BucketLists[Left]->Get_Current_Max_Gain() >= Left_Gain_Boundary || BucketLists[Right]->Get_Current_Max_Gain() >= Right_Gain_Boundary){
            Base_Cell = Find_Base_Cell();
            assert(Base_Cell != nullptr);
            Side = Base_Cell->Get_Side();
            Base_Cell->Set_State(Lock);
            BucketLists[Side]->Delete_Node(Base_Cell->Get_Node());
            Update_Neighbor_Gain(Base_Cell);
            Update_Base_Cell(Base_Cell);
        }
        Pass++;
        int cut = Get_Cut();
        if(cut < Current_Best_Cut){
            Current_Pass = Pass;
            Best_Cut_Repeat = 0;
            Current_Best_Cut = cut;
            for(int i = 0; i < Num_Cells; i++){
                Current_Best_Partition[i] = Cell_Array[i]->Get_Side();
            }
        }
        if(cut == Current_Best_Cut) Best_Cut_Repeat++;
        cout << "[FM(" << Pass << ")]Cut Size: " << cut << ", Current Best Cut: " << Current_Best_Cut << ", Repeat for: " << Best_Cut_Repeat << ", Not Change for: " << Pass - Current_Pass << endl;
        auto EndTime = chrono::steady_clock::now();
        ElapsedTimeSeconds = chrono::duration_cast<chrono::seconds>(EndTime - StartTime).count();
        if(ElapsedTimeSeconds > MAX_EXECUTION_TIME - BUFFER_TIME) break;
        if(Pass - Current_Pass > 500) break;
    }while(Best_Cut_Repeat <= CONVERAGE_CRITERIA);
}

void FM::Initialize_Partition(){

    for(int i = 0; i < (int)Lower_Partition_Bound + 1; i++){
        Cell_Array[i]->Set_Side(Left);
        Partition_Size[Left]++;
    }

    for(int i = (int)Lower_Partition_Bound + 1; i < Num_Cells; i++){
        Cell_Array[i]->Set_Side(Right);
        Partition_Size[Right]++;
    }

    assert(Partition_Size[Left] + Partition_Size[Right] == Num_Cells);
    assert(Partition_Size[Left] >= Lower_Partition_Bound && Partition_Size[Left] <= Higher_Partition_Bound);
    assert(Partition_Size[Right] >= Lower_Partition_Bound && Partition_Size[Right] <= Higher_Partition_Bound);

    for(int i = 0; i < Num_Nets; i++){
        for(size_t j = 0; j < Net_Array[i]->Get_Cell_List_Size(); j++){
            Cell *cell = Net_Array[i]->Get_Cell(j);
            Net_Array[i]->Increase_Partition_Size(cell->Get_Side());
        }
    }

    cout << endl;
    cout << "==================== Init Partition Summary ====================" << endl;
    cout << "Left: " << Partition_Size[Left] << ", Right: " << Partition_Size[Right] << endl;
}

void FM::Construct_BucketList(){
    if(BucketLists[Left] || BucketLists[Right]){
        BucketLists[Left]->Clear();
        BucketLists[Right]->Clear();
    }

    //allocate for the bucketlist
    BucketLists[Left] = new BucketList(Max_Degree);
    BucketLists[Right] = new BucketList(Max_Degree);

    for(int i = 0; i < Num_Cells; i++){
        int gain = 0;
        Partition_Side Cell_Side = Cell_Array[i]->Get_Side();
        Partition_Side Other_Side = static_cast<Partition_Side>(1 - static_cast<int>(Cell_Side));
        for(size_t j = 0; j < Cell_Array[i]->Get_Net_List_Size(); j++){
            Net *net = Cell_Array[i]->Get_Net(j);
            assert(net != nullptr);
            if(net->Get_Partition_Size(Cell_Side) == 1){
                //FS
                gain++;
            }
            if(net->Get_Partition_Size(Other_Side) == 0){
                //TE
                gain--;
            }
        }
        Cell_Array[i]->Set_Gain(gain);
        BucketLists[Cell_Side]->Insert_Node(Cell_Array[i]->Get_Node(), gain);
    }
}

Cell *FM::Find_Base_Cell(){
    Node *Left_Max_Gain_Node = BucketLists[Left]->Get_Max_Gain_Node();
    Node *Right_Max_Gain_Node = BucketLists[Right]->Get_Max_Gain_Node();

    // Boundary Condition: Can only take the cell from 1 side
    if(Partition_Size[Left] - 1 <= Lower_Partition_Bound){
        assert(Right_Max_Gain_Node != nullptr);
        return Right_Max_Gain_Node->cell;
    }
    else if(Partition_Size[Right] - 1 <= Lower_Partition_Bound){
        assert(Left_Max_Gain_Node != nullptr);
        return Left_Max_Gain_Node->cell;
    }

    if(Left_Max_Gain_Node == nullptr && Right_Max_Gain_Node == nullptr){
        return nullptr;
    }

    if(Left_Max_Gain_Node == nullptr){
        return Right_Max_Gain_Node->cell;
    }
    else if(Right_Max_Gain_Node == nullptr){
        return Left_Max_Gain_Node->cell;
    }

    assert(Left_Max_Gain_Node != nullptr && Right_Max_Gain_Node != nullptr);
    // Get the node that has larger gain
    if(Left_Max_Gain_Node->cell->Get_Gain() == Right_Max_Gain_Node->cell->Get_Gain()){
        return Left_Max_Gain_Node->cell->Get_Cell_Name() < Right_Max_Gain_Node->cell->Get_Cell_Name() ? Left_Max_Gain_Node->cell : Right_Max_Gain_Node->cell;
    }
    else if(Left_Max_Gain_Node->cell->Get_Gain() < Right_Max_Gain_Node->cell->Get_Gain()){
        return Right_Max_Gain_Node->cell;
    }
    else{
        return Left_Max_Gain_Node->cell;
    }
}


// Algorithm: Update_Gain
// 1 begin /* move base cell and update neighbors' gains */ 
// 2 F : the Front Block of the base cell; 
// 3 T : the To Block of the base cell; 
// 4 Lock the base cell and complement its block;
// 5 for each net n on the base cell do 
// /* check critical nets before the move */
// 6 if T(n) = 0 then increment gains of all free cells on n
// else if T(n)=1 then decrement gain of the only T cell on n,
// if it is free
// /* change F(n) and T(n) to reflect the move */
// 7 F(n) =  F(n) - 1; T(n) = T(n)+1; 
// /* check for critical nets after the move */ 
// 8 if F(n)=0 then decrement gains of all free cells on n
// else if F(n) = 1 then increment gain of the only F cell on n,
// if it is free
// 9 end
void FM::Update_Neighbor_Gain(Cell *Base_Cell){
    Partition_Side Cell_Side = Base_Cell->Get_Side();
    Partition_Side Other_Side = static_cast<Partition_Side>(1 - static_cast<int>(Cell_Side));

    // Only consider the critical net
    for(size_t i = 0; i < Base_Cell->Get_Net_List_Size(); i++){
        Net *net = Base_Cell->Get_Net(i);
        int F_net = net->Get_Partition_Size(Cell_Side);
        int T_net = net->Get_Partition_Size(Other_Side);
        if(T_net == 0){
            for(size_t j = 0; j < net->Get_Cell_List_Size(); j++){
                Cell *cell = net->Get_Cell(j);
                if(cell->Get_State() != Lock){
                    cell->Set_Gain(cell->Get_Gain() + 1);
                    BucketLists[Cell_Side]->Delete_Node(cell->Get_Node());
                    BucketLists[Cell_Side]->Insert_Node(cell->Get_Node(), cell->Get_Gain());
                }
            }
        }
        else if(T_net == 1){
            for(size_t j = 0; j < net->Get_Cell_List_Size(); j++){
                Cell *cell = net->Get_Cell(j);
                if(cell->Get_State() != Lock && cell->Get_Side() == Other_Side){
                    cell->Set_Gain(cell->Get_Gain() - 1);
                    BucketLists[Other_Side]->Delete_Node(cell->Get_Node());
                    BucketLists[Other_Side]->Insert_Node(cell->Get_Node(), cell->Get_Gain());
                    break;
                }
            }
        }

        F_net = F_net - 1;
        T_net = T_net + 1;
        
        if(F_net == 0){
            for(size_t j = 0; j < net->Get_Cell_List_Size(); j++){
                Cell *cell = net->Get_Cell(j);
                if(cell->Get_State() != Lock){
                    cell->Set_Gain(cell->Get_Gain() - 1);
                    BucketLists[Other_Side]->Delete_Node(cell->Get_Node());
                    BucketLists[Other_Side]->Insert_Node(cell->Get_Node(), cell->Get_Gain());
                }
            }
        }
        else if(F_net == 1){
            for(size_t j = 0; j < net->Get_Cell_List_Size(); j++){
                Cell *cell = net->Get_Cell(j);
                if(cell->Get_State() != Lock && cell->Get_Side() == Cell_Side){
                    cell->Set_Gain(cell->Get_Gain() + 1);
                    BucketLists[Cell_Side]->Delete_Node(cell->Get_Node());
                    BucketLists[Cell_Side]->Insert_Node(cell->Get_Node(), cell->Get_Gain());
                    break;
                }
            }
        }
    }
}

void FM::Update_Base_Cell(Cell *Base_Cell){
    Partition_Side Cell_Side = Base_Cell->Get_Side();
    Partition_Side Other_Side = static_cast<Partition_Side>(1 - static_cast<int>(Cell_Side));

    // Move Base_Cell to other side
    Base_Cell->Set_Side(Other_Side);

    // Update net partition size
    for(size_t i = 0; i < Base_Cell->Get_Net_List_Size(); i++){
        Net *net = Base_Cell->Get_Net(i);
        net->Decrease_Partition_Size(Cell_Side);
        net->Increase_Partition_Size(Other_Side);
    }

    // Update the overall Partition Size in FM class
    Partition_Size[Cell_Side]--;
    Partition_Size[Other_Side]++;
}

void FM::Unlock_Cell_State(){
    for(int i = 0; i < Num_Cells; i++){
        Cell_Array[i]->Set_State(Not_Lock);
    }
}

int FM::Get_Cut()const{
    int cut = 0;
    for(int i = 0; i < Num_Nets; i++){
        if(Net_Array[i]->Get_Partition_Size(Left) && Net_Array[i]->Get_Partition_Size(Right)){
            cut++;
        }
    }
    return cut;
}