#include "FinFET.h"

FinFET::FinFET(const string &name, FinFET_Type type, const string &drain, const string &gate, const string &source, double width, double length):
    Name(name),
    Type(type),
    Drain(drain),
    Gate(gate),
    Source(source),
    Width(width),
    Length(length)
{
    ;
}

FinFET::~FinFET(){
    ;
}

ostream &operator<<(ostream &out, const FinFET &finfet){
    out << finfet.Name << endl;
    out << "\tType: " << ((finfet.Type == N_Type) ? "NMOS" : "PMOS") << endl;
    out << "\tDrain: " << finfet.Drain << endl;
    out << "\tGate: " << finfet.Gate << endl;
    out << "\tSorce: " << finfet.Source << endl;
    out << "\tWidth: " << finfet.Width << endl;
    out << "\tLength: " << finfet.Length << endl;
    return out;
}