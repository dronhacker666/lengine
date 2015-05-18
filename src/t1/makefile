SRC += *.c
SRC += ../lib/*.c
SRC += LRenderNode/*.c
SRC += decoders/*.c

all: genOpenGLExt
	$(CC) $(SRC) -o run -std=c99 -lX11 -lGL -lGLU -lm -Wall -Iinclude
	./run

include OpenGLExt.mk
