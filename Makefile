include config.mk

### SETTINGS

APP := rpncalc
VERSION := 0.1

CFLAGS := $(CFLAGS) -DRPNCALC_VERSION='"$(VERSION)"' $(DEFS) -Wall -Werror -pedantic -std=c99

HEADERS := \
	src/eval.h \
	src/fraction.h \
	src/list.h \
	src/numbers.h \
	src/operators.h \
	src/predicates.h \
	src/util.h \
	src/real_ops.def

SOURCES := \
	src/eval.c \
	src/fraction.c \
	src/list.c \
	src/main.c \
	src/numbers.c \
	src/operators.c \
	src/predicates.c \
	src/util.c

OBJS := $(patsubst src/%.c,build/%.o,$(SOURCES))


DISTDIRS := \
	src

DISTFILES := \
	$(SOURCES) \
	$(HEADERS) \
	Makefile \
	config.mk \
	README

###

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
