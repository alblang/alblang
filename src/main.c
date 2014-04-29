#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"
#include "parser.h"

#include <editline/readline.h>

int main(int argc, char** argv) {
  
  create_parsers();    
  
  init();

  if (argc > 1) {

    parser_execute_file(argv[1]);
  
  } else {    
    while(1) {
      char* input = readline(":>  ");

      add_history(input);
      
      parser_execute(input);

      free(input);
    }
  }
  cleanup_parsers();

  return 0;
}
