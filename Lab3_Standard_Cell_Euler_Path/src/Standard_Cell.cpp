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
        Nodes.insert(source);
        Nodes.insert(drain);
        if(type == N_Type){
            N_FinFETs.emplace_back(finfet);
            N_Poly_Map.insert(make_pair(finfet->Gate, finfet));
        }
        else if(type == P_Type){
            P_FinFETs.emplace_back(finfet);
            P_Poly_Map.insert(make_pair(finfet->Gate, finfet));
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

    for(const auto &entry: N_Poly_Map){
        cout << entry.first << "->" << *entry.second << endl;
    }

    for(const auto &entry: P_Poly_Map){
        cout << entry.first << "->" << *entry.second << endl;
    }

    for(const auto &node: Nodes){
        cout << node << " ";
    }
    cout << endl;
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

    // Map gate to place the source and drain
    multimap<string, FinFET*> N_Poly_Map_Copy(N_Poly_Map.begin(), N_Poly_Map.end());
    multimap<string, FinFET*> P_Poly_Map_Copy(P_Poly_Map.begin(), P_Poly_Map.end());

    for (const auto &gate : Poly_Sequence_With_Dummy) {
        if (gate != "Dummy") {
            Layout.emplace_back(make_pair(P_Poly_Map_Copy.find(gate)->second, N_Poly_Map_Copy.find(gate)->second));

            // Erase elements with the given key
            auto range_P = P_Poly_Map_Copy.equal_range(gate);
            auto range_N = N_Poly_Map_Copy.equal_range(gate);

            for (auto it = range_P.first; it != range_P.second; /* no increment here */) {
                if (it->second == P_Poly_Map_Copy.find(gate)->second) {
                    it = P_Poly_Map_Copy.erase(it);
                    break;
                } else {
                    ++it;
                }
            }

            for (auto it = range_N.first; it != range_N.second; /* no increment here */) {
                if (it->second == N_Poly_Map_Copy.find(gate)->second) {
                    it = N_Poly_Map_Copy.erase(it);
                    break;
                } else {
                    ++it;
                }
            }
        }
        else if(gate == "Dummy"){
            Layout.emplace_back(make_pair(new FinFET(true), new FinFET(true)));
        }
        else abort();
    }

    assert(P_Poly_Map_Copy.size() == 0);
    assert(N_Poly_Map_Copy.size() == 0);

    for(const auto &pair : Layout){
        FinFET *PMOS = pair.first;
        FinFET *NMOS = pair.second;
        if(PMOS->Name == "Dummy" && NMOS->Name == "Dummy") continue;
        assert(PMOS->Gate == NMOS->Gate);
        cout << PMOS->Gate << endl;
        cout << "\tP:\t" << ((PMOS->Swap_Drain_Source == false) ? PMOS->Drain + " " + PMOS->Gate + " " + PMOS->Source : PMOS->Source + " " + PMOS->Gate + " " + PMOS->Drain) << endl;
        cout << "\tN:\t" << ((NMOS->Swap_Drain_Source == false) ? NMOS->Drain + " " + NMOS->Gate + " " + NMOS->Source : NMOS->Source + " " + NMOS->Gate + " " + NMOS->Drain) << endl;
    }
}