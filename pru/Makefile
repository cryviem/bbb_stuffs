
PRU_ROOT:= $(shell pwd)
PRU_CC := $(shell find ~ -name clpru)
PRU_CGT := $(subst /bin/clpru,,$(PRU_CC))
PRU_LD := $(PRU_CGT)/bin/lnkpru

PRU_SSP := $(PRU_ROOT)/pru-software-support-package-6.1.0
PRU_LNKCMD := $(PRU_ROOT)/linker_cmds

export PRU_CC PRU_LD PRU_CGT PRU_SSP PRU_LNKCMD

SUBDIRS=pru_test0 pru_test1 led_ctrl_by_host

all: chk_precond main

print_db:
	@echo "PRU_CC $(PRU_CC)"
	@echo "PRU_LD $(PRU_LD)"
	@echo "PRU_CGT $(PRU_CGT)"
	@echo "PRU_ROOT $(PRU_ROOT)"
	@echo "PRU_SSP $(PRU_SSP)"
	@echo "PRU_LNKCMD $(PRU_LNKCMD)"
	@echo "SUBDIRS $(SUBDIRS)"

chk_precond:
ifeq ($(strip $(PRU_CC)),)
	$(error PRU Compiler not found)
endif
ifeq ($(wildcard $(PRU_SSP)),)
	$(error PRU support package not found)
endif
	

main: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	@for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done

.PHONY: all clean print_db chk_precond main $(SUBDIRS)

