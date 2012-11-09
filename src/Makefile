# Makefile

.PHONY : all
all:
	bison -d alblang.y 
	flex alblang.lex
	cc -o alblang alblang.tab.c lex.yy.c -lfl

#testing
#	./alblang test.alb