# Makefile

CFLAGS=-std=c99 -Wall
LFLAGS=-ledit -lm
LIBS=parser.c parser/mpc.c
SOURCES=main.c

all: clean
	$(CC) $(CFLAGS) main.c $(LIBS) $(LFLAGS) -o ../alblang

clean:
	rm -rf ../bin
	mkdir ../bin
