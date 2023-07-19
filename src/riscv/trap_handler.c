#include "trap_handler.h"
#include "print.h"
#include "csr.h"
#include "mtimer.h"

void _trap_handler() {
    uint64 buff;
    uint32 mcause = read_mcause();

    switch (mcause) {
        case MCAUSE_TIMER_IRQ:
            _mtimer_irq();
            break;
        default:
            buff = mcause;
            fprint("Unexpected mcause found: %u\n", &buff);
            buff = read_mepc();
            fprint("MEPC: %u\n", &buff);
            while(1);
    }
}
