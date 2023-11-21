#include "Floorplan_Manager.h"
#include <bits/stdc++.h>
#include "Floorplan.h"
using namespace std;

// int main(int argc, char *argv[]){
//     ifstream fin(argv[1]);
//     ofstream fout(argv[2]);
//     Floorplan fp_manager(false);
//     fp_manager.Parser(fin);
//     fp_manager.Run();
//     fp_manager.Dump(fout);
//     return 0;
// }

// For multi-therad implementation
int main(int argc, char *argv[]){
    Floorplan_Manager fp_manager(argv[1], argv[2]);
    fp_manager.Run_Thread();
    return 0;
}