#include "Floorplan_Manager.h"

// Constructor & Destructor
Floorplan_Manager::Floorplan_Manager(const char *input_filename, const char *output_filename):
    input_filename(input_filename),
    output_filename(output_filename)
{
    fin1.open(input_filename);
    fin2.open(input_filename);
    fin3.open(input_filename);
    fin4.open(input_filename);
    fin5.open(input_filename);
    fin6.open(input_filename);
    fin7.open(input_filename);
    fin8.open(input_filename);
    fin9.open(input_filename);
    fin10.open(input_filename);
    fout.open(output_filename);
}

Floorplan_Manager::~Floorplan_Manager(){
    ;
}

void Floorplan_Manager::Run_Thread(){
    vector<Floorplan *> fps;
    vector<int> Areas;
    Floorplan *fp1 = new Floorplan(true);   fps.emplace_back(fp1);
    Floorplan *fp2 = new Floorplan(true);   fps.emplace_back(fp2);
    Floorplan *fp3 = new Floorplan(true);   fps.emplace_back(fp3);
    Floorplan *fp4 = new Floorplan(true);   fps.emplace_back(fp4);
    Floorplan *fp5 = new Floorplan(true);   fps.emplace_back(fp5);
    Floorplan *fp6 = new Floorplan(false);  fps.emplace_back(fp6);
    Floorplan *fp7 = new Floorplan(false);  fps.emplace_back(fp7);
    Floorplan *fp8 = new Floorplan(false);  fps.emplace_back(fp8);
    Floorplan *fp9 = new Floorplan(false);  fps.emplace_back(fp9);
    Floorplan *fp10 = new Floorplan(false); fps.emplace_back(fp10);

    
    thread thread1([&]() {
        fp1->Parser(fin1);
        fp1->Run();
    });

    thread thread2([&]() {
        fp2->Parser(fin2);
        fp2->Run();
    });

    thread thread3([&]() {
        fp3->Parser(fin3);
        fp3->Run();
    });

    thread thread4([&]() {
        fp4->Parser(fin4);
        fp4->Run();
    });

    thread thread5([&]() {
        fp5->Parser(fin5);
        fp5->Run();
    });

    thread thread6([&]() {
        fp6->Parser(fin6);
        fp6->Run();
    });

    thread thread7([&]() {
        fp7->Parser(fin7);
        fp7->Run();
    });

    thread thread8([&]() {
        fp8->Parser(fin8);
        fp8->Run();
    });

    thread thread9([&]() {
        fp9->Parser(fin9);
        fp9->Run();
    });

    thread thread10([&]() {
        fp10->Parser(fin10);
        fp10->Run();
    });

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

    for(size_t i = 0; i < fps.size(); i++){
        cout << fps[i]->Area << endl;
        Areas.emplace_back(fps[i]->Area);
    }

    int Min_Index = -1;
    int Min_Area = INT_MAX;
    for(size_t i = 0; i < fps.size(); i++){
        if(int(fps[i]->Area) < Min_Area){
            Min_Index = i;
            Min_Area = fps[i]->Area;
        }
    }
    fps[Min_Index]->Dump(fout);
}