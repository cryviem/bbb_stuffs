/*
 * Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	* Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the
 *	  distribution.
 *
 *	* Neither the name of Texas Instruments Incorporated nor the names of
 *	  its contributors may be used to endorse or promote products derived
 *	  from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// ***************************************
// *    Global Structure Definitions     *
// ***************************************

#include <stdint.h>


/* R31 is used to generate the "I'm done" back to the ARM */
volatile register uint8_t __R31;

/* Accessing the operands structure within the multiplyParams structure
 * forces the compiler to pair the registers together */
typedef struct {
	uint32_t op1;
	uint32_t op2;
} operands;

#define NUMMACS 256

/*
 * Structure buf is pretty big: uint32 * 2 * 256 = 2kB, or 0x800 memory.
 * Make sure that there is enough Data RAM for your program. This example
 * allocates space for buf in .bss (uninitialized near data section).
 * After you build the example, you can verify the amount of Data RAM the
 * example uses by inspecting the .map file in the outputs folder.
 * The .map file for the MAC example tells us:
 * MEMORY CONFIGURATION --> PRUx_DMEMx: 0x900 memory is used
 * SECTION ALLOCATION MAP: .bss uses 0x800 (this is buf), .stack uses 0x100
 *
 * To modify the size of the stack, edit Makefile > STACK_SIZE.
 *
 * Reference "PRU Optimizing C/C++ Compiler User's Guide", section "Dynamic
 * Memory Allocation" if you want to allocate large arrays from the heap instead
 * of the .bss section.
 */
operands buf[NUMMACS];

/* Need to create a while loop inside main to wait for interrupt from host.
 * The interrupt will signify that a buffer of data has been passed and is
 * ready for MAC processing. This will be passed by rpmsg driver.
 */
void main(void)
{
	uint32_t i;
	uint16_t numMacs = NUMMACS; // Arbitrary number
	uint64_t result = 0;
	volatile uint64_t storeValue = 0;

	/* Dummy data set */
	for (i = 0; i < numMacs; i++) {
		buf[i].op1 = i;
		buf[i].op2 = i+1;
	}

	/* Perform numMacs MAC operations */
	for (i = 0; i < numMacs; i++) {
		result += (uint64_t)buf[i].op1 * (uint64_t)buf[i].op2;
	}

	storeValue = result;

	/* Nothing to do so halt */
	__halt();
}
