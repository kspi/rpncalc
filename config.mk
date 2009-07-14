### Compile-time configuration.

# Possible compilation options to add to DEFS:
#   -DHISTORY - writes interactive history to ~/.rpncalc_history
# 
DEFS = -DHISTORY

CFLAGS = -g -ggdb -O0
LIBS = -lm -lreadline



### The rest shouldn't be modified.

APP = rpncalc
VERSION = 0.1

CFLAGS := $(CFLAGS) -DRPNCALC_VERSION='"$(VERSION)"' $(DEFS) -Wall -std=c99

HEADERS = \
	src/eval.h \
	src/fraction.h \
	src/frap.h \
	src/list.h \
	src/numbers.h \
	src/operators.h \
	src/predicates.h \
	src/util.h \
	src/real_ops.def

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
	README
