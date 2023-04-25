#ifndef _MAIN_
#define _MAIN_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <error.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BSIZE 1024
#define TOK_BSIZE 128
#define TOK_DLIM " \t\r\n\a"

/*points to an array*/
extern char **environ;

/**
 * struct data - struct contains all relevant data
 * @av: arg vec
 * @inp: cmd line entered by the user
 * @args: tokens of the cmd line
 * @status: prev stat of the shell
 * @counter: lines counter
 * @_environ: env var
 * @pid: process ID
 */
typedef struct data
{
	char **av;
	char *inp;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_sh;
/**
 * struct sep_lists - linked list
 * @separator: ; | &
 * @next: next node
 * Desc: linked list to store separators
 */
typedef struct sep_lists
{
	char separator;
	struct sep_lists *next;
} sep_list;
/**
 * struct line_lists - linked list
 * @line: cmd line
 * @next: next node
 * Desc: linked list to store command lines
 */
typedef struct line_lists
{
	char *line;
	struct line_lists *next;
} line_list;
/**
 * struct rvar_list -  linked list
 * @len_var: length of the var
 * @val: value of the var
 * @len_val: length of the value
 * @next: next node
 * Desc: list to store variables
 */
typedef struct rvar_list
{
	int len_var;
	char *val;
	int len_val;
	struct rvar_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct
 * @name: The name of the cmd builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_sh *datash);
} built_in;

/* 1-get_builtin */
int (*get_builtin(char *cmd))(data_sh *datash);

/* get_err.c */
int get_err(data_sh *datash, int eval);

/* cd_dot.c */
void cd_dot(data_sh *datash);
void cd_to(data_sh *datash);
void cd_prev(data_sh *datash);
void cd_home(data_sh *datash);

/* cd_sh.c */
int cd_shell(data_sh *datash);

/* syntax_error.c */
int count_char(char *inp, int idx);
int err_sep_op(char *inp, int idx, char last);
int first_char(char *inp, int *idx);
void print_syntax_err(data_sh *datash, char *inp, int idx, int bool);
int check_syntax_err(data_sh *datash, char *inp);

/* cmdexec.c */
int cdir(char *path, int *idx);
char *_which(char *cmd, char **_environ);
int is_exec(data_sh *datash);
int check_err_cmd(char *dir, data_sh *datash);
int cmd_exec(data_sh *datash);

/* split.c */
char *swap_char(char *inp, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *inp);
void move_next(sep_list **list_s, line_list **list_l, data_sh *datash);
int split_cmd(data_sh *datash, char *inp);
char **split_line(char *inp);

/* get_line.c */
void assign_line(char **lineptr, size_t *nl, char *buffer, size_t jb);
ssize_t get_line(char **lineptr, size_t *nl, FILE *stream);

/* sh_loop.c */
char *del_comment(char *inp);
void shell_loop(data_sh *datash);

/* rd_line.c */
char *read_line(int *idx_eof);

/* ax_err.c */
char *strcat_cd(data_sh *datash, char *msg, char *err, char *ver_str);
char *err_get_cd(data_sh *datash);
char *err_not_found(data_sh *datash);
char *err_exit_shell(data_sh *datash);

/* ax_err1.c */
char *err_get_alias(char **args);
char *err_env(data_sh *datash);
char *err_syntax(char **args);
char *err_permission(char **args);
char *err_path_126(data_sh *datash);

/* ax_elp.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_gen(void);
void aux_help_exit(void);

/* ax_elp1.c */
void aux_help(void);
void aux_help_aka(void);
void aux_help_cd(void);

/* ax_ls.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* ax_ls1.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* ax_m.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* ax_stdlb.c */
int get_len(int num);
char *aux_itoa(int num);
int _atoi(char *str);

/* ax_str*/
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *str, char *str2);
char *_strchr(char *str, char c);
int _strspn(char *str, char *acc);

/* ax_str1.c */
char *_strdup(const char *str);
int _strlen(const char *str);
int cmp_chars(char str[], const char *dlim);
char *_strtok(char str[], const char *dlim);
int _isdigit(const char *str);

/* ax_str2.c */
void rev_str(char *str);

/* env.c */
char *_getenv(const char *name, char **_environ);
int _env(data_sh *datash);

/* env1.c */
char *cpy_info(char *name, char *val);
void set_env(char *name, char *val, data_sh *datash);
int _setenv(data_sh *datash);
int _unsetenv(data_sh *datash);

/* exe_line */
int exec_line(data_sh *datash);

/* ext_shell.c */
int exit_shell(data_sh *datash);

/* g_sigint.c */
void get_sigint(int sig);

/* rep_var.c */
void check_env(r_var **hd, char *inp, data_sh *data);
int check_vars(r_var **hd, char *inp, char *st, data_sh *data);
char *replaced_input(r_var **head, char *inp, char *new_inp, int nlen);
char *rep_var(char *inp, data_sh *datash);

/* g_help.c */
int get_help(data_sh *datash);
#endif
