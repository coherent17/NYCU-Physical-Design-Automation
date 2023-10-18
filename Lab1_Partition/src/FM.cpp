#include "FM.h"

FM::FM():
    Num_Cells(0),
    Num_Nets(0),
    Max_Degree(0),
    Balanced_Factor(0),
    Lower_Bound(0),
    Higher_Bound(0)
{
    ;
}

FM::~FM(){

    for(auto &cell : Cell_Array){
        delete cell;
    }

    for(auto &net : Net_Array){
        delete net;
    }
}

void FM::Parser(ifstream &fin){
    // Parse Balanced Factor
    fin >> Balanced_Factor;

    // Parse hyperedge net
    // A hash table map cell name to the pointer to the cell object
    unordered_map<string, Cell *> Cell_Map;
    while(fin){
        string literal;
        fin >> literal;
        if(literal == "NET"){
            string Net_Name;
            fin >> Net_Name;
            Net *net = new Net(Net_Name);
            while(fin >> literal &&  literal != ";"){
                // Check if the Cell exists in the Cell_Map
                string Cell_Name = literal;
                if (Cell_Map.find(Cell_Name) == Cell_Map.end()) {
                    Cell_Map[Cell_Name] = new Cell(Cell_Name);
                }
                Cell_Map[Cell_Name]->Nets.emplace_back(net);
                net->Cells.emplace_back(Cell_Map[Cell_Name]);
            }
            Net_Array.emplace_back(net);
        }
    }
    fin.close();

    // Construct Cell Array
    for(const auto& pair : Cell_Map){
        Cell_Array.emplace_back(pair.second);
    }

    Num_Cells = Cell_Array.size();
    Num_Nets = Net_Array.size();

    // Find Max Degree
    for(size_t i = 0; i < Num_Cells; i++){
        size_t Cell_Degree = Cell_Array[i]->Nets.size();
        Max_Degree = Max_Degree > Cell_Degree ? Max_Degree : Cell_Degree;
    }

    // Calculate partition bound
    Lower_Bound = (1 - Balanced_Factor) * Num_Cells / 2.0;
    Higher_Bound = (1 + Balanced_Factor) * Num_Cells / 2.0;
}

void FM::Dump(ofstream &fout){
    fout << "Cutsize = " << Get_Cut() << endl;

    fout << "G1 " << Partition_Size[Left] << endl;
    for(const auto &cell : Cell_Array){
        if(cell->Side == Left){
            fout << cell->Name << " ";
        }
    }
    fout << ";" << endl;
    fout << "G2 " << Partition_Size[Right] << endl;
    for(const auto &cell : Cell_Array){
        if(cell->Side == Right){
            fout << cell->Name << " ";
        }
    }
    fout << ";" << endl;
    fout.close();
}

void FM::Run(){
    Initialize_Partition();
    cout << "Init: " << Get_Cut() << endl;

    Construct_BucketList();
    Unlock_Cells();
    while(BucketLists[Left]->Current_Max_Gain >= 1 || BucketLists[Right]->Current_Max_Gain >= 1){
        Cell *Base_Cell = Find_Base_Cell();
        //cout << *Base_Cell << endl;
        Base_Cell->State = Lock;
        BucketLists[Base_Cell->Side]->Delete(Base_Cell);
        Update_Neighbor_Gain(Base_Cell);
        Update_Base_Cell(Base_Cell);
        cout << Get_Cut() << endl;
    }
    cout << Get_Cut() << endl;
}

void FM::Initialize_Partition(){
    for(size_t i = 0; i < (size_t)Lower_Bound + 1; i++){
        Cell_Array[i]->Side = Left;
        Partition_Size[Left]++;
    }

    for(size_t i = (size_t)Lower_Bound + 1; i < Num_Cells; i++){
        Cell_Array[i]->Side = Right;
        Partition_Size[Right]++;
    }

    // Check for the bounding criteria
    assert(Partition_Size[Left] + Partition_Size[Right] == Num_Cells);
    assert(Partition_Size[Left] >= Lower_Bound && Partition_Size[Left] <= Higher_Bound);
    assert(Partition_Size[Right] >= Lower_Bound && Partition_Size[Right] <= Higher_Bound);

    // For each net, calculate how many cells are in each partition
    for(const auto &net : Net_Array){
        for(const auto &cell : net->Cells){
            net->Partition_Size[cell->Side]++;
        }
    }
}

void FM::Construct_BucketList(){
    // Allocate for the BucketList
    BucketLists[Left] = new BucketList(Max_Degree);
    BucketLists[Right] = new BucketList(Max_Degree);

    // Calculate Initial Cell Gain By (FS - TE)
    for(const auto &cell : Cell_Array){
        int gain = 0;
        Partition_Side Cell_Side = cell->Side;
        Partition_Side Other_Side = static_cast<Partition_Side>(1 - static_cast<int>(cell->Side));
        for(const auto &net : cell->Nets){
            if(net->Partition_Size[Cell_Side] == 1){
                // FS
                gain++;
            }
            if(net->Partition_Size[Other_Side] == 0){
                // TE
                gain--;
            }
        }
        cell->Gain = gain;
        BucketLists[Cell_Side]->Insert(gain, cell);
    }
}

Cell *FM::Find_Base_Cell(){
    Cell *Left_Max_Gain_Cell = BucketLists[Left]->Get_Max_Gain_Cell();
    Cell *Right_Max_Gain_Cell = BucketLists[Right]->Get_Max_Gain_Cell();

    // Boundary Condition: Can only take the cell from 1 side
    if(Partition_Size[Left] - 1 <= Lower_Bound){
        assert(Right_Max_Gain_Cell != nullptr);
        return Right_Max_Gain_Cell;
    }
    else if(Partition_Size[Right] - 1 <= Lower_Bound){
        assert(Left_Max_Gain_Cell != nullptr);
        return Left_Max_Gain_Cell;
    }

    if(Left_Max_Gain_Cell == nullptr && Right_Max_Gain_Cell == nullptr){
        return nullptr;
    }

    if(Left_Max_Gain_Cell == nullptr){
        return Right_Max_Gain_Cell;
    }
    else if(Right_Max_Gain_Cell == nullptr){
        return Left_Max_Gain_Cell;
    }

    assert(Left_Max_Gain_Cell != nullptr && Right_Max_Gain_Cell != nullptr);
    // Get the node that has larger gain
    if(Left_Max_Gain_Cell->Gain == Right_Max_Gain_Cell->Gain){
        return Left_Max_Gain_Cell->Name < Right_Max_Gain_Cell->Name ? Left_Max_Gain_Cell : Right_Max_Gain_Cell;
    }
    else if(Left_Max_Gain_Cell->Gain < Right_Max_Gain_Cell->Gain){
        return Right_Max_Gain_Cell;
    }
    else{
        return Left_Max_Gain_Cell;
    }
}


/*

Algorithm: Update_Gain
begin [move base cell and update neighbors' gains]
F <- the Front Block of the base cell; 
T <- the To Block of the base cell; 
Lock the base cell and complement its block;
for each net n on the base cell do 

    if T(n) = 0 then increment gains of all free cells on n
    else if T(n)=1 then decrement gain of the only T cell on n, if it is free

    // update F and T to reflect the move
    F(n) =  F(n) - 1; T(n) = T(n)+1; 

    if F(n)=0 then decrement gains of all free cells on n
    else if F(n) = 1 then increment gain of the only F cell on n,
    if it is free
end

*/

void FM::Update_Neighbor_Gain(Cell *Base_Cell){
    Partition_Side Cell_Side = Base_Cell->Side;
    Partition_Side Other_Side = static_cast<Partition_Side>(1 - static_cast<int>(Base_Cell->Side));

    // Only consider the critical net
    for(const auto &net : Base_Cell->Nets){
        int F = net->Partition_Size[Cell_Side];
        int T = net->Partition_Size[Other_Side];

        if(T == 0){
            for(const auto &cell : net->Cells){
                if(cell->State != Lock){
                    cell->Gain += 1;
                    BucketLists[Cell_Side]->Delete(cell);
                    BucketLists[Cell_Side]->Insert(cell->Gain, cell);
                }
            }
        }

        else if(T == 1){
            for(const auto &cell : net->Cells){
                if(cell->State != Lock && cell->Side == Other_Side){
                    cell->Gain -= 1;
                    BucketLists[Other_Side]->Delete(cell);
                    BucketLists[Other_Side]->Insert(cell->Gain, cell);
                    break;
                }
            }
        }

        F--;
        T++;

        if(F == 0){
            for(const auto &cell : net->Cells){
                if(cell->State != Lock){
                    cell->Gain -= 1;
                    BucketLists[Other_Side]->Delete(cell);
                    BucketLists[Other_Side]->Insert(cell->Gain, cell);
                }
            }
        }

        else if(F == 1){
            for(const auto &cell : net->Cells){
                if(cell->State != Lock && cell->Side == Cell_Side){
                    cell->Gain += 1;
                    BucketLists[Cell_Side]->Delete(cell);
                    BucketLists[Cell_Side]->Insert(cell->Gain, cell);
                    break;
                }
            }
        }
    }
}

void FM::Update_Base_Cell(Cell *Base_Cell){
    Partition_Side Cell_Side = Base_Cell->Side;
    Partition_Side Other_Side = static_cast<Partition_Side>(1 - static_cast<int>(Base_Cell->Side));

    // Move Base Cell to other side
    Base_Cell->Side = Other_Side;

    // Update net partition size
    for(const auto &net : Base_Cell->Nets){
        net->Partition_Size[Cell_Side]--;
        net->Partition_Size[Other_Side]++;
    }

    // Update overall partition size in FM class
    Partition_Size[Cell_Side]--;
    Partition_Size[Other_Side]++;
}

void FM::Unlock_Cells(){
    for(int i = 0; i < Num_Cells; i++){
        Cell_Array[i]->State = Not_Lock;
    }
}

int FM::Get_Cut()const{
    int cut = 0;
    for(int i = 0; i < Num_Nets; i++){
        if(Net_Array[i]->Partition_Size[Left] > 0 && Net_Array[i]->Partition_Size[Right] > 0){
            cut++;
        }
    }
    return cut;
}