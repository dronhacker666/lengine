export LIB_PATH = $(abspath lib)
export BIN_PATH = $(abspath bin)
export MODULES_OUT_PATH = $(BIN_PATH)/modules

export ENGINE_PATH = $(abspath src/engine)
PLAYER_PATH = $(abspath src/player)
MODULES_PATH = $(abspath src/modules)

MODULES_PATHS = $(dir $(wildcard $(MODULES_PATH)/*/))
MODULES = $(patsubst $(MODULES_PATH)/%/,module_%,$(MODULES_PATHS))

.PHONY: all clean player engine clean

all: player $(MODULES)
	cd $(BIN_PATH) && ./player

$(LIB_PATH):; mkdir -p $@
$(BIN_PATH):; mkdir -p $@
$(MODULES_OUT_PATH):; mkdir -p $@

player: $(BIN_PATH) engine 
	$(MAKE) -C $(PLAYER_PATH)

engine: $(LIB_PATH)
	$(MAKE) -C $(ENGINE_PATH)

module_%: engine $(MODULES_OUT_PATH)
	mkdir -p $(MODULES_OUT_PATH)/$(patsubst module_%,%,$@)
	$(MAKE) -C $(patsubst module_%,$(MODULES_PATH)/%,$@)

clean:
	$(MAKE) -C $(ENGINE_PATH) clean
	$(MAKE) -C $(PLAYER_PATH) clean
	@for m in $(MODULES_PATHS); do\
		$(MAKE) -C $$m clean;\
	done
