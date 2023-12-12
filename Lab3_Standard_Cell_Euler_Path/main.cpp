#include <bits/stdc++.h>
#include "Standard_Cell.h"
using namespace std;

int main(int argc, char *argv[]){
    ifstream Spice_File(argv[1]);
    ofstream Rpt_File(argv[2]);
    Standard_Cell standard_cell;
    standard_cell.Spice_Parser(Spice_File);
    standard_cell.Run();
    standard_cell.Dump(Rpt_File);
    return 0;
}