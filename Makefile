include config.mk

.PHONY: all clean dist

all: $(APP)

$(APP): config.mk depend.mk build $(OBJS)
	@echo "    LD  $@"
	@$(CC) $(LIBS) -o $(APP) $(OBJS)

build/%.o: src/%.c config.mk
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
	@echo "    CLEAN"
	@rm -rf build dist
	@rm -f $(APP) $(OBJS) depend.mk

dist: dist/$(APP)-$(VERSION).tar

dist/$(APP)-$(VERSION).tar: $(DISTFILES)
	@echo "Copying files ..."
	@mkdir -p dist/$(APP)-$(VERSION)
	@rm -rf dist/$(APP)-$(VERSION)/*
	@for d in $(DISTDIRS); do echo "    MKDIR  $$d"; mkdir -p dist/$(APP)-$(VERSION)/$$d; done
	@for f in $(DISTFILES); do echo "    CP  $$f"; cp $$f dist/$(APP)-$(VERSION)/$$f; done
	@echo "Testing compilation ..."
	@make -Cdist/$(APP)-$(VERSION) clean all
	@make -Cdist/$(APP)-$(VERSION) clean
	@echo "Creating archive ..."
	@cd dist && tar -czvf $(APP)-$(VERSION).tar.gz $(APP)-$(VERSION)
	@rm -rf dist/$(APP)-$(VERSION)
	@echo "dist/$(APP)-$(VERSION).tar created!"

-include depend.mk
