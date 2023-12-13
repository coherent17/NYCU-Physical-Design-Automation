#include "Random_Number_Generator.h"

// Constructor & Destructor
Random_Number_Generator::Random_Number_Generator(){
    srand(time(0));
}

Random_Number_Generator::~Random_Number_Generator(){
    ;
}

// Generate a random integer between 0 and n (inclusive)
int Random_Number_Generator::Generate_Random_Integer(int n){
    return rand() % (n + 1);
}

// Generate a random floating-point number between 0 and 1
double Random_Number_Generator::Generate_Random_Float(){
    return static_cast<double>(rand()) / RAND_MAX;
}