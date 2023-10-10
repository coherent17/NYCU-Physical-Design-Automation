#ifndef _UTIL_H_
#define _UTIL_H_

// 2-Way Partition
#define NPARTS 2

#define CONVERAGE_CRITERIA 20

// Timing Control
#define MAX_EXECUTION_TIME 3600
#define BUFFER_TIME 2

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