APP = rpncalc
VERSION = 0.1


CFLAGS = -g -ggdb -O0 -Wall -std=c99 -DRPNCALC_VERSION='"$(VERSION)"'
LIBS = -lm -lreadline


HEADERS = \
	src/eval.h \
	src/fraction.h \
	src/frap.h \
	src/list.h \
	src/numbers.h \
	src/operators.h \
	src/predicates.h \
	src/util.h

SOURCES = \
	src/eval.c \
	src/fraction.c \
	src/frap.c \
	src/list.c \
	src/main.c \
	src/numbers.c \
	src/operators.c \
	src/predicates.c \
	src/util.c

OBJS = $(patsubst src/%.c,build/%.o,$(SOURCES))


DISTDIRS = \
	src

DISTFILES = \
	$(SOURCES) \
	$(HEADERS) \
	Makefile \
	config.mk \
	README \
	$(APP)
