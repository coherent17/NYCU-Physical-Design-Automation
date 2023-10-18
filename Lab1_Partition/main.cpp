#include "FM.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
    ifstream fin1(argv[1]);
    ifstream fin2(argv[1]);
    ofstream fout(argv[2]);
    FM *fm1 = new FM();
    FM *fm2 = new FM();

    // Create two threads to run fm1 and fm2 in parallel
    thread thread1([&]() {
        fm1->Parser(fin1);
        fm1->Run();
    });

    std::thread thread2([&]() {
        fm2->Parser(fin2);
        fm2->Run();
    });

    // Wait for both threads to finish
    thread1.join();
    thread2.join();
    
    if(fm1->Get_Cut() < fm2->Get_Cut()){
        fm1->Dump(fout);
    }
    else{
        fm2->Dump(fout);
    }
    delete fm1;
    delete fm2;
    return 0;
}