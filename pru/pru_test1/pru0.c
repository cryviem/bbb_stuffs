#include <stdint.h>
#include <rsc_types.h>  /* struct resource_table */
 

#define CYCLES_PER_SECOND 200000000 /* 200MHz clock */
#define PR1_PRU0_PRU_R30_14 (1 << 14) /* Pin to change (GPIO1_12) */
 

volatile register uint32_t __R30;   /* GPIO output register */
 

void main(void) {
    while (1) {
        /* Switch the GPIO with one cycle every millisecond.  This can be
         * verified with an oscilloscope. */
        __R30 |= PR1_PRU0_PRU_R30_14;
        __delay_cycles(CYCLES_PER_SECOND / 2000);
        __R30 &= ~PR1_PRU0_PRU_R30_14;
        __delay_cycles(CYCLES_PER_SECOND / 2000);
    }
}

 
/* Required by the Linux remoteproc driver.  This is an empty resource table
 * which is good enough if no resources are required. */
#pragma DATA_SECTION(my_resource_table, ".resource_table")
#pragma RETAIN(my_resource_table)
struct resource_table my_resource_table = {1, 0, 0, 0};
