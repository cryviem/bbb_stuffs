ARM_CC=/home/an/tools/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
ARM_LD=/home/an/tools/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-ld
TARGET=led_ctrl
SRCS=$(wildcard *.c)
OBJS=$(strip $(patsubst %.c, %.o, $(SRCS)))
INC=
LIB=-lm -lpng

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
	$(ARM_LD) $(LIB) -o $@ $(OBJS)

%.o: %.c
	@echo "building $@ ..."
	$(ARM_CC) $(INC) -c $<

clean:
	rm *.o
	rm $(TARGET)

.PHONY: all clean print_start print_end main


