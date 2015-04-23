SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: $(BIN_PATH)/player
	
$(BIN_PATH)/player: $(lastword $(MAKEFILE_LIST)) $(OBJ)
	$(CC) $(filter %.o,$^) -o $@ -L$(LIB_PATH) -lengine -Wl,-rpath $(LIB_PATH)

clean:
	rm -f $(BIN_PATH)/player
	rm -f *.o
	rm -f *.d

-include $(SRC:.c=.d)
%.d: %.c
	$(CC) -MM $< > $@
%.o: %.c
	$(CC) -c $< -o $@ -I$(ENGINE_PATH)
