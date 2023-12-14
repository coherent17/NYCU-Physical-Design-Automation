#include "Standard_Cell.h"

Standard_Cell::Standard_Cell() : 
    Num_FinFETs(0),
    Temperature(ANNEALING_TEMPERATURE),
    HPWL(DBL_MAX)
{
    rng = new Random_Number_Generator();
    StartTime = chrono::steady_clock::now();
}

Standard_Cell::~Standard_Cell(){
    for(FinFET *finfet : FinFETs){
        delete finfet;
    }
    delete rng;
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
        FinFET *finfet = new FinFET(name.substr(1), drain, gate, source, type, width, length);
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

    // cout << "########### Pin Map ###########" << endl;
    // for(const auto &pair : FinFET_Pin_Map){
    //     cout << pair.first << "->";
    //     for(const auto &finfet : pair.second){
    //         cout << finfet->Name << " ";
    //     }
    //     cout << endl;
    // }

    // cout << "########### N Poly Map ###########" << endl;
    // for(const auto &pair : N_FinFET_Poly_Map){
    //     cout << pair.first << "->";
    //     for(const auto &finfet : pair.second){
    //         cout << finfet->Name << " ";
    //     }
    //     cout << endl;
    // }
    
    // cout << "########### P Poly Map ###########" << endl;
    // for(const auto &pair : P_FinFET_Poly_Map){
    //     cout << pair.first << "->";
    //     for(const auto &finfet : pair.second){
    //         cout << finfet->Name << " ";
    //     }
    //     cout << endl;
    // }
    P_Active_Width = P_FinFETs.front()->Width;
    N_Active_Width = N_FinFETs.front()->Width;
    N_Active_Center_Height = N_Active_Width / 2.0;
    P_Active_Center_Height = N_Active_Width + ACTIVE_VERTICAL_SPACING + P_Active_Width / 2.0;

    for(size_t i = 0; i < Num_FinFETs * 2; i++){
        Dummy_FinFET_Garbage_Collector.emplace_back(make_pair(new FinFET(), new FinFET()));
    }
}

void Standard_Cell::Dump(ofstream &fout){
    fout << HPWL << endl;
    
    // Dummy Insertion
    list<pair<FinFET *, FinFET *>> Layout_Copy = Layout;
    for(auto it = Layout_Copy.begin(); it != Layout_Copy.end(); ++it){
        if(next(it) == Layout_Copy.end()) break;
        it = Layout_Copy.insert(next(it), make_pair(new FinFET(), new FinFET()));
    }

    // Remove Dummy
    for(auto it = Layout_Copy.begin(); it != Layout_Copy.end();){
        FinFET *PMOS = it->first;
        FinFET *NMOS = it->second;

        if(PMOS->Type == Dummy && NMOS->Type == Dummy){
            auto prev_it = prev(it);
            auto next_it = next(it);
            FinFET *prev_PMOS = prev_it->first;
            FinFET *next_PMOS = next_it->first;
            FinFET *prev_NMOS = prev_it->second;
            FinFET *next_NMOS = next_it->second;
            if(prev_PMOS->Type == Dummy || next_PMOS->Type == Dummy) continue;
            assert(prev_PMOS->Type == P_Type && prev_NMOS->Type == N_Type);
            assert(next_PMOS->Type == P_Type && next_NMOS->Type == N_Type);
            bool P_Match = prev_PMOS->Right_Diffusion_Pin == next_PMOS->Left_Diffusion_Pin;
            bool N_Match = prev_NMOS->Right_Diffusion_Pin == next_NMOS->Left_Diffusion_Pin;
            if(P_Match && N_Match){
                delete PMOS;
                delete NMOS;
                it = Layout_Copy.erase(it);
            }
        }
        it++;
    }

    for(const auto &pair : Layout_Copy){
        FinFET *PMOS = pair.first;
        fout << PMOS->Name << " ";
    }
    fout << endl;

    for(auto it = Layout_Copy.begin(); it != Layout_Copy.end(); ++it){
        FinFET *PMOS = (*it).first;
        if(it == Layout_Copy.begin()){
            fout << PMOS->Left_Diffusion_Pin << " " << PMOS->Gate << " " << PMOS->Right_Diffusion_Pin << " ";
            continue;
        }
        else if(PMOS->Type == Dummy){
            fout << "Dummy" << " ";
            continue;
        }
        auto prev_it = prev(it);
        FinFET *prev_PMOS = (*prev_it).first;
        FinFET *prev_NMOS = (*prev_it).second;
        assert((prev_PMOS->Type == Dummy && prev_NMOS->Type == Dummy) || (prev_PMOS->Type == P_Type && prev_NMOS->Type == N_Type));
        if(prev_PMOS->Type == Dummy){
            fout << PMOS->Left_Diffusion_Pin << " " << PMOS->Gate << " " << PMOS->Right_Diffusion_Pin << " ";
        }
        else{
            fout << PMOS->Gate << " " << PMOS->Right_Diffusion_Pin << " ";
        }
    }
    fout << endl;

    for(const auto &pair : Layout_Copy){
        FinFET *NMOS = pair.second;
        fout << NMOS->Name << " ";
    }
    fout << endl;

    for(auto it = Layout_Copy.begin(); it != Layout_Copy.end(); ++it){
        FinFET *NMOS = (*it).second;
        if(it == Layout_Copy.begin()){
            fout << NMOS->Left_Diffusion_Pin << " " << NMOS->Gate << " " << NMOS->Right_Diffusion_Pin << " ";
            continue;
        }
        else if(NMOS->Type == Dummy){
            fout << "Dummy" << " ";
            continue;
        }
        auto prev_it = prev(it);
        FinFET *prev_PMOS = (*prev_it).first;
        FinFET *prev_NMOS = (*prev_it).second;
        assert((prev_PMOS->Type == Dummy && prev_NMOS->Type == Dummy) || (prev_PMOS->Type == P_Type && prev_NMOS->Type == N_Type));
        if(prev_NMOS->Type == Dummy){
            fout << NMOS->Left_Diffusion_Pin << " " << NMOS->Gate << " " << NMOS->Right_Diffusion_Pin << " ";
        }
        else{
            fout << NMOS->Gate << " " << NMOS->Right_Diffusion_Pin << " ";
        }
    }
    fout << endl;
}

void Standard_Cell::Run(){
    Init_Poly_Sequence();
    HPWL = Calculate_HPWL();
    Simulated_Annealing();
}

double Standard_Cell::Get_HPWL(){
    return HPWL;
}

void Standard_Cell::Init_Poly_Sequence(){
    vector<string> Poly_Sequence;
    vector<string> Poly_Sequence_With_Dummy;

    for(const auto &finfet : N_FinFETs){
        Poly_Sequence.emplace_back(finfet->Gate);
    }
    // Should add these 2 line when release
    srand(time(nullptr));
    random_shuffle(Poly_Sequence.begin(), Poly_Sequence.end());
    // cout << "########### Gate Seq ###########" << endl;
    // for(const auto &gate : Poly_Sequence){
    //     cout << gate << " ";
    // }
    // cout << endl;

    // Init the layout
    // Map gate to place the source and drain
    unordered_map<string, vector<FinFET *>> N_FinFET_Poly_Map_Copy(N_FinFET_Poly_Map.begin(), N_FinFET_Poly_Map.end());
    unordered_map<string, vector<FinFET *>> P_FinFET_Poly_Map_Copy(P_FinFET_Poly_Map.begin(), P_FinFET_Poly_Map.end());
    
    for(auto &pair : N_FinFET_Poly_Map_Copy){
        if(pair.second.size() > 1){
            random_shuffle(pair.second.begin(), pair.second.end());
        }
    }

    for(auto &pair : P_FinFET_Poly_Map_Copy){
        if(pair.second.size() > 1){
            random_shuffle(pair.second.begin(), pair.second.end());
        }
    }

    for(const auto &gate : Poly_Sequence){
        Layout.push_back(make_pair(P_FinFET_Poly_Map_Copy[gate].front(), N_FinFET_Poly_Map_Copy[gate].front()));
        P_FinFET_Poly_Map_Copy[gate].erase(P_FinFET_Poly_Map_Copy[gate].begin());
        N_FinFET_Poly_Map_Copy[gate].erase(N_FinFET_Poly_Map_Copy[gate].begin());
    }

    // Check if all vectors in the unordered maps have size 0
    for (const auto &entry : N_FinFET_Poly_Map_Copy) {
        assert(entry.second.size() == 0);
    }

    for (const auto &entry : P_FinFET_Poly_Map_Copy) {
        assert(entry.second.size() == 0);
    }

    // Check for the init Layout list
    // for(const auto &pair : Layout){
    //     FinFET *PMOS = pair.first;
    //     FinFET *NMOS = pair.second;
    //     assert(PMOS->Gate == NMOS->Gate);
    //     cout << PMOS->Gate << endl;
    //     cout << PMOS->Left_Diffusion_Pin << " " << PMOS->Gate << " " << PMOS->Right_Diffusion_Pin << endl;
    //     cout << NMOS->Left_Diffusion_Pin << " " << NMOS->Gate << " " << NMOS->Right_Diffusion_Pin << endl;
    // }
}

double Standard_Cell::Calculate_HPWL(){
    // Dummy Insertion
    list<pair<FinFET *, FinFET *>> Layout_Copy = Layout;
    for(auto it = Layout_Copy.begin(); it != Layout_Copy.end(); ++it){
        if(next(it) == Layout_Copy.end()) break;
        pair<FinFET *, FinFET *> Dummy_Pair = Dummy_FinFET_Garbage_Collector.front();
        Dummy_FinFET_Garbage_Collector.erase(Dummy_FinFET_Garbage_Collector.begin());
        it = Layout_Copy.insert(next(it), make_pair(Dummy_Pair.first, Dummy_Pair.second));
    }

    // Remove Dummy
    for(auto it = Layout_Copy.begin(); it != Layout_Copy.end();){
        FinFET *PMOS = it->first;
        FinFET *NMOS = it->second;

        if(PMOS->Type == Dummy && NMOS->Type == Dummy){
            auto prev_it = prev(it);
            auto next_it = next(it);
            FinFET *prev_PMOS = prev_it->first;
            FinFET *next_PMOS = next_it->first;
            FinFET *prev_NMOS = prev_it->second;
            FinFET *next_NMOS = next_it->second;
            if(prev_PMOS->Type == Dummy || next_PMOS->Type == Dummy) continue;
            assert(prev_PMOS->Type == P_Type && prev_NMOS->Type == N_Type);
            assert(next_PMOS->Type == P_Type && next_NMOS->Type == N_Type);
            bool P_Match = prev_PMOS->Right_Diffusion_Pin == next_PMOS->Left_Diffusion_Pin;
            bool N_Match = prev_NMOS->Right_Diffusion_Pin == next_NMOS->Left_Diffusion_Pin;
            if(P_Match && N_Match){
                Dummy_FinFET_Garbage_Collector.emplace_back(make_pair(PMOS, NMOS));
                it = Layout_Copy.erase(it);
            }
        }
        it++;
    }

    // Calculate pin coordinate
    for(auto it = Layout_Copy.begin(); it != Layout_Copy.end(); ++it){
        FinFET *PMOS = it->first;
        FinFET *NMOS = it->second;
        
        // Dummy FinFET
        if(PMOS->Type == Dummy && NMOS->Type == Dummy) continue;

        // Left Edge: Extend the left active area
        if(it == Layout_Copy.begin()){
            PMOS->Gate_X_Coordinate = GATE_ACTIVE_EXTENSION + GATE_WIDTH / 2.0;
            NMOS->Gate_X_Coordinate = GATE_ACTIVE_EXTENSION + GATE_WIDTH / 2.0;
            PMOS->Left_Diffusion_X_Coordinate = PMOS->Gate_X_Coordinate - (GATE_WIDTH + GATE_ACTIVE_EXTENSION) / 2.0;
            NMOS->Left_Diffusion_X_Coordinate = NMOS->Gate_X_Coordinate - (GATE_WIDTH + GATE_ACTIVE_EXTENSION) / 2.0;
            PMOS->Right_Diffusion_X_Coordinate = PMOS->Gate_X_Coordinate + (GATE_WIDTH + GATE_SPACING) / 2.0;
            NMOS->Right_Diffusion_X_Coordinate = NMOS->Gate_X_Coordinate + (GATE_WIDTH + GATE_SPACING) / 2.0;
        }

        // Right Edge: Expand the right active area
        else if(next(it) == Layout_Copy.end()){
            auto prev_it = prev(it);
            FinFET *prev_PMOS = prev_it->first;
            FinFET *prev_NMOS = prev_it->second;
            if(prev_PMOS->Type == Dummy && prev_NMOS->Type == Dummy){
                auto prev_prev_it = prev(prev_it);
                FinFET *prev_prev_PMOS = prev_prev_it->first;
                FinFET *prev_prev_NMOS = prev_prev_it->second;
                assert(prev_prev_PMOS->Gate_X_Coordinate == prev_prev_NMOS->Gate_X_Coordinate);
                double prev_finfet_poly_x = prev_prev_PMOS->Gate_X_Coordinate;
                PMOS->Gate_X_Coordinate = prev_finfet_poly_x + (GATE_SPACING + GATE_WIDTH) * 3.0;
                NMOS->Gate_X_Coordinate = prev_finfet_poly_x + (GATE_SPACING + GATE_WIDTH) * 3.0;
                PMOS->Left_Diffusion_X_Coordinate = PMOS->Gate_X_Coordinate - (GATE_WIDTH + GATE_SPACING) / 2.0;
                NMOS->Left_Diffusion_X_Coordinate = NMOS->Gate_X_Coordinate - (GATE_WIDTH + GATE_SPACING) / 2.0;
                PMOS->Right_Diffusion_X_Coordinate = PMOS->Gate_X_Coordinate + (GATE_WIDTH + GATE_ACTIVE_EXTENSION) / 2.0;
                NMOS->Right_Diffusion_X_Coordinate = NMOS->Gate_X_Coordinate + (GATE_WIDTH + GATE_ACTIVE_EXTENSION) / 2.0;
            }
            else{
                double prev_finfet_poly_x = prev_PMOS->Gate_X_Coordinate;
                PMOS->Gate_X_Coordinate = prev_finfet_poly_x + GATE_SPACING + GATE_WIDTH;
                NMOS->Gate_X_Coordinate = prev_finfet_poly_x + GATE_SPACING + GATE_WIDTH;
                PMOS->Left_Diffusion_X_Coordinate = PMOS->Gate_X_Coordinate - (GATE_WIDTH + GATE_SPACING) / 2.0;
                NMOS->Left_Diffusion_X_Coordinate = NMOS->Gate_X_Coordinate - (GATE_WIDTH + GATE_SPACING) / 2.0;
                PMOS->Right_Diffusion_X_Coordinate = PMOS->Gate_X_Coordinate + (GATE_WIDTH + GATE_ACTIVE_EXTENSION) / 2.0;
                NMOS->Right_Diffusion_X_Coordinate = NMOS->Gate_X_Coordinate + (GATE_WIDTH + GATE_ACTIVE_EXTENSION) / 2.0;
            }
        }

        // General case
        else{
            auto prev_it = prev(it);
            FinFET *prev_PMOS = (*prev_it).first;
            FinFET *prev_NMOS = (*prev_it).second;
            if(prev_PMOS->Type == Dummy && prev_NMOS->Type == Dummy){
                auto prev_prev_it = prev(prev_it);
                FinFET *prev_prev_PMOS = (*prev_prev_it).first;
                FinFET *prev_prev_NMOS = (*prev_prev_it).second;
                assert(prev_prev_PMOS->Gate_X_Coordinate == prev_prev_NMOS->Gate_X_Coordinate);
                double prev_finfet_poly_x = prev_prev_PMOS->Gate_X_Coordinate;
                PMOS->Gate_X_Coordinate = prev_finfet_poly_x + (GATE_SPACING + GATE_WIDTH) * 3.0;
                NMOS->Gate_X_Coordinate = prev_finfet_poly_x + (GATE_SPACING + GATE_WIDTH) * 3.0;
                PMOS->Left_Diffusion_X_Coordinate = PMOS->Gate_X_Coordinate - (GATE_WIDTH + GATE_SPACING) / 2.0;
                NMOS->Left_Diffusion_X_Coordinate = NMOS->Gate_X_Coordinate - (GATE_WIDTH + GATE_SPACING) / 2.0;
                PMOS->Right_Diffusion_X_Coordinate = PMOS->Gate_X_Coordinate + (GATE_WIDTH + GATE_SPACING) / 2.0;
                NMOS->Right_Diffusion_X_Coordinate = NMOS->Gate_X_Coordinate + (GATE_WIDTH + GATE_SPACING) / 2.0;
            }
            else{
                double prev_finfet_poly_x = prev_PMOS->Gate_X_Coordinate;
                PMOS->Gate_X_Coordinate = prev_finfet_poly_x + GATE_SPACING + GATE_WIDTH;
                NMOS->Gate_X_Coordinate = prev_finfet_poly_x + GATE_SPACING + GATE_WIDTH;
                PMOS->Left_Diffusion_X_Coordinate = PMOS->Gate_X_Coordinate - (GATE_WIDTH + GATE_SPACING) / 2.0;
                NMOS->Left_Diffusion_X_Coordinate = NMOS->Gate_X_Coordinate - (GATE_WIDTH + GATE_SPACING) / 2.0;
                PMOS->Right_Diffusion_X_Coordinate = PMOS->Gate_X_Coordinate + (GATE_WIDTH + GATE_SPACING) / 2.0;
                NMOS->Right_Diffusion_X_Coordinate = NMOS->Gate_X_Coordinate + (GATE_WIDTH + GATE_SPACING) / 2.0;
            }
        }
    }

    // Calculate hpwl for each net
    double hpwl = 0;
    for(const auto &pair : FinFET_Pin_Map){
        string pin_name = pair.first;
        double min_x = DBL_MAX;
        double min_y = P_Active_Center_Height;
        double max_x = 0;
        double max_y = N_Active_Center_Height;
        for(const auto &finfet : pair.second){
            assert((finfet->Type == N_Type || finfet->Type == P_Type) && "Invalid FinFET type");
            assert(pin_name == finfet->Left_Diffusion_Pin || pin_name == finfet->Right_Diffusion_Pin);
            if(pin_name == finfet->Left_Diffusion_Pin && pin_name == finfet->Right_Diffusion_Pin){
                min_x = min({min_x, finfet->Left_Diffusion_X_Coordinate, finfet->Right_Diffusion_X_Coordinate});
                max_x = max({max_x, finfet->Left_Diffusion_X_Coordinate, finfet->Right_Diffusion_X_Coordinate});
            }
            else if(pin_name == finfet->Left_Diffusion_Pin){
                min_x = min({min_x, finfet->Left_Diffusion_X_Coordinate});
                max_x = max({max_x, finfet->Left_Diffusion_X_Coordinate});
            }
            else if(pin_name == finfet->Right_Diffusion_Pin){
                min_x = min({min_x, finfet->Right_Diffusion_X_Coordinate});
                max_x = max({max_x, finfet->Right_Diffusion_X_Coordinate});
            }
            else abort();

            if(finfet->Type == N_Type){
                min_y = min({min_y, N_Active_Center_Height});
                max_y = max({max_y, N_Active_Center_Height});
            }
            else if(finfet->Type == P_Type){
                min_y = min({min_y, P_Active_Center_Height});
                max_y = max({max_y, P_Active_Center_Height});
            }
            else abort();
        }
        hpwl += (max_x - min_x) + (max_y - min_y);
    }

    for(auto it = Layout_Copy.begin(); it != Layout_Copy.end(); ++it){
        FinFET *PMOS = it->first;
        FinFET *NMOS = it->second;
        if(PMOS->Type == Dummy && NMOS->Type == Dummy){
            Dummy_FinFET_Garbage_Collector.emplace_back(make_pair(PMOS, NMOS));
        }
    }

    return hpwl;
}

void Standard_Cell::Simulated_Annealing(){
    bool Convergence_Flag = false;
    double previous_hpwl = HPWL;
    int Num_Consecutive_Temperature_Unchanged = 0;
    while(Temperature > TERMINATE_TEMPERATURE && !Convergence_Flag){
        for(size_t i = 0; i < STEPS_PER_TEMPERATURE; i++){
            int Which_Operation = rng->Generate_Random_Integer(3);
            bool sa_result;
            switch(Which_Operation){
                case OPERATION1:
                    sa_result = SA_Operation1();
                    //cout << ((sa_result == ACCEPT) ? "[M1]Accept " : "[M1]Reject ") << HPWL << endl;
                    break;
                case OPERATION2:
                    sa_result = SA_Operation2();
                    //cout << ((sa_result == ACCEPT) ? "[M2]Accept " : "[M2]Reject ") << HPWL << endl;
                    break;
                case OPERATION3:
                    sa_result = SA_Operation3();
                    //cout << ((sa_result == ACCEPT) ? "[M3]Accept " : "[M3]Reject ") << HPWL << endl;
                    break;
                case OPERATION4:
                    sa_result = SA_Operation4();
                    //cout << ((sa_result == ACCEPT) ? "[M4]Accept " : "[M4]Reject ") << HPWL << endl;
                    break;
                default:
                    abort();
            }
        }

        if(HPWL == previous_hpwl){
            Num_Consecutive_Temperature_Unchanged++;
            if(Num_Consecutive_Temperature_Unchanged >= MAX_CONSECUTIVE_TEMPERATURN_UNCHANGE){
                Convergence_Flag = true;
            }
        }
        else{
            Num_Consecutive_Temperature_Unchanged = 0;
            previous_hpwl = HPWL;
        }
        //cout << Temperature << " " << HPWL << endl;
        Temperature = (Temperature > CRITICAL_TEMPERATURE) ? Temperature * TEMPERATURE_DECREASING_FAST_RATE : Temperature * TEMPERATURE_DECREASING_SLOW_RATE;
    }
}

//Operations for simulated annealing
bool Standard_Cell::SA_Operation1(){
    size_t index = rng->Generate_Random_Integer(P_FinFETs.size() - 1);
    assert(index < P_FinFETs.size() && index >= 0);
    double new_hpwl;
    swap(P_FinFETs[index]->Left_Diffusion_Pin, P_FinFETs[index]->Right_Diffusion_Pin);
    new_hpwl = Calculate_HPWL();

    // Better Move
    if(new_hpwl <= HPWL){
        HPWL = new_hpwl;
        return ACCEPT;
    }

    // Worse but legal move
    else{
        double delta_hpwl = new_hpwl - HPWL;
        double r = rng->Generate_Random_Float();

        // Accept
        if(r < exp(-1 * delta_hpwl / Temperature)){
            HPWL = new_hpwl;
            return ACCEPT;
        }
        else{
            swap(P_FinFETs[index]->Left_Diffusion_Pin, P_FinFETs[index]->Right_Diffusion_Pin);
            HPWL = Calculate_HPWL();
            return REJECT;
        }
    }
}

bool Standard_Cell::SA_Operation2(){
    size_t index = rng->Generate_Random_Integer(N_FinFETs.size() - 1);
    assert(index < N_FinFETs.size() && index >= 0);
    double new_hpwl;
    swap(N_FinFETs[index]->Left_Diffusion_Pin, N_FinFETs[index]->Right_Diffusion_Pin);
    new_hpwl = Calculate_HPWL();

    // Better Move
    if(new_hpwl <= HPWL){
        HPWL = new_hpwl;
        return ACCEPT;
    }

    // Worse but legal move
    else{
        double delta_hpwl = new_hpwl - HPWL;
        double r = rng->Generate_Random_Float();

        // Accept
        if(r < exp(-1 * delta_hpwl / Temperature)){
            HPWL = new_hpwl;
            return ACCEPT;
        }
        else{
            swap(N_FinFETs[index]->Left_Diffusion_Pin, N_FinFETs[index]->Right_Diffusion_Pin);
            HPWL = Calculate_HPWL();
            return REJECT;
        }
    }
}

bool Standard_Cell::SA_Operation3(){
    size_t index1 = rng->Generate_Random_Integer(Layout.size() - 1);
    size_t index2 = rng->Generate_Random_Integer(Layout.size() - 1);
    
    double new_hpwl;
    auto it1 = Layout.begin();
    advance(it1, index1);
    auto it2 = Layout.begin();
    advance(it2, index2);
    if(it1->first->Type == Dummy || it2->first->Type == Dummy){
        return REJECT;
    }
    iter_swap(it1, it2);
    new_hpwl = Calculate_HPWL();

    // Better Move
    if(new_hpwl <= HPWL){
        HPWL = new_hpwl;
        return ACCEPT;
    }

    // Worse but legal move
    else{
        double delta_hpwl = new_hpwl - HPWL;
        double r = rng->Generate_Random_Float();

        // Accept
        if(r < exp(-1 * delta_hpwl / Temperature)){
            HPWL = new_hpwl;
            return ACCEPT;
        }
        else{
            iter_swap(it1, it2);
            HPWL = Calculate_HPWL();
            return REJECT;
        }
    }
}

bool Standard_Cell::SA_Operation4(){
    vector<string> multi_poly_names;
    for(const auto &pair : P_FinFET_Poly_Map){
        if(pair.second.size() > 1){
            multi_poly_names.emplace_back(pair.first);
        }
    }
    if(multi_poly_names.size() == 0) return REJECT;
    size_t index = rng->Generate_Random_Integer(multi_poly_names.size() - 1);
    string poly_name = multi_poly_names[index];
    const vector<FinFET *> &FinFET_vec = P_FinFET_Poly_Map[poly_name];
    size_t index1 = rng->Generate_Random_Integer(FinFET_vec.size() - 1);
    size_t index2 = rng->Generate_Random_Integer(FinFET_vec.size() - 1);
    if(index1 == index2) return REJECT;

    FinFET *PMOS1 = FinFET_vec[index1];
    FinFET *PMOS2 = FinFET_vec[index2];

    auto it1 = Layout.end();
    auto it2 = Layout.end();
    // Find positions of PMOS1 and PMOS2
    for (auto it = Layout.begin(); it != Layout.end(); ++it){
        if (it->first == PMOS1) {
            it1 = it;
            if (it2 != Layout.end())
                break;  // Break if both PMOS1 and PMOS2 are found
        }
        if (it->first == PMOS2) {
            it2 = it;
            if (it1 != Layout.end())
                break;  // Break if both PMOS1 and PMOS2 are found
        }
    }

    swap(it1->first, it2->first);
    double new_hpwl = Calculate_HPWL();

    // Better Move
    if(new_hpwl <= HPWL){
        HPWL = new_hpwl;
        return ACCEPT;
    }

    // Worse but legal move
    else{
        double delta_hpwl = new_hpwl - HPWL;
        double r = rng->Generate_Random_Float();

        // Accept
        if(r < exp(-1 * delta_hpwl / Temperature)){
            HPWL = new_hpwl;
            return ACCEPT;
        }
        else{
            swap(it1->first, it2->first);
            HPWL = Calculate_HPWL();
            return REJECT;
        }
    }
}