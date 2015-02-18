MODULE = $(notdir $(abspath .)).module

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: $(MODULE)
	
$(MODULE): $(lastword $(MAKEFILE_LIST)) $(OBJ)
	$(LD) -shared $(filter %.o,$^) -o $@ -L$(LIB_PATH) -lengine

clean:
	rm -f $(MODULE)
	rm -f *.o

%.o: %.c
	$(CC) -c -fpic $< -o $@ -I$(ENGINE_PATH)
