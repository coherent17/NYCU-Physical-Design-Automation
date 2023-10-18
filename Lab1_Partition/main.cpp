#include "FM.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
    ifstream fin1(argv[1]);
    ifstream fin2(argv[1]);
    ifstream fin3(argv[1]);
    ifstream fin4(argv[1]);
    ifstream fin5(argv[1]);
    ifstream fin6(argv[1]);
    ifstream fin7(argv[1]);
    ifstream fin8(argv[1]);
    ofstream fout(argv[2]);

    FM *fm1 = new FM();
    FM *fm2 = new FM();
    FM *fm3 = new FM();
    FM *fm4 = new FM();
    FM *fm5 = new FM();
    FM *fm6 = new FM();
    FM *fm7 = new FM();
    FM *fm8 = new FM();

    // Create two threads to run fm1 and fm2 in parallel
    thread thread1([&]() {
        fm1->Parser(fin1);
        fm1->Run();
    });

    thread thread2([&]() {
        fm2->Parser(fin2);
        fm2->Run();
    });

    thread thread3([&]() {
        fm3->Parser(fin3);
        fm3->Run();
    });

    thread thread4([&]() {
        fm4->Parser(fin4);
        fm4->Run();
    });

    thread thread5([&]() {
        fm5->Parser(fin5);
        fm5->Run();
    });
        thread thread6([&]() {
        fm6->Parser(fin6);
        fm6->Run();
    });
        thread thread7([&]() {
        fm7->Parser(fin7);
        fm7->Run();
    });
        thread thread8([&]() {
        fm8->Parser(fin8);
        fm8->Run();
    });

    // Wait for both threads to finish
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();

    // Compare the results and dump the one with the smaller cut
    int fm1_cut = fm1->Get_Best_Cut();
    int fm2_cut = fm2->Get_Best_Cut();
    int fm3_cut = fm3->Get_Best_Cut();
    int fm4_cut = fm4->Get_Best_Cut();
    int fm5_cut = fm5->Get_Best_Cut();
    int fm6_cut = fm6->Get_Best_Cut();
    int fm7_cut = fm7->Get_Best_Cut();
    int fm8_cut = fm8->Get_Best_Cut();

    cout << fm1_cut << " " << fm2_cut << " " << fm3_cut << " " << fm4_cut << " " << fm5_cut << " " << fm6_cut << " " << fm7_cut << " " << fm8_cut << endl;
    int min_cut = std::min({fm1_cut, fm2_cut, fm3_cut, fm4_cut, fm5_cut, fm6_cut, fm7_cut, fm8_cut});
    if (min_cut == fm1_cut) {
        fm1->Dump(fout);
    } else if (min_cut == fm2_cut) {
        fm2->Dump(fout);
    } else if (min_cut == fm3_cut) {
        fm3->Dump(fout);
    } else if(min_cut == fm4_cut){
        fm4->Dump(fout);
    }else if(min_cut == fm5_cut){
        fm5->Dump(fout);
    }else if(min_cut == fm6_cut){
        fm6->Dump(fout);
    }else if(min_cut == fm7_cut){
        fm7->Dump(fout);
    }else if(min_cut == fm8_cut){
        fm8->Dump(fout);
    }else{
        abort();
    }

    delete fm1;
    delete fm2;
    delete fm3;
    delete fm4;
    delete fm5;
    delete fm6;
    delete fm7;
    delete fm8;
    return 0;
}