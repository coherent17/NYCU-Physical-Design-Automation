#ifndef _UTIL_H_
#define _UTIL_H_

#define ANNEALING_TEMPERATURE 99999999
#define TEMPERATURE_DECREASING_RATE 0.999
#define TERMINATE_TEMPERATURE 1
#define STEPS_PER_TEMPERATURE 10

struct Match{
    size_t X;
    size_t Y;
};

#endif