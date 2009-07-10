APP = rpncalc
VERSION = 0.1

CFLAGS = -g -ggdb -O0 -Wall -std=c99 -DRPNCALC_VERSION='\"$(VERSION)\"'
LIBS = -lm -lreadline

DISTDIRS = \
	src

DISTFILES = \
	src/eval.c \
	src/eval.h \
	src/fraction.c \
	src/fraction.h \
	src/frap.c \
	src/frap.h \
	src/list.c \
	src/list.h \
	src/main.c \
	src/numbers.c \
	src/numbers.h \
	src/operators.c \
	src/operators.h \
	src/predicates.c \
	src/predicates.h \
	src/util.c \
	src/util.h \
	src/Makefile \
	Makefile \
	README \
	$(APP)

OBJS = main.o list.o predicates.o operators.o util.o numbers.o eval.o	\
	   fraction.o frap.o

.PHONY: all clean dist

all: $(APP)

$(APP): src/$(APP)
	ln -sf src/$(APP) $(APP)

.PHONY: ${patsubst %,src/%,$(OBJS)}

src/$(APP): ${patsubst %,src/%,$(OBJS)}
	make -Csrc $(APP) APP="$(APP)" CC="$(CC)" CFLAGS="$(CFLAGS)" LIBS="$(LIBS)" OBJS="$(OBJS)"

clean:
	rm -f $(APP)
	make -Csrc clean APP="$(APP)" OBJS="$(OBJS)"
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