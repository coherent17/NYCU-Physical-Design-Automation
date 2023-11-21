#ifndef _UTIL_H_
#define _UTIL_H_


// Log Setting
#define PRINT_INITIAL_SEQUENCE_PAIR false

// Simulated Annealing Setting
#define ANNEALING_TEMPERATURE 99999
#define CRITICAL_TEMPERATURE 999
#define TEMPERATURE_DECREASING_SLOW_RATE 0.999
#define TEMPERATURE_DECREASING_FAST_RATE 0.8
#define TERMINATE_TEMPERATURE 0.001
#define STEPS_PER_TEMPERATURE 450
#define MAX_CONSECUTIVE_TEMPERATURN_UNCHANGE 20

// SA OP
#define OPERATION1 0
#define OPERATION2 1
#define OPERATION3 2
#define OPERATION4 3

#define ACCEPT 1
#define REJECT 0

// Timing Control
#define MAX_EXECUTION_TIME 3600
#define BUFFER_TIME 10

struct Match{
    size_t X;
    size_t Y;
};

#endif