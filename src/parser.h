/* Functions interfaces */
#include <stdlib.h>

extern mpc_parser_t* Number; 
extern mpc_parser_t* Symbol; 
extern mpc_parser_t* String; 
extern mpc_parser_t* Comment;
extern mpc_parser_t* Sexpr;  
extern mpc_parser_t* Qexpr;  
extern mpc_parser_t* Expr; 
extern mpc_parser_t* Alblang;

/* Forward Declarations */
struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

/* Lisp Value */
enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_FUN, LVAL_SEXPR, LVAL_QEXPR };

typedef lval*(*lbuiltin)(lenv*, lval*);

void create_parsers();
void parser_execute(lenv* env, char* input);
void parser_execute_files(lenv* e, int argc, char** argv);
void cleanup_parsers();

lval* lval_num(long x);
lval* lval_err(char* fmt, ...);
lval* lval_sym(char* s);
lval* lval_str(char* s);
lval* lval_builtin(lbuiltin func);
lval* lval_sexpr(void);
lval* lval_qexpr(void);
lval* lval_lambda(lval* formals, lval* body);

int  lval_eq(lval* x, lval* y);


lval* lval_call(lenv* e, lval* f, lval* a);
lval* lval_eval_sexpr(lenv* e, lval* v);
lval* lval_eval(lenv* e, lval* v);
lval* lval_read_num(mpc_ast_t* t);
lval* lval_read_str(mpc_ast_t* t);
lval* lval_read(mpc_ast_t* t);

void  lval_del(lval* v);
lval* lval_copy(lval* v);
lval* lval_add(lval* v, lval* x);
lval* lval_join(lval* x, lval* y);
lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);

void lval_print(lval* v);
void lval_print_expr(lval* v, char open, char close);
void lval_print_str(lval* v);
void lval_print(lval* v);
void lval_println(lval* v);

char* ltype_name(int t);

/* Lisp Environment */
struct lenv;

lenv* lenv_new(void);
void  lenv_del(lenv* e);
lenv* lenv_copy(lenv* e);
lval* lenv_get(lenv* e, lval* k);
void  lenv_put(lenv* e, lval* k, lval* v);
void  lenv_def(lenv* e, lval* k, lval* v);

void  lenv_add_builtin(lenv* e, char* name, lbuiltin func);
void  lenv_add_builtins(lenv* e);

lval* builtin_lambda(lenv* e, lval* a);
lval* builtin_list(lenv* e, lval* a);
lval* builtin_head(lenv* e, lval* a);
lval* builtin_tail(lenv* e, lval* a);

lval* builtin_eval(lenv* e, lval* a);
lval* builtin_join(lenv* e, lval* a);
lval* builtin_op(lenv* e, lval* a, char* op);
lval* builtin_add(lenv* e, lval* a);
lval* builtin_sub(lenv* e, lval* a);
lval* builtin_mul(lenv* e, lval* a);
lval* builtin_div(lenv* e, lval* a);

lval* builtin_var(lenv* e, lval* a, char* func);
lval* builtin_def(lenv* e, lval* a);
lval* builtin_put(lenv* e, lval* a);

lval* builtin_ord(lenv* e, lval* a, char* op);

lval* builtin_gt(lenv* e, lval* a);
lval* builtin_lt(lenv* e, lval* a);
lval* builtin_ge(lenv* e, lval* a);
lval* builtin_le(lenv* e, lval* a);
lval* builtin_cmp(lenv* e, lval* a, char* op);
lval* builtin_eq(lenv* e, lval* a);
lval* builtin_ne(lenv* e, lval* a);

lval* builtin_if(lenv* e, lval* a);

lval* builtin_load(lenv* e, lval* a);
lval* builtin_print(lenv* e, lval* a);
lval* builtin_error(lenv* e, lval* a);
