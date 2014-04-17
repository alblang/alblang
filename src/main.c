#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"

#include "parser.h"

#include <editline/readline.h>

mpc_parser_t* Number;
mpc_parser_t* Symbol; 
mpc_parser_t* Sexpr; 
mpc_parser_t* Qexpr;  
mpc_parser_t* Expr;  
mpc_parser_t* Alblang;

void init() {
  puts("alb v0.0.1");
  puts("Ctrl + c to exit.");
}

void create_parsers() {
    /* Create Some Parsers */
  Number   = mpc_new("number");
  Symbol   = mpc_new("symbol");
  Sexpr    = mpc_new("sexpr");
  Qexpr    = mpc_new("qexpr");
  Expr     = mpc_new("expr");
  Alblang = mpc_new("alblang");

  /* Define them with the following Language */
  mpca_lang(MPC_LANG_DEFAULT,
    "                                                      \
      number : /-?[0-9]+/ ;                                \
      symbol : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+/ ;          \
      sexpr  : '(' <expr>* ')' ;                           \
      qexpr  : '{' <expr>* '}' ;                           \
      expr   : <number> | <symbol> | <sexpr> | <qexpr> ;   \
      alblang  : /^/ <expr>* /$/ ;                       \
    ",
    Number, Symbol, Sexpr, Qexpr, Expr, Alblang);
}

void cleanup_parsers() {
  mpc_cleanup(6, Number, Symbol, Sexpr, Qexpr, Expr, Alblang);
}

int main(int argc, char** argv) {
  
  lenv* e = lenv_new();
  lenv_add_builtins(e);

  create_parsers();
  
  init();
  
  while(1) {
    char* input = readline("alb >> ");

    add_history(input);
    
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Alblang, &r)) {      
      lval* x = lval_eval(e, lval_read(r.output));
      lval_println(x);
      lval_del(x);
      
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }

  /* Undefine and Delete our Parsers */
  cleanup_parsers();
  
  return 0;
}
