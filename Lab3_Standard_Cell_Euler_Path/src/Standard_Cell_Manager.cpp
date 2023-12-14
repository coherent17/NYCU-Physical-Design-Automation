#include "Standard_Cell_Manager.h"

// Constructor & Destructor
Standard_Cell_Manager::Standard_Cell_Manager(const char *input_filename, const char *output_filename):
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

Standard_Cell_Manager::~Standard_Cell_Manager(){
    ;
}

void Standard_Cell_Manager::Run_Thread(){
    vector<Standard_Cell *> std_cells;
    vector<double> hpwls;
    Standard_Cell *std_cell1 = new Standard_Cell();   std_cells.emplace_back(std_cell1);
    Standard_Cell *std_cell2 = new Standard_Cell();   std_cells.emplace_back(std_cell2);
    Standard_Cell *std_cell3 = new Standard_Cell();   std_cells.emplace_back(std_cell3);
    Standard_Cell *std_cell4 = new Standard_Cell();   std_cells.emplace_back(std_cell4);
    Standard_Cell *std_cell5 = new Standard_Cell();   std_cells.emplace_back(std_cell5);
    Standard_Cell *std_cell6 = new Standard_Cell();   std_cells.emplace_back(std_cell6);
    Standard_Cell *std_cell7 = new Standard_Cell();   std_cells.emplace_back(std_cell7);
    Standard_Cell *std_cell8 = new Standard_Cell();   std_cells.emplace_back(std_cell8);
    Standard_Cell *std_cell9 = new Standard_Cell();   std_cells.emplace_back(std_cell9);
    Standard_Cell *std_cell10 = new Standard_Cell();  std_cells.emplace_back(std_cell10);
    
    thread thread1([&]() {
        std_cell1->Spice_Parser(fin1);
        std_cell1->Run();
    });

    thread thread2([&]() {
        std_cell2->Spice_Parser(fin2);
        std_cell2->Run();
    });

    thread thread3([&]() {
        std_cell3->Spice_Parser(fin3);
        std_cell3->Run();
    });

    thread thread4([&]() {
        std_cell4->Spice_Parser(fin4);
        std_cell4->Run();
    });

    thread thread5([&]() {
        std_cell5->Spice_Parser(fin5);
        std_cell5->Run();
    });

    thread thread6([&]() {
        std_cell6->Spice_Parser(fin6);
        std_cell6->Run();
    });

    thread thread7([&]() {
        std_cell7->Spice_Parser(fin7);
        std_cell7->Run();
    });

    thread thread8([&]() {
        std_cell8->Spice_Parser(fin8);
        std_cell8->Run();
    });

    thread thread9([&]() {
        std_cell9->Spice_Parser(fin9);
        std_cell9->Run();
    });

    thread thread10([&]() {
        std_cell10->Spice_Parser(fin10);
        std_cell10->Run();
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

    for(size_t i = 0; i < std_cells.size(); i++){
        //cout << std_cells[i]->Get_HPWL() << endl;
        hpwls.emplace_back(std_cells[i]->Get_HPWL());
    }

    int Min_Index = -1;
    double Min_HPWL = INT_MAX;
    for(size_t i = 0; i < std_cells.size(); i++){
        if(std_cells[i]->Get_HPWL() < Min_HPWL){
            Min_Index = i;
            Min_HPWL = std_cells[i]->Get_HPWL();
        }
    }
    std_cells[Min_Index]->Dump(fout);
}