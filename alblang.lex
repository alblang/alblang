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

class|inherits|def|end|return|if|else|for|while|do|switch|case|break|continue|void|public|private|protected|new {
    printf("keyword : %s\n", yytext);
}

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
    yylex();
}