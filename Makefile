include config.mk

.PHONY: all clean dist

all: $(APP)

$(APP): depend.mk build $(OBJS)
	@echo "    LD  $@"
	@$(CC) $(LIBS) -o $(APP) $(OBJS)

build/%.o: src/%.c
	@echo "    CC  $@"
	@$(CC) $(CFLAGS) -c -o $@ $(patsubst build/%.o,src/%.c,$@)

build:
	@echo "    MKDIR $@"
	@mkdir -p $@

depend.mk: $(SOURCES) $(INCLUDES)
# the -M switch probably only works with gcc
	@echo "    DEPEND"
	@$(CC) $(CFLAGS) -M $(SOURCES) $(INCLUDES) \
		| sed -r 's,^(.*\.o:),build/\1,' > depend.mk

clean:
	rm -f $(APP)
	rm -f src/$(APP) $(OBJS)
	rm -rf build
	rm -f depend.mk
	rm -rf dist

dist: dist/$(APP)-$(VERSION).tar

dist/$(APP)-$(VERSION).tar: $(DISTFILES)
	mkdir -p dist/$(APP)-$(VERSION)
	rm -rf dist/$(APP)-$(VERSION)/*
	for d in $(DISTDIRS); do mkdir -p dist/$(APP)-$(VERSION)/$$d; done
	for f in $(DISTFILES); do cp $$f dist/$(APP)-$(VERSION)/$$f; done
	make -Cdist/$(APP)-$(VERSION) clean all
	make -Cdist/$(APP)-$(VERSION) clean
	cd dist && tar -czvf $(APP)-$(VERSION).tar.gz $(APP)-$(VERSION)
	rm -rf dist/$(APP)-$(VERSION)

include depend.mk