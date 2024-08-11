
# Need dtc version 1.5.0 or newer
# Manual update here: https://launchpad.net/ubuntu/+source/device-tree-compiler/
# amd64.deb

DTS_FILES=$(wildcard *.dts)
WO_EXT=$(strip $(patsubst %.dts, %, $(DTS_FILES)))
BUILD_CMD=dtc -@ -I dts -O dtb -o
PREPRC_CMD=cpp -nostdinc -I . -undef -x assembler-with-cpp

BBB=am335x-boneblack

all: print_start main print_end

print_start:
	@echo ""
	@echo "---- START BUILD OVERLAY ----"
	@echo ""

print_end:
	@echo ""
	@echo "---- END BUILD OVERLAY ----"
	@echo ""

# main:
# 	@for MTAR in $(WO_EXT); do \
# 		echo "building $$MTAR ..."; \
# 		$(PREPRC_CMD) $$MTAR.dts > $$MTAR.tmp.dts; \
# 		$(BUILD_CMD) $$MTAR.dtbo $$MTAR.tmp.dts; \
# 	done
	 
main: $(WO_EXT)

$(WO_EXT):
	@echo "building $@.dtb ...";
	@$(PREPRC_CMD) $@.dts > $@.tmp.dts
	@$(BUILD_CMD) $@.dtb $@.tmp.dts

bbb:
	@echo "building $(BBB).dtb ...";
	@$(PREPRC_CMD) $(BBB).dts > $(BBB).tmp.dts
	@$(BUILD_CMD) $(BBB).dtb $(BBB).tmp.dts

clean:
	rm -rf $(wildcard *.tmp.*)
	rm -rf $(wildcard *.dtb)

.PHONY: all clean print_start print_end main bbb $(WO_EXT)