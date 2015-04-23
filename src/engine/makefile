LIBS = dl

MODULES_PATH = $(abspath modules)
MODULES = OGLRender

SRC = $(wildcard core/*.c)
SRC += $(MODULES_PATH)/modules.c
SRC += $(wildcard $(patsubst %,$(MODULES_PATH)/%/*.c,$(MODULES)))
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

.PHONY: all clean

all: $(LIB_PATH)/libengine.so

$(LIB_PATH)/libengine.so: $(lastword $(MAKEFILE_LIST)) $(OBJ)
	$(CC) -shared $(filter %.o,$^) -o $@ $(addprefix -l,$(LIBS))

-include $(patsubst %,$(MODULES_PATH)/%/makefile,$(MODULES))

$(MODULES_PATH)/modules.c:
	@echo "#include <core/lengine.h>\n" > $@
	@echo "void le_init_modules(LEngine* engine)" >> $@
	@echo "{" >> $@
	@for module in $(MODULES) ; do\
		echo "\t"$$module"_init(engine);" >> $@ ;\
	done
	@echo "}" >> $@

clean:
	rm $(MODULES_PATH)/modules.c
	rm -f $(LIB_PATH)/libengine.so
	rm -f $(OBJ)
	rm -f $(DEP)

-include $(DEP)
%.d: %.c
	$(CC) -MM $< > $@
%.o: %.c
	$(CC) -c -fpic $< -o $@ -I.
