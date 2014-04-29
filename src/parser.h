/* Functions interfaces */
#include <stdlib.h>

extern mpc_parser_t* Integer; 
extern mpc_parser_t* Identifier; 
extern mpc_parser_t* Operator; 
extern mpc_parser_t* Comment;
extern mpc_parser_t* Expr; 
extern mpc_parser_t* Alblang;

void init();
void create_parsers();
void parser_execute(char* input);
void parser_execute_file(char* file_name);
void cleanup_parsers();