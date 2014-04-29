#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"
#include "parser.h"

mpc_parser_t* Integer; 
mpc_parser_t* Identifier; 
mpc_parser_t* Operator; 
mpc_parser_t* Comment;
mpc_parser_t* Expr; 
mpc_parser_t* Alblang;

void init() {
  puts("alblang v0.1");
  puts("Ctrl + c to exit.");
}

/* Creation of the Parsers */
void create_parsers() {
  Integer    = mpc_new("integer");
  Identifier = mpc_new("identifier");
  Operator   = mpc_new("operator");
  Comment = mpc_new("comment");
  Expr    = mpc_new("expr");
  Alblang = mpc_new("alblang");

  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                                                   \
      integer  : /[0-9]+/ ;                                                             \
      identifier  : /[a-zA-Z]+/ ;                                                       \
      operator  : /[+\\-*\\/=<>!&]+/ ;                                                  \
      comment : /#[^\\r\\n]*/ ;                                                         \
      expr    : '(' <expr>* ')' | <integer>  | <identifier> | <comment> | <operator>;   \
      alblang : /^/ <expr>* /$/ ;                                                       \
    ",
    Integer, Identifier, Operator, Comment, Expr, Alblang);
}

void parser_execute(char* input) {
  mpc_result_t r;
    if (mpc_parse("<stdin>", input, Alblang, &r)) {            
      // print the parser tree
      mpc_ast_print(r.output);
      
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
}

/* Undefine and Delete our Parsers */
void cleanup_parsers() {
  mpc_cleanup(6, Integer, Identifier, Operator, Comment, Expr, Alblang);
}