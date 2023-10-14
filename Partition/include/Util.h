#ifndef _UTIL_H_
#define _UTIL_H_

// show log
#define SHOW_LOG 1
#define PRINT_DETAIL 0

// 2-Way Partition
#define NPARTS 2

// FM terminate condition
#define CONVERAGE_CRITERIA 20
#define MAX_USELESS_FM_COUNT 100

// Local Search times when finiding better solution
#define LOCAL_SEARCH_TIME 3

// Timing Control
#define MAX_EXECUTION_TIME 3600
#define BUFFER_TIME 5

// Check whether the cell is locked of not in FM process
enum Lock_State{
    Not_Lock = 0,
    Lock = 1
};

// Represent cell current partition side
enum Partition_Side{
    Left = 0,
    Right = 1
};

#endif