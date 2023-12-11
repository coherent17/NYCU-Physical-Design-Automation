#include "Standard_Cell.h"

Standard_Cell::Standard_Cell() : Num_FinFETs(0){
    ;
}
Standard_Cell::~Standard_Cell(){
    for(FinFET *finfet : FinFETs){
        delete finfet;
    }
}

void Standard_Cell::Spice_Parser(ifstream &fin){
    string line;
    string token;
    getline(fin, line); // read .SUBCKT
    while(getline(fin, line)){
        if(line == ".ENDS") break;
        stringstream ss(line);
        string name, drain, gate, source, body, pvt, width_str, length_str, nfin;
        double width, length;
        FinFET_Type type;

        // Regex pattern for floating-point numbers
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
        Pin_Names.insert(drain);
        Pin_Names.insert(source);

        if(type == N_Type){
            N_FinFETs.emplace_back(finfet);
            FinFET_Pin_Map[drain].emplace_back(finfet);
            FinFET_Pin_Map[source].emplace_back(finfet);
            N_FinFET_Poly_Map[gate].emplace_back(finfet);
        }
        else if(type == P_Type){
            P_FinFETs.emplace_back(finfet);
            FinFET_Pin_Map[drain].emplace_back(finfet);
            FinFET_Pin_Map[source].emplace_back(finfet);
            P_FinFET_Poly_Map[gate].emplace_back(finfet);
        }
        else abort();
    }
    fin.close();
    Num_FinFETs = FinFETs.size();

    // Standard Cell Property Check
    assert(Num_FinFETs % 2 == 0);
    assert(Num_FinFETs / 2 == N_FinFETs.size());
    assert(Num_FinFETs / 2 == P_FinFETs.size());
    assert(N_FinFET_Poly_Map.size() == P_FinFET_Poly_Map.size());

    cout << "########### Pin Map ###########" << endl;
    for(const auto &pair : FinFET_Pin_Map){
        cout << pair.first << "->";
        for(const auto &finfet : pair.second){
            cout << finfet->Name << " ";
        }
        cout << endl;
    }

    cout << "########### N Poly Map ###########" << endl;
    for(const auto &pair : N_FinFET_Poly_Map){
        cout << pair.first << "->";
        for(const auto &finfet : pair.second){
            cout << finfet->Name << " ";
        }
        cout << endl;
    }
    
    cout << "########### P Poly Map ###########" << endl;
    for(const auto &pair : P_FinFET_Poly_Map){
        cout << pair.first << "->";
        for(const auto &finfet : pair.second){
            cout << finfet->Name << " ";
        }
        cout << endl;
    }
    P_Active_Width = P_FinFETs.front()->Width;
    N_Active_Width = N_FinFETs.front()->Width;
    N_Active_Center_Height = N_FinFETs.front()->Length / 2;
    P_Active_Center_Height = N_FinFETs.front()->Length + ACTIVE_VERTICAL_SPACING + P_FinFETs.front()->Length / 2;
}

void Standard_Cell::Run(){
    Init_Poly_Sequence();
    Calculate_HPWL();
}

void Standard_Cell::Init_Poly_Sequence(){
    vector<string> Poly_Sequence;
    vector<string> Poly_Sequence_With_Dummy;

    for(const auto &finfet : N_FinFETs){
        Poly_Sequence.emplace_back(finfet->Gate);
    }
    // Should add these 2 line when release
    // srand(time(NULL));
    // random_shuffle(Poly_Sequence.begin(), Poly_Sequence.end());
    cout << "########### Gate Seq ###########" << endl;
    for(const auto &gate : Poly_Sequence){
        cout << gate << " ";
    }
    cout << endl;

    for(size_t i = 0; i < Poly_Sequence.size(); i++){
        Poly_Sequence_With_Dummy.emplace_back(Poly_Sequence[i]);
        if(i != Poly_Sequence.size() - 1){
            Poly_Sequence_With_Dummy.emplace_back("Dummy");
        }
    }

    cout << "########### Gate Seq With Dummy ###########" << endl;
    for(const auto &gate : Poly_Sequence_With_Dummy){
        cout << gate << " ";
    }
    cout << endl;

    // Init the layout
    // Map gate to place the source and drain
    unordered_map<string, vector<FinFET *>> N_FinFET_Poly_Map_Copy(N_FinFET_Poly_Map.begin(), N_FinFET_Poly_Map.end());
    unordered_map<string, vector<FinFET *>> P_FinFET_Poly_Map_Copy(P_FinFET_Poly_Map.begin(), P_FinFET_Poly_Map.end());
    
    for(const auto &gate : Poly_Sequence_With_Dummy){
        if(gate != "Dummy"){
            Layout.push_back(make_pair(P_FinFET_Poly_Map_Copy[gate].front(), N_FinFET_Poly_Map_Copy[gate].front()));
            P_FinFET_Poly_Map_Copy[gate].erase(P_FinFET_Poly_Map_Copy[gate].begin());
            N_FinFET_Poly_Map_Copy[gate].erase(N_FinFET_Poly_Map_Copy[gate].begin());
        }
        else{
            Layout.push_back(make_pair(new FinFET(), new FinFET()));
        }
    }
    // Check if all vectors in the unordered maps have size 0
    for (const auto &entry : N_FinFET_Poly_Map_Copy) {
        assert(entry.second.size() == 0);
    }

    for (const auto &entry : P_FinFET_Poly_Map_Copy) {
        assert(entry.second.size() == 0);
    }

    for(const auto &pair : Layout){
        FinFET *PMOS = pair.first;
        FinFET *NMOS = pair.second;
        if(PMOS->Name == "Dummy" && NMOS->Name == "Dummy") continue;
        assert(PMOS->Gate == NMOS->Gate);
        cout << PMOS->Gate << endl;
        cout << PMOS->Left_Diffusion_Pin << " " << PMOS->Gate << " " << PMOS->Right_Diffusion_Pin << endl;
        cout << NMOS->Left_Diffusion_Pin << " " << NMOS->Gate << " " << NMOS->Right_Diffusion_Pin << endl;
    }
}

double Standard_Cell::Calculate_HPWL(){
    double hpwl = 0;
    double x_coordinate_offset = 0;
    size_t finfet_count = 0;
    for(const auto &pair : Layout){
        FinFET *PMOS = pair.first;
        FinFET *NMOS = pair.second;
        if(PMOS->Name == "Dummy" && NMOS->Name == "Dummy"){
            PMOS->Gate_X_Coordinate = x_coordinate_offset + (GATE_WIDTH + GATE_SPACING) * 2;
            NMOS->Gate_X_Coordinate = x_coordinate_offset + (GATE_WIDTH + GATE_SPACING) * 2;
            x_coordinate_offset = x_coordinate_offset + (GATE_WIDTH + GATE_SPACING) * 2;
        }
        else{
            assert(PMOS->Type != Dummy);
            assert(NMOS->Type != Dummy);
            if(finfet_count == 0){
                PMOS->Gate_X_Coordinate = GATE_ACTIVE_EXTENSION + GATE_WIDTH / 2;
                NMOS->Gate_X_Coordinate = GATE_ACTIVE_EXTENSION + GATE_WIDTH / 2;
                x_coordinate_offset = GATE_ACTIVE_EXTENSION + GATE_WIDTH / 2;
            }
            else{
                PMOS->Gate_X_Coordinate = x_coordinate_offset + GATE_SPACING + GATE_WIDTH;
                NMOS->Gate_X_Coordinate = x_coordinate_offset + GATE_SPACING + GATE_WIDTH;
                x_coordinate_offset = x_coordinate_offset + GATE_SPACING + GATE_WIDTH;
            }
            finfet_count++;
        }
    }

    for(const auto &pair : FinFET_Pin_Map){
        string pin_name = pair.first;
        double min_x = 0;
        double min_y = 0;
        double max_x = INT_MAX;
        double max_y = INT_MAX;
        for(const auto finfet : pair.second){
            if(finfet->Type == N_Type){
                if(pin_name == finfet->Left_Diffusion_Pin && pin_name == finfet->Right_Diffusion_Pin){
                    min_x = min({min_x, finfet->Gate_X_Coordinate - GATE_WIDTH / 2 - });
                }
                else if(pin)
            }
            else if(finfet->Type == P_Type){

            }
            else abort();
        }
    }
    
    return hpwl;
}