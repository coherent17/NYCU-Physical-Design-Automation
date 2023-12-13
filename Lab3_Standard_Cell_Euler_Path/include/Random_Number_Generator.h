#ifndef _RANDOM_NUMBER_GENERATOR_H_
#define _RANDOM_NUMBER_GENERATOR_H_

#include <bits/stdc++.h>
using namespace std;

class Random_Number_Generator{
    public:
        // Constructor & Destructor
        Random_Number_Generator();
        ~Random_Number_Generator();
        
        // Generate a random integer between 0 and n (inclusive)
        int Generate_Random_Integer(int n);

        // Generate a random floating-point number between 0 and 1
        double Generate_Random_Float();
};

#endif