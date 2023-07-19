#ifndef C_RAND_H
#define C_RAND_H

#include "types.h"

/*
	###########################
	# Random number generator #
	###########################
*/

extern uint32 rand_reg;

// Linear feedback for lsfr31 register
inline void lfsr31(uint32* reg) {
	uint32 v = *reg;
	uint32 feedback = (((v >> 3) ^ v) & 1);
	*reg = (feedback << 30) | (v >> 1);
}

// Returns random 31 bit number and advances lsfr state
inline uint32 c_rand() {
	uint32 aux = rand_reg;
	lfsr31(&rand_reg);
	return aux;
}

// Rand state setter, Set internal value of rand lfsr
inline void c_set_rand_seed(uint32 seed) {
	rand_reg = seed & 0x7FFFFFFF;
	lfsr31(&rand_reg);
}

/*
	#############################
	# Gaussian number generator #
	#############################
*/

#define NREGS 12
extern uint32 c_gauss_regs[NREGS];

// Register setter, Set internal value of lfsr i
inline void c_set_gauss_seed(uint8 i, uint32 seed) {
	c_gauss_regs[i-1] = seed & 0x7FFFFFFF;
}

// Generates a random number using a sum of 12
// lsfr31 registers random generated values
// Returns in range [-24570, 24570]
inline int32 c_gauss_gen() {
	uint32 acc = 0;
	for(int i = 0; i < NREGS; i++) {
		acc += c_gauss_regs[i] & 0xFFF;
		lfsr31(&c_gauss_regs[i]);
	}
	return ((int32) acc) - 24570;
}

#endif