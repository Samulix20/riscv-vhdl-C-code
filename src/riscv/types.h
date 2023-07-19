#ifndef TYPES_H
#define TYPES_H

// NULL definition

#define NULL 0

// Standard type sizes

typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed int int32;
typedef unsigned int uint32;

typedef signed long long int int64;
typedef unsigned long long int uint64;

typedef uint32  size_t;

// FUNCTIONS IMPLEMENTED HERE FOR INLINING

typedef int32   fix16;
typedef int32   fix28;

#define ITOFIX(i, n)				(i << n)
#define FTOFIX(f, n, dt)			((dt) (f * (1 << n)))
#define MULFIX(a, b, n, dt, dt2)	((dt) (((dt2) a * (dt2) b) >> n))
#define DIVFIX(a, b, n, dt, dt2)	((dt) (((dt2) a << n) / (dt2) b))

#endif