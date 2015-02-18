SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: $(LIB_PATH)/libengine.so
	
$(LIB_PATH)/libengine.so: $(lastword $(MAKEFILE_LIST)) $(OBJ)
	$(CC) -shared $(filter %.o,$^) -o $@ -ldl

clean:
	rm -f $(LIB_PATH)/libengine.so
	rm -f *.o

%.o: %.c
	$(CC) -c -fpic $< -o $@ -I.
