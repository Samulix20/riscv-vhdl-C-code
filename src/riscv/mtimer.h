#ifndef MTIMER_H
#define MTIMER_H

#include "types.h"

// mtimer registers
#define MTIMER_BASE_ADDR    0x00050000
#define MTIMER_COUNTER      *((volatile uint64 *) MTIMER_BASE_ADDR)
#define MTIMER_CMP          *((volatile uint64 *) (MTIMER_BASE_ADDR + 8))

// mtimer bit in mie
#define MIE_MTIMER (1 << 7)

// mtimer irq handler
void _mtimer_irq();

// mtimer set interrupt period in ticks
void set_mtimer_period(uint64 p);

// Enable mtimer interrupts
void enable_mtimer();

#endif
