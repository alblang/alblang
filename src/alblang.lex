/* 
 * Scanner for Alblang Programming language 
 * Copyright (C) 2012 Jesús Navarrete <jenaiz@alblang.org>
 * Read the LICENSE file
 */

%{ 

	#include "alblang.tab.h"

%}

EQUAL =
ASSIGN <-
NUMBER [0-9]+
FLOAT [+-]?[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?
IDENTIFIER [a-z][a-z0-9]*
TYPE_IDENTIFIER [A-Z][a-zA-Z0-9]+
COMMENT_START "/*"
COMMENT_END "*/"
COMMENT "//"

%%
{COMMENT_START} {
    printf("start comment\n");
}

{COMMENT_END} {
    printf("end comment\n");
}

{COMMENT} {
    printf("comment\n");
}
{EQUAL} {
    printf("equal : %s\n", yytext);
}

{ASSIGN} {
    printf("assign : %s\n", yytext);
}

"class" { return CLASS; }
"inherits" { return INHERITS; }
"def" { return DEF; }
"end" { return END; }

"return" { return RETURN; }
"if" { return IF; }
"else" { return ELSE; }
"for" { return FOR; }
"while" { return WHILE; }
"do" { return DO; }
"switch" { return SWITCH; }
"case" { return CASE; }
"break" { return BREAK; }
"continue" { return CONTINUE; }
"void" { return VOID; }
"public" { return PUBLIC; }
"private" { return PRIVATE; }
"protected" { return PROTECTED; }
"new" { return NEW; }
"false" { return BOOLEAN; }
"true" { return BOOLEAN; }

"+"|"-"|"*"|"/" { 
    printf("operator : %s\n", yytext);
}

{TYPE_IDENTIFIER} {
    printf("type identifier : %s\n", yytext); 
}

{IDENTIFIER} {
    printf("identifier : %s\n", yytext); 
}

{NUMBER} { printf("number : %s\n", yytext); }

{FLOAT} { printf("float : %s\n", yytext); }

\n      { printf("EOL \n"); }

[ \t]   { /* ignore whitespace */ }

%%

int main( int argc, char **argv ) {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    yyparse();
    //yylex();    
}