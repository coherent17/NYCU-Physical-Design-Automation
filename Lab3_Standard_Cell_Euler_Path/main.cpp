#include <bits/stdc++.h>
#include "Standard_Cell.h"
using namespace std;

int main(int argc, char *argv[]){
    ifstream Spice_File(argv[1]);
    Standard_Cell standard_cell;
    standard_cell.Parse_Spice(Spice_File);
    standard_cell.Init_Sequence();
    return 0;
}