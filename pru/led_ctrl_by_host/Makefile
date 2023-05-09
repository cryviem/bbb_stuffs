
TARGET=led_ctrl_by_host.out
PRU_LKCMD_FILE=$(PRU_LNKCMD)/AM335x_PRU_INTC_RSCTB.cmd

SRCS=$(wildcard *.c)
OBJS=$(strip $(patsubst %.c, %.obj, $(SRCS)))
INC=-I$(PRU_SSP)/include -I$(PRU_SSP)/include/am335x -I$(PRU_CGT)/include
LIB=-i$(PRU_CGT)/lib

all: print_start main print_end

print_start:
	@echo ""
	@echo "---- START BUILD $(TARGET) ----"
	@echo ""

print_end:
	@echo ""
	@echo "---- END BUILD $(TARGET) ----"
	@echo ""

main: $(TARGET)

$(TARGET): $(OBJS)
	@echo "linking $@ ..."
	$(PRU_LD) $(LIB) $(PRU_LKCMD_FILE) $(OBJS) -o $@

%.obj: %.c
	@echo "building $@ ..."
	$(PRU_CC) $(INC) -c $<

clean:
	rm *.obj
	rm $(TARGET)

.PHONY: all clean print_start print_end main
