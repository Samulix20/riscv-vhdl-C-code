#include "mtimer.h"
#include "csr.h"
#include "print.h"

static uint64 period;

void _mtimer_irq() {
    MTIMER_CMP = MTIMER_COUNTER + period;
    print_str("Tick!\n");
}

void set_mtimer_period(uint64 p) {
    period = p;
    MTIMER_CMP = MTIMER_COUNTER + period;
}

void enable_mtimer() {
    set_mie(MIE_MTIMER);
    set_mstatus(MSTATUS_MIE);
}

