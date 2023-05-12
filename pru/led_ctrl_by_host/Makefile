
TARGET=led_ctrl_by_host.out
PRU_LKCMD_FILE=$(PRU_LNKCMD)/AM335x_PRU_INTC_RSCTB.cmd

SRCS=$(wildcard *.c)
OBJS=$(strip $(patsubst %.c, %.obj, $(SRCS)))
INC=-I$(PRU_SSP)/include -I$(PRU_SSP)/include/am335x -I$(PRU_CGT)/include
LIB=-i$(PRU_CGT)/lib -i$(PRU_SSP)/lib -lrpmsg_lib.lib

SUBDIRS=host_app

all: print_start main print_end $(SUBDIRS)

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
	$(PRU_LD) --reread_libs $(LIB) $(PRU_LKCMD_FILE) $(OBJS) -o $@

%.obj: %.c
	@echo "building $@ ..."
	$(PRU_CC) $(INC) -c $<

clean:
	rm *.obj
	rm $(TARGET)
	@for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all clean print_start print_end main $(SUBDIRS)
