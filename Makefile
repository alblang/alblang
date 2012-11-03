# part of the makefile 
alblang: 	alblang.lex alblang.y
			#bison -d alblang.y 
			flex alblang.lex
			#cc -o $@ alblang.tab.c lex.yy.c -lfl
			cc lex.yy.c -lfl -o alblang
			./alblang test.alb