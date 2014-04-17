/*
 * Bison library for Alblang Programing Language
 */
 
%{
    #include <stdio.h>
%}

/* 
 * Tokens declaration
 */

%token BREAK CASE CLASS CONTINUE DEF DO ELSE END IF INHERITS FOR NEW PRIVATE PROTECTED PUBLIC RETURN SWITCH VOID WHILE 

%token COMMENT_START COMMENT_END COMMENT

%token EQUAL ASSIGN BOOLEAN

%token PLUS MINUS TIMES DIVIDE

%token <id> TYPE IDENTIFIER 

%token <val> NUMBER FLOAT

%token EOL

%%

program : class

class: /* empty */
	| CLASS type EOL definition END { printf("class: \n"); }

type: /* empty */
	| TYPE { printf("new class founded type\n"); }

definition : /* empty */
	| DEF IDENTIFIER END { printf(" method name\n"); }

%%

yyerror(char *s) {
    fprintf(stderr, "ERROR: %s\n", s);
}