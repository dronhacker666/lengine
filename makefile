MAKE_FLAGS = -s

export LIB_PATH = $(abspath lib)
export BIN_PATH = $(abspath bin)

export ENGINE_PATH = $(abspath src/engine)
PLAYER_PATH = $(abspath src/player)

.PHONY: all clean player engine clean

all: player
	cd $(BIN_PATH) && ./player

$(LIB_PATH):; mkdir -p $@
$(BIN_PATH):; mkdir -p $@

player: $(BIN_PATH) engine 
	$(MAKE) $(MAKE_FLAGS) -C $(PLAYER_PATH)

engine: $(LIB_PATH)
	$(MAKE) $(MAKE_FLAGS) -C $(ENGINE_PATH)

module_%: engine $(MODULES_OUT_PATH)
	mkdir -p $(MODULES_OUT_PATH)/$(patsubst module_%,%,$@)
	$(MAKE) $(MAKE_FLAGS) -C $(patsubst module_%,$(MODULES_PATH)/%,$@)

clean:
	$(MAKE) $(MAKE_FLAGS) -C $(ENGINE_PATH) clean
	$(MAKE) $(MAKE_FLAGS) -C $(PLAYER_PATH) clean
