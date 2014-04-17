# Makefile

.PHONY : all
all:
	bison -d alblang.y 
	flex alblang.lex 
	cc -o alblang alblang.tab.c lex.yy.c -lfl

#testing
#	./alblang test.alb

.PHONY : clean
clean:
	rm -rf lex.yy.c
	rm -rf alblang.tab.c
	rm -rf alblang.tab.h