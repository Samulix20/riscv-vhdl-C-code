#include "rand.h"

// Rand state register
uint32 rand_reg = 332497906;

// Default seeds
uint32 c_gauss_regs[NREGS] = {
	1716423834,
	942653533,
	806001601,
	1310124748,
	676345546,
	581446409,
	1612362739,
	1239472396,
	73697298,
	1439998451,
	76811588,
	1082159512,
};

