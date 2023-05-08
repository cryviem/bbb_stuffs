#include <stdint.h>
 

#define CYCLES_PER_SECOND 200000000 /* 200MHz clock */
#define PR1_PRU0_PRU_R30_2 (1 << 2)
 

volatile register uint32_t __R30;   /* GPIO output register */
 

void main(void) {
    while (1) {
        /* Switch the GPIO with one cycle every millisecond.  This can be
         * verified with an oscilloscope. */
        __R30 |= PR1_PRU0_PRU_R30_2;
        __delay_cycles(CYCLES_PER_SECOND / 2000);
        __R30 &= ~PR1_PRU0_PRU_R30_2;
        __delay_cycles(CYCLES_PER_SECOND / 2000);
    }
}