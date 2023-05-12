ARM_CC := $(shell find ~ -name arm-linux-gnueabihf-gcc)

TARGET=led_ctrl

SRCS=$(wildcard *.c)
OBJS=$(strip $(patsubst %.c, %.o, $(SRCS)))
INC=
LIB=

all: print_start chk_precond main print_end

print_start:
	@echo ""
	@echo "---- START BUILD $(TARGET) ----"
	@echo ""

print_end:
	@echo ""
	@echo "---- END BUILD $(TARGET) ----"
	@echo ""

chk_precond:
ifeq ($(strip $(ARM_CC)),)
	$(error ARM Compiler not found)
endif
	@echo "found ARM_CC: $(ARM_CC)"
	@echo ""

main: $(TARGET)

$(TARGET): $(OBJS)
	@echo "linking $@ ..."
	$(ARM_CC) $(LIB) -o $@ $(OBJS)

%.o: %.c
	@echo "building $@ ..."
	$(ARM_CC) $(INC) -c $<

clean:
	rm -f *.o
	rm -f $(TARGET)

.PHONY: all clean print_start print_end main chk_precond


