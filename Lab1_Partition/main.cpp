#include "FM.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    FM *fm = new FM();
    fm->Parser(fin);
    fm->Run();
    fm->Dump(fout);
    delete fm;
    return 0;
}