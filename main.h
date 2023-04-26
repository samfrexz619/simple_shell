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

/*Points to an arr*/
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
} sep_ls;
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
} line_ls;
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
} st_var;

/**
 * struct builtin_s - Builtin struct
 * @name: The name of the cmd builtin i.e cd, exit, env
 * @h: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*h)(data_sh *datash);
} built_in;

/* 1-get_builtin */
int (*get_builtin(char *cmd))(data_sh *datash);

/* get_err.c */
int getErr(data_sh *datash, int eval);

/* cd_dot.c */
void _cd(data_sh *datash);
void cd_into(data_sh *datash);
void cd_prev(data_sh *datash);
void cd_hm(data_sh *datash);

/* cd_sh.c */
int cd_sh(data_sh *datash);

/* syntax_error.c */
int count_char(char *inp, int idx);
int err_sep_op(char *inp, int idx, char last);
int first_char(char *inp, int *idx);
void print_syntax_err(data_sh *datash, char *inp, int idx, int bool);
int check_syntax_err(data_sh *datash, char *inp);

/* cmdexec.c */
int cdir(char *path, int *idx);
char *l_wch(char *cmd, char **_environ);
int is_exec(data_sh *datash);
int errCmd(char *dr, data_sh *datash);
int _exec(data_sh *datash);

/* split.c */
char *swap_char(char *inp, int bool);
void add_nodes(sep_ls **head_s, line_ls **head_l, char *inp);
void move_next(sep_ls **list_s, line_ls **list_l, data_sh *datash);
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
char *strcat_cd(data_sh *datash, char *msg, char *err, char *_str);
char *errCd(data_sh *datash);
char *errNotf(data_sh *datash);
char *errExitsh(data_sh *datash);

/* ax_err1.c */
char *err_get_alias(char **args);
char *errEnv(data_sh *datash);
char *err_syntax(char **args);
char *err_permission(char **args);
char *errPath126(data_sh *datash);

/* ax_elp.c */
void xh_env(void);
void xh_setenv(void);
void xh_unsetenv(void);
void xh_gen(void);
void xh_exit(void);

/* ax_elp1.c */
void x_help(void);
void xh_aka(void);
void xh_cd(void);

/* ax_ls.c */
sep_ls *addSpNodeEnd(sep_ls **head, char sep);
void freeSpLs(sep_ls **head);
line_ls *addLnNodeEnd(line_ls **head, char *line);
void freeLnls(line_ls **head);

/* ax_ls1.c */
st_var *addRvarNd(st_var **head, int lenVar, char *var, int lenVal);
void freeRvarLs(st_var **head);

/* ax_m.c */
void _memcpy(void *newptr, const void *ptr, unsigned int sz);
void *_realloc(void *ptr, unsigned int old_sz, unsigned int new_sz);
char **_reallocdp(char **ptr, unsigned int old_sz, unsigned int new_sz);

/* ax_stdlb.c */
int getLength(int num);
char *x_itoa(int num);
int _atoi(char *str);

/* ax_str*/
char *_strcat(char *dst, const char *src);
char *_strcpy(char *dst, char *src);
int _strcmp(char *str, char *str2);
char *_strchr(char *str, char ch);
int _strspn(char *str, char *acc);

/* ax_str1.c */
char *_strdup(const char *str);
int _strlen(const char *str);
int cmp_chars(char str[], const char *dlim);
char *_strtok(char str[], const char *dlim);
int _isdigit(const char *str);

/* ax_str2.c */
void revStr(char *str);

/* env.c */
char *_getenv(const char *name, char **_environ);
int _env(data_sh *datash);

/* env1.c */
char *cpyInfo(char *name, char *val);
void setEnv(char *name, char *val, data_sh *datash);
int _setEnv(data_sh *datash);
int _unSetEnv(data_sh *datash);

/* exe_line */
int exec_line(data_sh *datash);

/* ext_shell.c */
int exit_shell(data_sh *datash);

/* g_sigint.c */
void get_sigint(int sig);

/* r_var.c */
void check_env(st_var **hd, char *inp, data_sh *data);
int check_vars(st_var **hd, char *inp, char *stat, data_sh *data);
char *replaced_input(st_var **head, char *inp, char *new_inp, int nlen);
char *rep_var(char *inp, data_sh *datash);

/* g_help.c */
int get_help(data_sh *datash);
#endif
