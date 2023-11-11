#include "Floorplan.h"

// Constructor & Destructor
Floorplan::Floorplan(){
    ;
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
}

void Floorplan::Run(){
    Init_Sequence();
    cout << Evaluate_Sequence(EVALUATE_X) << endl;
    cout << Evaluate_Sequence(EVALUATE_Y) << endl;

    ofstream fout("out");
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

size_t Floorplan::Evaluate_Sequence(int8_t option){
    if(option & EVALUATE_Y){
        reverse(Positive_Sequence.begin(), Positive_Sequence.end());
    }
    size_t *match_x = new size_t[Blocks.size()];
    size_t *match_y = new size_t[Blocks.size()];
    for(size_t i = 0; i < Blocks.size(); i++){
        match_x[Positive_Sequence[i]] = i;
        match_y[Negative_Sequence[i]] = i;
    }

    VanEmdeBoas *H = new VanEmdeBoas(Blocks.size() + 1);
    H->Insert(0);
    vector<int> BUCKL(Blocks.size() + 1, 0);
    for (int i = 0; i < Blocks.size(); ++i) {
        int b = Positive_Sequence[i];
        int p = match_y[b];
        H->Insert(p);
        if (option & EVALUATE_X) {
            // x coordinates
            int pos = BUCKL[H->Predecessor(p)];
            BUCKL[p] = pos + Blocks[b]->Width;
            Blocks[b]->X_Coordinate = pos;
        } else {
            // y coordinates
            int pos = BUCKL[H->Predecessor(p)];
            BUCKL[p] = pos + Blocks[b]->Height;
            Blocks[b]->Y_Coordinate = pos;
        }
        int k = p;
        while (H->Successor(k) != -1) {
            k = H->Successor(k);
            if (BUCKL[k] <= BUCKL[p])
                H->Delete(k);            
        }
    }

    if(option & EVALUATE_Y){
        reverse(Positive_Sequence.begin(), Positive_Sequence.end());
    }
    delete []match_x;
    delete []match_y;
    return BUCKL[H->GetMax()];
}