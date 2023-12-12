#include "FinFET.h"

FinFET::FinFET(const string &name, const string &drain, const string &gate, const string &source, FinFET_Type type, double width, double length):
    Name(name), 
    Drain(drain), 
    Gate(gate), 
    Source(source), 
    Type(type), 
    Width(width), 
    Length(length),
    Gate_X_Coordinate(0),
    Is_Dummy(type == Dummy),
    Left_Diffusion_Pin(drain),
    Right_Diffusion_Pin(source),
    Left_Diffusion_X_Coordinate(0),
    Right_Diffusion_X_Coordinate(0)
{
    ;
}

FinFET::FinFET():
    Name("Dummy"), 
    Drain("UNSET"), 
    Gate("UNSET"), 
    Source("UNSET"), 
    Type(Dummy), 
    Width(0.0), 
    Length(0.0),
    Gate_X_Coordinate(0),
    Is_Dummy(true),
    Left_Diffusion_Pin(""),
    Right_Diffusion_Pin(""),
    Left_Diffusion_X_Coordinate(0),
    Right_Diffusion_X_Coordinate(0)
{
    ;
}

FinFET::~FinFET() {
    ;
}

ostream &operator<<(ostream &out, const FinFET &finfet) {
    out << "Name: " << finfet.Name << "\n";
    out << "Drain: " << finfet.Drain << "\n";
    out << "Gate: " << finfet.Gate << "\n";
    out << "Source: " << finfet.Source << "\n";
    out << "Type: ";
    switch (finfet.Type) {
        case N_Type:
            out << "N_Type";
            break;
        case P_Type:
            out << "P_Type";
            break;
        case Dummy:
            out << "Dummy";
            break;
    }
    out << "\nWidth: " << finfet.Width << "\n";
    out << "Length: " << finfet.Length << "\n";
    out << "Gate X Coordinate: " << finfet.Gate_X_Coordinate << "\n";
    out << "Is Dummy: " << (finfet.Is_Dummy ? "Yes" : "No") << "\n";
    return out;
}