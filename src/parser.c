/*
 * Parser, grammar and front-end of Alblang
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"
#include "parser.h"

mpc_parser_t* Integer; 
mpc_parser_t* Comment;
mpc_parser_t* Expr; 
mpc_parser_t* Term;
mpc_parser_t* Factor; 
mpc_parser_t* Alblang;

void init() {
  puts("alblang v0.1");
  puts("Ctrl + c to exit.");
}

/* Creation of the Parsers */
void create_parsers() {
  Integer = mpc_new("integer");
  Comment = mpc_new("comment");
  Expr    = mpc_new("expr");
  Term    = mpc_new("term");
  Factor  = mpc_new("factor");
  Alblang = mpc_new("alblang");

  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT,
    "  integer  : /[0-9]+/ ;                                 "
    "  comment : /#[^\\r\\n]*/ ;                             "
    "  expr    : <term> (('+' | '-') <term>)* ;        "
    "  term    : <factor> (('*' | '/') <factor>)* ;    "
    "  factor  : '(' <expr> ')' | <integer> ;                "
    "  alblang : /^/ <expr> /$/ ;                            ",
    Integer, Comment, Expr, Term, Factor, Alblang);
}

void parser_execute(char* input) {
  mpc_result_t r;
    if (mpc_parse("input", input, Alblang, &r)) {            
      // print the parser tree
      mpc_ast_print(r.output);
      
      //long result = eval(r.output);
      //printf("%li\n", result);

      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
}

void parser_execute_file(char* file_name) {
  mpc_result_t r;
  if (mpc_parse_contents(file_name, Alblang, &r)) {
    mpc_ast_print(r.output);
    mpc_ast_delete(r.output);
  } else {
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
  }
}

/* Undefine and Delete our Parsers */
void cleanup_parsers() {
  mpc_cleanup(6, Integer, Comment, Expr, Term, Factor, Alblang);
}

long eval(mpc_ast_t* t) {
  
  if (strstr(t->tag, "integer")) { 
    return atoi(t->contents); 
  }

  long x = eval(t->children[1]);
  
  char* op = t->children[2]->contents;
    
  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }
  
  return x;  
}

/* Use operator string to see which operation to perform */
long eval_op(long x, char* op, long y) {
  if (strcmp(op, "+") == 0) { return x + y; }
  if (strcmp(op, "-") == 0) { return x - y; }
  if (strcmp(op, "*") == 0) { return x * y; }
  if (strcmp(op, "/") == 0) { return x / y; }
  return 0;
}