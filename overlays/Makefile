
# Need dtc version 1.5.0 or newer
# Manual update here: https://launchpad.net/ubuntu/+source/device-tree-compiler/
# amd64.deb

DTS_FILES=$(wildcard *.dts)
DTBO_FILES=$(patsubst %.dts, %.dtbo, $(DTS_FILES))
WO_EXT=$(strip $(patsubst %.dts, %, $(DTS_FILES)))
BUILD_CMD=dtc -@ -I dts -O dtb -o
all: print_start main print_end

print_start:
	@echo ""
	@echo "---- START BUILD OVERLAY ----"
	@echo ""

print_end:
	@echo ""
	@echo "---- END BUILD OVERLAY ----"
	@echo ""

main:
	@for MTAR in $(WO_EXT); do \
		echo "building $$MTAR ..."; \
		cpp -nostdinc -I . -undef -x assembler-with-cpp $$MTAR.dts > $$MTAR.tmp.dts; \
		$(BUILD_CMD) $$MTAR.dtbo $$MTAR.tmp.dts; \
	done
	 
clear:
	rm -rf $(wildcard *.tmp.*)
	rm -rf $(wildcard *.dtbo)