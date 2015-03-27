SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

LIB_PATH = .

.PHONY: all clean

all: $(LIB_PATH)/libengine.so
	
$(LIB_PATH)/libengine.so: $(lastword $(MAKEFILE_LIST)) $(OBJ)
	$(CC) -shared $(filter %.o,$^) -o $@ -ldl

clean:
	rm -f $(LIB_PATH)/libengine.so
	rm -f *.o
	rm -f *.d

include $(SRC:.c=.d)
%.d: %.c
	$(CC) -MM $< > $@
%.o: %.c
	$(CC) -c -fpic $< -o $@ -I.
