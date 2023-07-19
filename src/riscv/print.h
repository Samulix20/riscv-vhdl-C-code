#ifndef PRINT_H
#define PRINT_H

#include "types.h"

// print register
#define PRINT_REG_ADDR   0x00090000
#define PRINT_REG       *((volatile unsigned int *) PRINT_REG_ADDR)

inline void print_char(char c) {
    PRINT_REG = c;
}

// -------------- Strings --------------
void print_str(char* str);

// -------------- 32 bits --------------
void printmc_int32(int32 num, uint8 minchars);
#define print_int32(num) printmc_int32(num, 0)
void printmc_uint32(uint32 num, uint8 minchars);
#define print_uint32(num) printmc_uint32(num, 0)

// -------------- 64 bits --------------
void printmc_int64(int64 num, uint8 minchars);
#define print_int64(num) printmc_int64(num, 0)
void printmc_uint64(uint64 num, uint8 minchars);
#define print_uint64(num) printmc_uint64(num, 0)

// -------------- fixed16 --------------
void print_fixed16(int32 num);

/*
    %i_ -> int32_t
    %u_ -> uint32_t
    %li -> int64_t
    %lu -> uint64_t
    %f  -> fix16_t
*/
void fprint(char* format, uint64* params);

// Macros used for variadic number of parameters

#define CONCATENATE(a, b) a##b
#define _NVARGS(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, ...) p10
#define NVARGS(...) _NVARGS(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1)

// Declaration for a common buffer
extern uint64 print_buff[];

// Macros for printf with 10 variadic parameters
#define _PRINTF_0(str, i, ...) fprint(str, print_buff)
#define _PRINTF_1(str, i, x, ...) print_buff[i] = x; _PRINTF_0(str, 0, __VA_ARGS__)
#define _PRINTF_2(str, i, x, ...) print_buff[i] = x; _PRINTF_1(str, i+1, __VA_ARGS__)
#define _PRINTF_3(str, i, x, ...) print_buff[i] = x; _PRINTF_2(str, i+1, __VA_ARGS__)
#define _PRINTF_4(str, i, x, ...) print_buff[i] = x; _PRINTF_3(str, i+1, __VA_ARGS__)
#define _PRINTF_5(str, i, x, ...) print_buff[i] = x; _PRINTF_4(str, i+1, __VA_ARGS__)
#define _PRINTF_6(str, i, x, ...) print_buff[i] = x; _PRINTF_5(str, i+1, __VA_ARGS__)
#define _PRINTF_7(str, i, x, ...) print_buff[i] = x; _PRINTF_6(str, i+1, __VA_ARGS__)
#define _PRINTF_8(str, i, x, ...) print_buff[i] = x; _PRINTF_7(str, i+1, __VA_ARGS__)
#define _PRINTF_9(str, i, x, ...) print_buff[i] = x; _PRINTF_8(str, i+1, __VA_ARGS__)
#define _PRINTF(str, n, ...) CONCATENATE(_PRINTF_, n)(str, 0, __VA_ARGS__)

#define PRINTF(str, ...) _PRINTF(str, NVARGS(__VA_ARGS__), __VA_ARGS__) 
#define PRINT(str) print_str(str)

#endif
