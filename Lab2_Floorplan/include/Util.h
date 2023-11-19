#ifndef _UTIL_H_
#define _UTIL_H_


// Log Setting
#define PRINT_INITIAL_SEQUENCE_PAIR true

// Simulated Annealing Setting
#define ANNEALING_TEMPERATURE 99999999
#define TEMPERATURE_DECREASING_RATE 0.999
#define TERMINATE_TEMPERATURE 1
#define STEPS_PER_TEMPERATURE 10
#define OPERATION1 0
#define OPERATION2 1
#define OPERATION3 2
#define POSITIVE_SEQ 0
#define NEGATIVE_SEQ 1


struct Match{
    size_t X;
    size_t Y;
};

#endif