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
    ifstream fin9(argv[1]);
    ifstream fin10(argv[1]);
    ifstream fin11(argv[1]);
    ifstream fin12(argv[1]);
    ifstream fin13(argv[1]);
    ifstream fin14(argv[1]);
    ifstream fin15(argv[1]);
    ifstream fin16(argv[1]);
    ofstream fout(argv[2]);

    FM *fm1 = new FM();
    FM *fm2 = new FM();
    FM *fm3 = new FM();
    FM *fm4 = new FM();
    FM *fm5 = new FM();
    FM *fm6 = new FM();
    FM *fm7 = new FM();
    FM *fm8 = new FM();
    FM *fm9 = new FM();
    FM *fm10 = new FM();
    FM *fm11 = new FM();
    FM *fm12 = new FM();
    FM *fm13 = new FM();
    FM *fm14 = new FM();
    FM *fm15 = new FM();
    FM *fm16 = new FM();

    // Create threads to run fm in parallel
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
    thread thread9([&]() {
        fm9->Parser(fin9);
        fm9->Run();
    });

    thread thread10([&]() {
        fm10->Parser(fin10);
        fm10->Run();
    });

    thread thread11([&]() {
        fm11->Parser(fin11);
        fm11->Run();
    });

    thread thread12([&]() {
        fm12->Parser(fin12);
        fm12->Run();
    });

    thread thread13([&]() {
        fm13->Parser(fin13);
        fm13->Run();
    });
        thread thread14([&]() {
        fm14->Parser(fin14);
        fm14->Run();
    });
        thread thread15([&]() {
        fm15->Parser(fin15);
        fm15->Run();
    });
        thread thread16([&]() {
        fm16->Parser(fin16);
        fm16->Run();
    });

    // Wait for all threads to finish
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();
    thread9.join();
    thread10.join();
    thread11.join();
    thread12.join();
    thread13.join();
    thread14.join();
    thread15.join();
    thread16.join();

    // Compare the results and dump the one with the smaller cut
    int fm1_cut = fm1->Get_Best_Cut();
    int fm2_cut = fm2->Get_Best_Cut();
    int fm3_cut = fm3->Get_Best_Cut();
    int fm4_cut = fm4->Get_Best_Cut();
    int fm5_cut = fm5->Get_Best_Cut();
    int fm6_cut = fm6->Get_Best_Cut();
    int fm7_cut = fm7->Get_Best_Cut();
    int fm8_cut = fm8->Get_Best_Cut();
    int fm9_cut = fm9->Get_Best_Cut();
    int fm10_cut = fm10->Get_Best_Cut();
    int fm11_cut = fm11->Get_Best_Cut();
    int fm12_cut = fm12->Get_Best_Cut();
    int fm13_cut = fm13->Get_Best_Cut();
    int fm14_cut = fm14->Get_Best_Cut();
    int fm15_cut = fm15->Get_Best_Cut();
    int fm16_cut = fm16->Get_Best_Cut();

    //cout << fm1_cut << " " << fm2_cut << " " << fm3_cut << " " << fm4_cut << " " << fm5_cut << " " << fm6_cut << " " << fm7_cut << " " << fm8_cut << endl;
    //cout << fm9_cut << " " << fm10_cut << " " << fm11_cut << " " << fm12_cut << " " << fm13_cut << " " << fm14_cut << " " << fm15_cut << " " << fm16_cut << endl;
    int min_cut = std::min({fm1_cut, fm2_cut, fm3_cut, fm4_cut, fm5_cut, fm6_cut, fm7_cut, fm8_cut, fm9_cut, fm10_cut, fm11_cut, fm12_cut, fm13_cut, fm14_cut, fm15_cut, fm16_cut});
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
    }else if (min_cut == fm9_cut) {
        fm9->Dump(fout);
    } else if (min_cut == fm10_cut) {
        fm10->Dump(fout);
    } else if (min_cut == fm11_cut) {
        fm11->Dump(fout);
    } else if(min_cut == fm12_cut){
        fm12->Dump(fout);
    }else if(min_cut == fm13_cut){
        fm13->Dump(fout);
    }else if(min_cut == fm14_cut){
        fm14->Dump(fout);
    }else if(min_cut == fm15_cut){
        fm15->Dump(fout);
    }else if(min_cut == fm16_cut){
        fm16->Dump(fout);
    }
    else{
        abort();
    }
    return 0;
}