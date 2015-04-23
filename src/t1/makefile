SRC += *.c
SRC += ../lib/*.c
SRC += LRenderNode/*.c
SRC += LRenderTarget/*.c

all:
	$(CC) $(SRC) -o run -std=c99 -lX11 -lGL -lGLU -lm -Wall
	./run
