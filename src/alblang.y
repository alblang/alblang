/*
 * Bison library for Alblang Programing Language
 */
 
%{
    #include <stdio.h>
%}

/* 
 * Tokens declaration
 */

%token CLASS 258
%token DEF 259
%token END 260
%token INHERITS 261
%token RETURN 262
%token IF 263
%token ELSE 264
%token FOR 265
%token WHILE 266
%token DO 267
%token SWITCH 268
%token CASE 269
%token BREAK 270
%token CONTINUE 271
%token VOID 272
%token PUBLIC 273
%token PRIVATE 274
%token PROTECTED 275
%token NEW 276
%token EQUAL 278
%token ASSIGN 279
%token COMMENT_START 280
%token COMMENT_END 281
%token COMMENT 282
%token PLUS 283
%token MINUS 284
%token TIMES 285
%token DIVIDE 286
%token TYPE 287
%token IDENTIFIER 288
%token BOOLEAN 289
%token EOL 290

%%

program : class

class: /* empty */
	| CLASS type EOL definitions END { printf("class: %c\n", $2); }

type: /* empty */
	| TYPE { printf("new class founded type: %c\n", $1); }

definitions : /* empty */
	| definition definition { printf("definitions: %c\n", $1); }

definition : /* empty */
	| DEF IDENTIFIER END { printf(" method name : %c\n", $2); }

%%

yyerror(char *s) {
    fprintf(stderr, "ERROR: %s\n", s);
}