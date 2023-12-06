#include "Standard_Cell.h"

// Constructor & Destructor
Standard_Cell::Standard_Cell(){
    ;
}

Standard_Cell::~Standard_Cell(){
    for(const auto &finfet: FinFETs){
        delete finfet;
    }
}

// Parser
void Standard_Cell::Parse_Spice(ifstream &fin){
    string line;
    getline(fin, line);     // read .SUBCKT
    while(getline(fin, line)){
        if(line == ".ENDS") break;
        stringstream ss(line);
        string name, drain, gate, source, body, pvt, width_str, length_str, nfin;
        double width, length;
        FinFET_Type type;
        const regex Float_Pattern(R"(-?\d+(\.\d+)?)");
        smatch width_match;
        smatch length_match;
        
        ss >> name >> drain >> gate >> source >> body >> pvt >> width_str >> length_str >> nfin;
        type = (pvt == "nmos_rvt") ? N_Type : P_Type; 
        regex_search(width_str, width_match, Float_Pattern);
        regex_search(length_str, length_match, Float_Pattern);
        width = stod(width_match.str());
        length = stod(length_match.str());
        FinFET *finfet = new FinFET(name, drain, gate, source, type, width, length);
        FinFETs.emplace_back(finfet);
        if(type == N_Type){
            N_FinFETs.emplace_back(finfet);
        }
        else if(type == P_Type){
            P_FinFETs.emplace_back(finfet);
        }
        else abort();

        if(PRINT_FINFET_INFO){
            cout << *finfet << endl;
        }
    }
    fin.close();
    Num_FinFETs = FinFETs.size();
    assert(Num_FinFETs % 2 == 0);
    assert(Num_FinFETs / 2 == N_FinFETs.size());
    assert(Num_FinFETs / 2 == P_FinFETs.size());
}

void Standard_Cell::Init_Sequence(){
    for(const auto &finfet : N_FinFETs){
        Poly_Sequence.emplace_back(finfet->Gate);
    }
    // srand(time(NULL));
    // random_shuffle(Poly_Sequence.begin(), Poly_Sequence.end());
    for(const auto &gate : Poly_Sequence){
        cout << gate << " ";
    }
    cout << endl;

    for(size_t i = 0; i < Poly_Sequence.size(); i++){
        Poly_Sequence_With_Dummy.emplace_back(Poly_Sequence[i]);
        if(i == Poly_Sequence.size() - 1){
            continue;
        }
        Poly_Sequence_With_Dummy.emplace_back("Dummy");
    }

    for(const auto &gate : Poly_Sequence_With_Dummy){
        cout << gate << " ";
    }
    cout << endl;
}