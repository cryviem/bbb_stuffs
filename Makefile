SUBDIRS=overlays pru

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clear:
	@for d in $(SUBDIRS); do (cd $$d; $(MAKE) clear ); done

.PHONY: all clear $(SUBDIRS)