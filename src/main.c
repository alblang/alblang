#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"
#include "parser.h"

#include <editline/readline.h>

void init() {
  puts("alb v0.0.1");
  puts("Ctrl + c to exit.");
}

int main(int argc, char** argv) {
  
  lenv* e = lenv_new();
  lenv_add_builtins(e);

  create_parsers();
  
  /* Interactive Prompt */
  if (argc == 1) {
    init();
  
    while(1) {
      char* input = readline("alb >> ");

      add_history(input);
      
      parser_execute(e, input);

      free(input);
    }


  } 
  
  /* Supplied with list of files */
  if (argc >= 2) {
  
    parser_execute_files(e, argc, argv);
  }

  cleanup_parsers();

  return 0;
}
