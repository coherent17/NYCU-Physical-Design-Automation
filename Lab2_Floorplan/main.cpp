#include "Floorplan.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    Floorplan *fp_manager = new Floorplan();
    fp_manager->Parser(fin);
    fp_manager->Dump(fout);
    delete fp_manager;
    return 0;
}