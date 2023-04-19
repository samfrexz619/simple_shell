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
 * @_pid: process ID
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


#endif
