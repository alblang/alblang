# Makefile

CFLAGS=-std=c99 -Wall
LFLAGS=-ledit -lm
LIBS=parser.c mpc.c
SOURCES=main.c

all: clean 
	#bison -d alblang.y 
	#flex alblang.lex 
	#cc -o alblang alblang.tab.c lex.yy.c -lfl
	$(CC) $(CFLAGS) main.c $(LIBS) $(LFLAGS) -o ../bin/alblang

clean:
	#rm -rf lex.yy.c
	#rm -rf alblang.tab.c
	#rm -rf alblang.tab.h
	rm -rf ../bin
	mkdir ../bin