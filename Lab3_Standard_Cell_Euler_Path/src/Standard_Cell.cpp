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
        type = (body == "VSS") ? N_Type : P_Type; 
        regex_search(width_str, width_match, Float_Pattern);
        regex_search(length_str, length_match, Float_Pattern);
        width = stod(width_match.str());
        length = stod(length_match.str());
        FinFET *finfet = new FinFET(name, type, drain, gate, source, width, length);
        FinFETs.emplace_back(finfet);
        if(PRINT_FINFET_INFO){
            cout << *finfet << endl;
        }
    }
    fin.close();
}

void Standard_Cell::Construct_Graph(){
    for(const auto &finfet : FinFETs){
        if(finfet->Type == N_Type){
            Nmos_Graph.Add_Edge(finfet->Drain, finfet->Source, finfet->Gate);
        }
        else if(finfet->Type == P_Type){
            Pmos_Graph.Add_Edge(finfet->Drain, finfet->Source, finfet->Gate);
        }
        else abort();
        
    }
    cout << "NMOS:" << endl << Nmos_Graph << endl;
    cout << Nmos_Graph.Is_Connected_Graph() << endl;
    cout << Nmos_Graph.Has_Euler_Path() << endl;

    cout << "PMOS:" << endl << Pmos_Graph << endl;
    cout << Pmos_Graph.Is_Connected_Graph() << endl;
    cout << Pmos_Graph.Has_Euler_Path() << endl;
}