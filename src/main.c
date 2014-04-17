#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"

#include "parser.h"

#ifdef _WIN32

  #include <string.h>

  static char buffer[2048];

  /* Fake readline function */
  char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);

    cpy[strlen(ctr)-1] = '\0';
    
    return cpy;
  }

  /* Fake add_history function */
  void add_history(char* unused) {}

#else

  #include <editline/readline.h>

#endif

void init() {
  puts("alb v0.0.1");
  puts("Ctrl + c to exit.");
}

int main(int argc, char** argv) {
  
  lenv* e = lenv_new();
  lenv_add_builtins(e);

  /* Create Some Parsers */
  mpc_parser_t* Number   = mpc_new("number");
  mpc_parser_t* Symbol   = mpc_new("symbol");
  mpc_parser_t* Sexpr    = mpc_new("sexpr");
  mpc_parser_t* Qexpr    = mpc_new("qexpr");
  mpc_parser_t* Expr     = mpc_new("expr");
  mpc_parser_t* Microlisp = mpc_new("microlisp");

  /* Define them with the following Language */
  mpca_lang(MPC_LANG_DEFAULT,
    "                                                      \
      number : /-?[0-9]+/ ;                                \
      symbol : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+/ ;          \
      sexpr  : '(' <expr>* ')' ;                           \
      qexpr  : '{' <expr>* '}' ;                           \
      expr   : <number> | <symbol> | <sexpr> | <qexpr> ;   \
      microlisp  : /^/ <expr>* /$/ ;                       \
    ",
    Number, Symbol, Sexpr, Qexpr, Expr, Microlisp);
  init();
  
  while(1) {
    char* input = readline("alb >> ");

    add_history(input);
    
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Microlisp, &r)) {      
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
  mpc_cleanup(6, Number, Symbol, Sexpr, Qexpr, Expr, Microlisp);
  
  return 0;
}
