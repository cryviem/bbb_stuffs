SUBDIRS=PRU_access_const_table PRU_ADC_onChip PRU_Direct_Connect0 PRU_Direct_Connect1 PRU_edmaConfig PRU_gpioToggle PRU_Hardware_UART \
PRU_IEP PRU_MAC_Multiply_Accum PRU_RPMsg_Echo_Interrupt0 PRU_RPMsg_Echo_Interrupt1 PRU_Halt

all: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

clean:
	@for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done

.PHONY: all clean $(SUBDIRS)



