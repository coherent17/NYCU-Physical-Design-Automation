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
    ifstream fin17(argv[1]);
    ifstream fin18(argv[1]);
    ifstream fin19(argv[1]);
    ifstream fin20(argv[1]);
    ofstream fout(argv[2]);

    vector<FM *>fms;
    vector<size_t> cuts;
    FM *fm1 = new FM(Half_Bound);       fms.emplace_back(fm1);
    FM *fm2 = new FM(Half_Bound);       fms.emplace_back(fm2);
    FM *fm3 = new FM(Half_Bound);       fms.emplace_back(fm3);
    FM *fm4 = new FM(Half_Bound);       fms.emplace_back(fm4);
    FM *fm5 = new FM(Half_Bound);       fms.emplace_back(fm5);
    FM *fm6 = new FM(Half_Bound);       fms.emplace_back(fm6);
    FM *fm7 = new FM(Half_Bound);       fms.emplace_back(fm7);
    FM *fm8 = new FM(Half_Bound);       fms.emplace_back(fm8);
    FM *fm9 = new FM(Boundary_Bound);   fms.emplace_back(fm9);
    FM *fm10 = new FM(Boundary_Bound);  fms.emplace_back(fm10);
    FM *fm11 = new FM(Boundary_Bound);  fms.emplace_back(fm11);
    FM *fm12 = new FM(Boundary_Bound);  fms.emplace_back(fm12);
    FM *fm13 = new FM(Boundary_Bound);  fms.emplace_back(fm13);
    FM *fm14 = new FM(Boundary_Bound);  fms.emplace_back(fm14);
    FM *fm15 = new FM(Boundary_Bound);  fms.emplace_back(fm15);
    FM *fm16 = new FM(Boundary_Bound);  fms.emplace_back(fm16);
    FM *fm17 = new FM(Jump_Bound);      fms.emplace_back(fm17);
    FM *fm18 = new FM(Jump_Bound);      fms.emplace_back(fm18);
    FM *fm19 = new FM(Jump_Bound);      fms.emplace_back(fm19);
    FM *fm20 = new FM(Jump_Bound);      fms.emplace_back(fm20);

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
    thread thread17([&]() {
        fm17->Parser(fin17);
        fm17->Run();
    });
    thread thread18([&]() {
        fm18->Parser(fin18);
        fm18->Run();
    });
    thread thread19([&]() {
        fm19->Parser(fin19);
        fm19->Run();
    });
    thread thread20([&]() {
        fm20->Parser(fin20);
        fm20->Run();
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
    thread17.join();
    thread18.join();
    thread19.join();
    thread20.join();

    // Compare the results and dump the one with the smaller cut
    int fm1_cut = fm1->Get_Best_Cut();      cuts.emplace_back(fm1_cut);
    int fm2_cut = fm2->Get_Best_Cut();      cuts.emplace_back(fm2_cut);
    int fm3_cut = fm3->Get_Best_Cut();      cuts.emplace_back(fm3_cut);
    int fm4_cut = fm4->Get_Best_Cut();      cuts.emplace_back(fm4_cut);
    int fm5_cut = fm5->Get_Best_Cut();      cuts.emplace_back(fm5_cut);
    int fm6_cut = fm6->Get_Best_Cut();      cuts.emplace_back(fm6_cut);
    int fm7_cut = fm7->Get_Best_Cut();      cuts.emplace_back(fm7_cut);
    int fm8_cut = fm8->Get_Best_Cut();      cuts.emplace_back(fm8_cut);
    int fm9_cut = fm9->Get_Best_Cut();      cuts.emplace_back(fm9_cut);
    int fm10_cut = fm10->Get_Best_Cut();    cuts.emplace_back(fm10_cut);
    int fm11_cut = fm11->Get_Best_Cut();    cuts.emplace_back(fm11_cut);
    int fm12_cut = fm12->Get_Best_Cut();    cuts.emplace_back(fm12_cut);
    int fm13_cut = fm13->Get_Best_Cut();    cuts.emplace_back(fm13_cut);
    int fm14_cut = fm14->Get_Best_Cut();    cuts.emplace_back(fm14_cut);
    int fm15_cut = fm15->Get_Best_Cut();    cuts.emplace_back(fm15_cut);
    int fm16_cut = fm16->Get_Best_Cut();    cuts.emplace_back(fm16_cut);
    int fm17_cut = fm17->Get_Best_Cut();    cuts.emplace_back(fm17_cut);
    int fm18_cut = fm18->Get_Best_Cut();    cuts.emplace_back(fm18_cut);
    int fm19_cut = fm19->Get_Best_Cut();    cuts.emplace_back(fm19_cut);
    int fm20_cut = fm20->Get_Best_Cut();    cuts.emplace_back(fm20_cut);

    cout << "Half Bound: " << fm1_cut << " " << fm2_cut << " " << fm3_cut << " " << fm4_cut << " " << fm5_cut << " " << fm6_cut << " " << fm7_cut << " " << fm8_cut << endl;
    cout << "Boundary Bound: " << fm9_cut << " " << fm10_cut << " " << fm11_cut << " " << fm12_cut << " " << fm13_cut << " " << fm14_cut << " " << fm15_cut << " " << fm16_cut << endl;
    cout << "Jump Bound: " << fm17_cut << " " << fm18_cut << " " << fm19_cut << " " << fm20_cut << endl;
    
    // find the minimal cut from multithread result and dump it.
    int Min_Index = -1;
    int Min_Cut = INT_MAX;
    for(size_t i = 0; i < cuts.size(); i++){
        if(int(cuts[i]) < Min_Cut){
            Min_Index = i;
            Min_Cut = cuts[i];
        }
    }

    fms[Min_Index]->Dump(fout);
    return 0;
}
