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
 * @input: cmd line entered by the user
 * @args: tokens of the cmd line
 * @status: prev stat of the shell
 * @counter: lines counter
 * @_environ: env var
 * @pid: process ID
 */
typedef struct data
{
	char **av;
	char *input;
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



#endif
