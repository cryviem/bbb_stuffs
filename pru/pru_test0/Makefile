
TARGET=am335x-pru0-fw
PRU_LKCMD_FILE=$(PRU_LNKCMD)/AM335x_PRU_RSCTB.cmd

SRCS=$(wildcard *.c)
OBJS=$(strip $(patsubst %.c, %.obj, $(SRCS)))
INC=-I$(PRU_SP)/include -I$(PRU_SP)/include/am335x -I$(PRU_CGT)/include
LIB=-i$(PRU_CGT)/lib

all: print_start main print_end

print_start:
	@echo ""
	@echo "---- START BUILD ----"
	@echo ""

print_end:
	@echo ""
	@echo "---- END BUILD ----"
	@echo ""

main: $(TARGET)

$(TARGET): $(OBJS)
	@echo "linking $@ ..."
	$(PRU_LD) $(LIB) $(PRU_LKCMD_FILE) $(OBJS) -o $@

%.obj: %.c
	@echo "building $@ ..."
	$(PRU_CC) $(INC) -c $<

clear:
	@echo "pru_test0 clearing ..."
	rm *.obj
	rm $(TARGET)

.PHONY: all clear print_start print_end main
