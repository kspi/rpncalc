.PHONY: all

all: $(APP) clean

$(APP): $(OBJS)
	$(CC) $(LIBS) -o $(APP) $(OBJS)

clean:
	rm -f $(APP) $(OBJS)
