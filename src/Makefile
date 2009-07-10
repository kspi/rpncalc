# Metarules: Makefile in .. stores compile settings, so call it if
# this Makefile is called directly (without the settings).

.PHONY: all

all:
	test -n "$(OBJS)" || make -C.. all
	test -z "$(OBJS)" || make "$(APP)"

clean:
	test -n "$(OBJS)" || make -C.. clean
	test -z "$(OBJS)" || rm -f $(APP) $(OBJS)

# Normal rules

$(APP): $(OBJS)
	$(CC) $(LIBS) -o $(APP) $(OBJS)
