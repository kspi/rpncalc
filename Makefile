APP = rpncalc

OBJS = main.o list.o predicates.o operators.o util.o numbers.o eval.o	\
	   fraction.o

CC = gcc
CFLAGS = -g -ggdb -O0 -Wall -std=c99
LIBS = -lm -lreadline

.PHONY: all
all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LIBS) -o $(APP) $(OBJS)

install: all
	cp $(APP) $(HOME)/bin/$(APP)

clean:
	rm -f $(APP) $(OBJS)
