#!/bin/sh

PRU_CGT=/home/an/tools/ti_pru_compiler/ti-cgt-pru_2.3.3
PRU_SP=/home/an/ws/bbb/pru/pru-software-support-package-6.1.0

PRU_CC=${PRU_CGT}/bin/clpru
PRU_LD=${PRU_CGT}/bin/lnkpru
PRU_INC="-I${PRU_SP}/include -I${PRU_SP}/include/am335x -I${PRU_CGT}/include"
PRU_LIB="-i${PRU_CGT}/lib"
PRU_LKCMD=${PRU_CGT}/example/AM3359_PRU.cmd
 

${PRU_CC} ${PRU_INC} -c pru0.c
${PRU_LD} ${PRU_LIB} ${PRU_LKCMD} pru0.obj -o am335x-pru0-fw