#include <stdint.h>
 

#define CYCLES_PER_SECOND 200000000 /* 200MHz clock */
#define PR1_PRU0_PRU_R30_2 (1 << 2) /* R30_2 */
 
volatile register uint32_t __R30;   /* GPIO output register */

static void led_on()
{
    __R30 &= ~PR1_PRU0_PRU_R30_2;
}

static void led_off()
{
    __R30 |= PR1_PRU0_PRU_R30_2;
}

void main(void) {

    while (1) {
        
    }
}