APP = rpncalc

OBJS = main.o list.o predicates.o operators.o util.o numbers.o

CC = gcc
CFLAGS = -g -ggdb -O0 -std=c99
LIBS = -lm

.PHONY: all
all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LIBS) -o $(APP) $(OBJS)

install: all
	cp $(APP) $(HOME)/bin/$(APP)

clean:
	rm -f $(APP) $(OBJS)
