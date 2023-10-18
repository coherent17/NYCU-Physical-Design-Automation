#ifndef _UTIL_H_
#define _UTIL_H_

// 2-Way Partition
#define NPARTS 2

// Log
#define SHOW_PARSER_SUMMARY 1
#define SHOW_INIT_PARTITION_SUMMARY 1
#define PRINT_DETAIL 1

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