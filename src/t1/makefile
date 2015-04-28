SRC += *.c
SRC += ../lib/*.c
SRC += LRenderNode/*.c

all: genOpenGLExt
	$(CC) $(SRC) -o run -std=c99 -lX11 -lGL -lGLU -lm -Wall
	./run

include OpenGLExt.mk
