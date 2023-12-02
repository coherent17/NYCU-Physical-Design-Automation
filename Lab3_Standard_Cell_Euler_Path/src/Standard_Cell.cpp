#include "Standard_Cell.h"

// Constructor & Destructor
Standard_Cell::Standard_Cell(){
    ;
}

Standard_Cell::~Standard_Cell(){
    ;
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
        cout << line << endl;
        cout << *finfet << endl;
    }
    fin.close();
}