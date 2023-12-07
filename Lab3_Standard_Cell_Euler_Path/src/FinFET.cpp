#include "FinFET.h"

FinFET::FinFET(const string &name, const string &drain, const string &gate, const string &source, FinFET_Type type, double width, double length):
    Name(name),
    Drain(drain),
    Gate(gate),
    Source(source),
    Type(type),
    Width(width),
    Length(length),
    Swap_Drain_Source(false),
    Is_Dummy(false)
{
    ;
}

FinFET::FinFET(bool is_dummy):
    Name("Dummy"),
    Drain("Dummy_D"),
    Gate("Dummy_G"),
    Source("Dummy_S"),
    Type(Dummy_Type),
    Width(0),
    Length(0),
    Swap_Drain_Source(false),
    Is_Dummy(true)
{

}

FinFET::~FinFET(){
    ;
}

void FinFET::Swap_DS(){
    Swap_Drain_Source = !Swap_Drain_Source;
    swap(Drain, Source);
}

ostream &operator<<(ostream &out, const FinFET &finfet){
    if(finfet.Is_Dummy){
        out << "Dummy" << endl;
        return out;
    }

    out << finfet.Name << endl;
    out << "\tDrain: " << finfet.Drain << endl;
    out << "\tGate: " << finfet.Gate << endl;
    out << "\tSorce: " << finfet.Source << endl;
    out << "\tType: " << ((finfet.Type == N_Type) ? "N" : "P") << endl;
    out << "\tWidth: " << finfet.Width << endl;
    out << "\tLength: " << finfet.Length << endl;
    out << "\tOrder: " << ((finfet.Swap_Drain_Source == false) ? finfet.Drain + " " + finfet.Gate + " " + finfet.Source : finfet.Source + " " + finfet.Gate + " " + finfet.Drain) << endl; 
    return out;
}