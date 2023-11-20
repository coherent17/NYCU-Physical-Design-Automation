#include "Floorplan.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    Floorplan fp_manager;
    fp_manager.Parser(fin);
    fp_manager.Run();
    fp_manager.Dump(fout);
    return 0;
}